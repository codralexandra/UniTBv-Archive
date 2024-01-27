#include <vector>
#include <fstream>
#include <regex>
#include <iostream>
#include <algorithm>
#include "Product.h"
#include "ProductType.h"
#include "PerishableProduct.h"
#include "NonperishableProduct.h"

bool Comparator(const IPriceable* product1, const IPriceable* product2)
{
	//This comparator returns true if product1 comes first in an alphabetical order. False if not.
	return product1->GetName() < product2->GetName();

}
int main()
{
	std::vector<IPriceable*> products;
	for (std::ifstream in{ "product.prodb" }; !in.eof(); /*EMPTY*/)
	{
		uint16_t id;
		std::string name;
		float price;
		uint16_t vat;
		std::string expDateOrType;
		in >> id >> name >> price >> vat >> expDateOrType;
		if (std::regex_match(expDateOrType, std::regex(R"(\d\d\d\d-\d\d-\d\d)")))
		{
			IPriceable* product = new PerishableProduct(id, name, price, expDateOrType);
			products.push_back(product);
		}
		else
		{
			ProductType productType = ParseProductType(expDateOrType);
			//IPriceable* product = new NonperishableProduct(id, name, price, productType);
			products.emplace_back(new NonperishableProduct(id, name, price, productType));
		}
	}

	//testing
	//std::sort(products.begin(), products.end(), Comparator);
	//sort cu lambda function
	std::sort(products.begin(), products.end(), 
		[]
		(const IPriceable * product1, const IPriceable * product2)
		{return product1->GetName() < product2->GetName(); });
	for (const auto& product : products)
	{
		/*
			Mai eficient decat for-ul cu iteratie pentru ca in celalalt se aloca memorie pentru
			'i' si se apeleaza operatorul '[]'.

			Const auto& product e mai eficient cand vrem sa modificam elemente din vector pentru ca
			product e un pointer la elementele din products.

			Static cast - conversie numerica, pe tipuri primitive
			Dynamic cast - pt ierarhii de clase, pe tipuri de date abstracte
		*/
		auto p = dynamic_cast<Product*>(product);
		std::cout << (*p);
	}
	return 0;
}