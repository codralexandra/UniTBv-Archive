#include "products.h"


void populateStorage(Storage& storage)
{
	std::vector<Product> products{
		Product{ -1, "Milk",  5.f },
		Product{ -1, "Egg",   0.2f },
		Product{ -1, "Flour", 2.f },
		Product{ -1, "Butter", 8.f },
		Product{ -1, "Salt",  2.f },
		Product{ -1, "Jam",   5.f }
	};
	storage.insert_range(products.begin(), products.end());
}

AddToBasketHandler::AddToBasketHandler(Storage& storage)
	: m_db{storage}
{
}

crow::response AddToBasketHandler::operator()(const crow::request& req) const
{
	//crow::query_string qs{ req.body };
	//char* productId_chr = qs.get("productId");
	//char* quantity_chr = qs.get("quantity");
	// din pacate nu merge si crow inca nu are versiune cu functiile necesare

	auto bodyArgs = parseUrlArgs(req.body);
	auto end = bodyArgs.end();
	auto productIdIter = bodyArgs.find("productId");
	auto quantityIter = bodyArgs.find("quantity");
	if (productIdIter != end && quantityIter != end)
	{
		ShoppingBasketRow sbrow;
		sbrow.idProduct = std::stoi(productIdIter->second);
		sbrow.quantity = std::stoi(quantityIter->second);
		m_db.insert(sbrow);
	}
	return crow::response(201); // row was created and added
}
