#include <filesystem>
#include <iostream>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

#include "products.h"


// Cerinte:
// Sa se creeze si sa se populeze baza de date.
// Sa se creeze un server http cu urmatoarele rute:
//	/products  -> se vor trimite clientului produsele (vector, json)
//  /addproducttobasket/<id>?quantity=<value>  -> se va adauga un produs in cosul de cumparaturi (URL params)
//  /addproducttobasket  -> se va adauga un produs in cosul de cumparaturi (POST/PUT)
//  /basket  -> se trimit clientului produsele din cos (nume, pret, cantitate)


int main() {
	const std::string db_file = "products.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	auto initProductsCount = db.count<Product>();
	if (initProductsCount == 0)
		populateStorage(db);

	auto productsCount = db.count<Product>();
	std::cout << "productsCount = " << productsCount << '\n';


	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});

	CROW_ROUTE(app, "/products")([&db]() {
		std::vector<crow::json::wvalue> products_json;

		// auto products = db.get_all<Product>();  // can take a long time and a lot of memory
		for (const auto& product : db.iterate<Product>())
		{
			products_json.push_back(crow::json::wvalue{
				{"id", product.id},  // product_json["id"] = product.id;
				{"name", product.name},
				{"price", product.price}
				});

			//std::string product_json = db.dump(product);			
		}
		return crow::json::wvalue{ products_json };
		});


	CROW_ROUTE(app, "/addproducttobasket/<int>")([&db](const crow::request& req, int productId) {
		// validate productId

		char* quantity_chr = req.url_params.get("quantity");
		int quantity = 1;
		if (quantity_chr != nullptr) {
			quantity = std::stoi(quantity_chr); // on failure?
		}

		ShoppingBasketRow sbrow;
		sbrow.idProduct = productId;
		sbrow.quantity = quantity;
		db.insert(sbrow);

		return crow::response(200);
		});

	auto& addToBasketPut = CROW_ROUTE(app, "/addproducttobasket")
		.methods(crow::HTTPMethod::PUT); // https://stackoverflow.com/a/630475/12388382
	addToBasketPut(AddToBasketHandler(db));


	CROW_ROUTE(app, "/basket")([&db]() {
		using namespace sqlite_orm; // fara asta nu merg operatorii pt conditii (==, < etc)
		auto rows = db.select(
			sql::columns(&Product::name, &Product::price, &ShoppingBasketRow::quantity),
			sql::inner_join<ShoppingBasketRow>(sql::on(sql::c(&Product::id) == &ShoppingBasketRow::idProduct))
		);

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

	app.port(18080).multithreaded().run();


	return 0;
}