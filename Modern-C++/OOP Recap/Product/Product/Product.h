#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include "ProductType.h"
#include "IPriceable.h"



class Product : public IPriceable
{
public:
	Product(uint16_t id, const std::string& name, float price);
	std::string GetName() const override;
	float GetPriceWithTVA() const override;
	virtual uint16_t GetVAT()const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Product& product);
	/*
		Const pt Product pt ca nu-l modificam afisandu-l si nu vrem sa-l copiem

		ostream buffer care retine informatiile care s-au afisat deja, ce vreau eu sa 
		afisez si unde si cum se afiseaza (+poz unde se scrie in fisier)

		Nu il punem const pentru ca se modifica dupa fiecare afisare, dar nu vrem sa-l copiem pentru
		ca trebuie sa folosim acelasi buffer pt toate afisarile (ca sa ajunga in acelasi loc)
	*/
	
private:
	uint16_t m_id;
	std::string m_name;
	float m_price;
};

