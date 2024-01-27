#include <crow.h>
#include "productsDatabase.h"

namespace http
{
	class Routing
	{
	public:
		void Run(ProductStorage& storage);

	private:
		crow::response AddProductToBasketRoute(ProductStorage& storage, const crow::request& req, int productId )const;

	private:
		crow::SimpleApp m_app;
	};
}