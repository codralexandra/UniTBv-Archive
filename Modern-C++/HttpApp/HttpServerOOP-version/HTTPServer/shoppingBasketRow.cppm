export module shoppingBasketRow;

namespace http
{
	export class ShoppingBasketRow
	{
	public:
		ShoppingBasketRow() = default;
		ShoppingBasketRow(int id, int productId, int quantity);
		int GetId()const;
		int GetIdPoduct()const;
		int GetQuantity()const;

		void SetId(int id);
		void SetIdProduct(int productId);
		void SetQuantity(int quantity);

	private:

		int m_id;
		int m_productId;
		int m_quantity;
	};
}