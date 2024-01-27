#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>

#include <cpr/cpr.h>
#include <crow.h>



int  main()
{
    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/products" });

    std::cout << "Here is the list of products:\n";

    auto products = crow::json::load(response.text);
    for (const auto& product : products) {
        std::cout << product["id"] << ' '
            << product["name"].s() << ' '
            << product["price"] << '\n';
    }

    std::cout << "Please enter the id and quantity of the product to add to the basket. "
        << "When you're done, enter any word.\n";
    std::string input;
    std::cin >> input;
    std::regex is_number{ R"(\d+)" };
    while (std::regex_match(input, is_number)) {
        int id = std::stoi(input);
        int quantity;
        std::cin >> quantity;
        for (const auto& product : products) {
            if (product["id"] == id) {
                std::cout << "Selected " << product["name"] << " in amount " << quantity << '\n';

                //Sending it to the server
                //Version 1
               /*std::stringstream urlBuilder;
               urlBuilder << "http://localhost:18080/addproducttobasket/" << id;
               auto response = cpr::Get(cpr::Url{urlBuilder.str()},
                                        cpr::Parameters{{"quantity", std::to_string(quantity)}});*/
               // "http://localhost:18080/addproducttobasket/2?quantity=3"

               // Version 2
                auto response = cpr::Put(
                    cpr::Url{ "http://localhost:18080/addproducttobasket" },
                    cpr::Payload{
                        { "productId", std::to_string(id) },
                        { "quantity", std::to_string(quantity) }
                    }
                );

                if (response.status_code == 200 || response.status_code == 201) {
                    std::cout << "Added to basket :)\n";
                }
                else {
                    std::cout << "There was a problem adding the product to the basket :(\n";
                }
                break;
            }
        }

        std::cin >> input;
    }

    std::cout << "\nYour basket is now: \n";
    auto responseBasket = cpr::Get(cpr::Url{ "http://localhost:18080/basket" });
    auto responseRows = crow::json::load(responseBasket.text);
    for (const auto& responseRow : responseRows) {
        std::cout << responseRow["name"].s() << '\t'
            << responseRow["price"] << '\t'
            << "x " << responseRow["quantity"] << '\t'
            << "= " << responseRow["price"].d() * responseRow["quantity"].i() << '\n';
    }

    std::cout << "Total price: " << std::accumulate(
        responseRows.begin(),
        responseRows.end(),
        0.,
        [](double sum, crow::json::rvalue row) {
            return sum + row["price"].d() * row["quantity"].i();
        }
    ) << '\n';

    std::cout << "Bye!";


    return 0;
}
