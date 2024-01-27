#include "routing.h"

using namespace http;

import product;

void Routing::Run(ProductStorage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});

	CROW_ROUTE(m_app, "/products")([&storage]() {
		std::vector<crow::json::wvalue> products_json;

		auto products = storage.GetProducts();
		for (const auto& product : products)
		{
			products_json.push_back(crow::json::wvalue{
				{"id", product.GetId()},  // product_json["id"] = product.id;
				{"name", product.GetName()},
				{"price", product.GetPrice()}
				});

			//std::string product_json = db.dump(product);	
		}
		return crow::json::wvalue{ products_json };
		});


	CROW_ROUTE(m_app, "/addproducttobasket/<int>")([&storage, this](const crow::request& req, int productId) {
		return AddProductToBasketRoute(storage, req, productId);
		
		});

	auto& addToBasketPut = CROW_ROUTE(m_app, "/addproducttobasket")
		.methods(crow::HTTPMethod::PUT); // https://stackoverflow.com/a/630475/12388382
	addToBasketPut(AddToBasketHandler(storage));


	CROW_ROUTE(m_app, "/basket")([&storage]() {
		auto rows = storage.GetBasket();

		std::vector<crow::json::wvalue> results;
		for (const auto& row : rows) {
			const auto& [name, price, quantity] = row;
			results.push_back(crow::json::wvalue{
				{ "name", name },
				{ "price", price },
				{ "quantity", quantity }
				});
		}

		return crow::json::wvalue{ results };
		});

	m_app.port(18080).multithreaded().run();

}

crow::response Routing::AddProductToBasketRoute(ProductStorage& storage, const crow::request& req, int productId) const
{
	// validate productId
	char* quantity_chr = req.url_params.get("quantity");
	int quantity = 1;
	if (quantity_chr != nullptr) {
		quantity = std::stoi(quantity_chr); // on failure?
	}

	storage.AddProductToShoppingBasket(productId, quantity);

	return crow::response(200);;
}
