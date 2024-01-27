export module product;
import <string>;

namespace http
{
	export class Product
	{
	public:
		Product() = default;
		Product(int id, const std::string& name, float price);

		int GetId() const;
		std::string GetName()const;
		float GetPrice()const;

		void SetId(int id);
		void SetName(const std::string& name);
		void SetPrice(float price);

	private:
		int m_id;
		std::string m_name;
		float m_price;
	};


}