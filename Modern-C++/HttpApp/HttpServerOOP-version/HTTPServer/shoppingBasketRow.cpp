module shoppingBasketRow;

using namespace http;

ShoppingBasketRow::ShoppingBasketRow(int id, int productId, int quantity)
	:m_id{ id }, m_productId{ productId }, m_quantity{ quantity }
{
}

int ShoppingBasketRow::GetId()const
{
	return m_id;
}

int ShoppingBasketRow::GetIdPoduct()const
{
	return m_productId;
}

int ShoppingBasketRow::GetQuantity()const
{
	return m_quantity;
}

void ShoppingBasketRow::SetId(int id)
{
	m_id = id;
}

void ShoppingBasketRow::SetIdProduct(int productId)
{
	m_productId = productId;
}

void ShoppingBasketRow::SetQuantity(int quantity)
{
	m_quantity = quantity;
}