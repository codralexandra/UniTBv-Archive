#pragma once

#include <cstdint>
#include <string>
using namespace std::string_literals;

enum class ProductType : uint8_t
{
	PersonalHygiene = 10u,
	SmallAppliences,
	Clothing
};

ProductType ParseProductType(const std::string& str);

std::string ProductTypeToString(ProductType type);
