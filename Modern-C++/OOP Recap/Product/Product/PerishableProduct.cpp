#include "PerishableProduct.h"

PerishableProduct::PerishableProduct(uint16_t id, const std::string& name, float price, const std::string& date)
	:Product(id,name,price), m_date(date)
{
}

uint16_t PerishableProduct::GetVAT() const
{
	return PerishableProduct::kVAT;
}
