#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

import utils;
import product;
import shoppingBasketRow;

namespace http
{	
	inline auto CreateStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"Products",
				//&UsersEntity::SetUsername, &UsersEntity::GetUsername
				sql::make_column("id", &Product::SetId, &Product::GetId, sql::primary_key().autoincrement()),
				sql::make_column("name", &Product::SetName, &Product::GetName),
				sql::make_column("price", &Product::SetPrice, &Product::GetPrice)
			),
			sql::make_table(
				"ShoppingBasket",
				sql::make_column("id", &ShoppingBasketRow::SetId, &ShoppingBasketRow::GetId, sql::primary_key().autoincrement()),
				sql::make_column("idProduct", &ShoppingBasketRow::SetIdProduct, &ShoppingBasketRow::GetIdPoduct),
				sql::make_column("quantity", &ShoppingBasketRow::SetQuantity, &ShoppingBasketRow::GetQuantity)
			)
		);
	}

	using Storage = decltype(CreateStorage(""));


	class ProductStorage
	{
	public:
		bool Initialize();

		std::vector<Product> GetProducts();
		void AddProductToShoppingBasket(int productId, int quantity);
		std::vector<std::tuple<std::string, float, int>> GetBasket();


	private:
		void PopulateStorage();

	private:
		const std::string kDbFile{ "products.sqlite" };

	private:
		Storage m_db = CreateStorage(kDbFile);
	};


	class AddToBasketHandler {
	public:
		AddToBasketHandler(ProductStorage& storage);

		crow::response operator() (const crow::request& req) const;

	private:
		ProductStorage& m_db;
	};
}