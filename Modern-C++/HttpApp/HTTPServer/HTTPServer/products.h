#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

import utils;

struct Product
{
	int id;
	std::string name;
	float price;
};

struct ShoppingBasketRow
{
	int id;
	int idProduct;
	int quantity;
};


inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Products",
			sql::make_column("id", &Product::id, sql::primary_key().autoincrement()),
			sql::make_column("name", &Product::name),
			sql::make_column("price", &Product::price)
		),
		sql::make_table(
			"ShoppingBasket",
			sql::make_column("id", &ShoppingBasketRow::id, sql::primary_key().autoincrement()),
			sql::make_column("idProduct", &ShoppingBasketRow::idProduct),
			sql::make_column("quantity", &ShoppingBasketRow::quantity)
		)
	);
}

using Storage = decltype(createStorage(""));


void populateStorage(Storage& storage);


class AddToBasketHandler {
public:
	AddToBasketHandler(Storage& storage);

	crow::response operator() (const crow::request& req) const;

private:
	Storage& m_db;
};
