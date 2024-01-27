#pragma once
#include "ProductType.h"
#include "Product.h"
class NonperishableProduct : public Product
{
public:
	NonperishableProduct(uint16_t id, const std::string& name, float price, ProductType type);
	uint16_t GetVAT() const override;
private:
	ProductType m_type;
	static const uint16_t kVAT = 19;
	/*
	Metoda statica -> se foloseste in instanta de clasa;
	O metoda obisnuita -> se foloseste in instanta de obiect;
	-----------------------------------------------------------
	Exemplu:
	A{
		static f();
		g();
	}
	A::f();
	A a; a.g();
	-----------------------------------------------------------
	Folosim static pentru constanta pentru TVA pentru a nu retine valoarea per obiect ci pe clasa.
	Const ne spune ca acea constanta nu se va modifica pe parcursul utilizarii.
	*/

};

