#include "NonperishableProduct.h"

NonperishableProduct::NonperishableProduct(uint16_t id, const std::string& name, float price, ProductType type)
	:Product(id,name,price), m_type(type)
{
}

uint16_t NonperishableProduct::GetVAT() const
{
	return NonperishableProduct::kVAT;
}
