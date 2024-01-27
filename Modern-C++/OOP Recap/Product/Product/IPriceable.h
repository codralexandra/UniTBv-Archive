#pragma once
#include <string>
class IPriceable
{
public:
	virtual std::string GetName() const = 0;
	virtual float GetPriceWithTVA() const = 0;
};
