#include <filesystem>
#include <iostream>
#include <memory>

#include <sqlite_orm/sqlite_orm.h>

#include "productsDatabase.h"
#include "routing.h"

import product;

using namespace http;
namespace sql = sqlite_orm;


// Cerinte:
// Sa se creeze si sa se populeze baza de date.
// Sa se creeze un server http cu urmatoarele rute:
//	/products  -> se vor trimite clientului produsele (vector, json)
//  /addproducttobasket/<id>?quantity=<value>  -> se va adauga un produs in cosul de cumparaturi (URL params)
//  /addproducttobasket  -> se va adauga un produs in cosul de cumparaturi (POST/PUT)
//  /basket  -> se trimit clientului produsele din cos (nume, pret, cantitate)


int main() {

	ProductStorage storage;
	if (!storage.Initialize())
	{
		std::cout << "Faild to initialize the database!";
		return -1;
	}

	Routing r;
	r.Run(storage);


	return 0;
}