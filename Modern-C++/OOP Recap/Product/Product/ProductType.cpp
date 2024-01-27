#include "ProductType.h"

ProductType ParseProductType(const std::string& str)
{
	if (str == "Clothing")
	{
		return ProductType::Clothing;
	}

	if (str == "PersonalHygiene")
	{
		return ProductType::PersonalHygiene;
	}
	
	if (str == "SmallAppliences")
	{
		return ProductType::SmallAppliences;
	}
	else
	{
		throw std::exception{ "Unknown product type" };
		//programul va reactiona la fel ca si cum ar primi o eroare de la c++
	}
}

std::string ProductTypeToString(ProductType type)
{
	switch (type)
	{
	case ProductType::Clothing:
		return "Clothing"s;
	case ProductType::PersonalHygiene:
		return "PersonalHygiene"s;
	case ProductType::SmallAppliences:
		return "SmallAppliences"s;
	}
}
