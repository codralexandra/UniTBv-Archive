#pragma once
#include <string>
#include "Product.h"
class PerishableProduct : public Product
{
public:
	PerishableProduct(uint16_t id, const std::string& name, float price, const std::string& date);
	uint16_t GetVAT() const override;
private:
	std::string m_date;
	static const uint16_t kVAT = 9;
};

