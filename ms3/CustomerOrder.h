// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 03-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef _SDDS_CUSTOMER_ORDER_H
#define _SDDS_CUSTOMER_ORDER_H
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

	struct Item {
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src) {};
	};



	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		// class variable
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string& str);
		// Rule of 5(not allow copy constructor and copy assignment)
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&& src)noexcept;
		CustomerOrder& operator=(CustomerOrder&& src)noexcept;
		~CustomerOrder();

		bool isOrderFilled()const;
		bool isItemFilled(const std::string& itemName)const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os)const;

	};
}





#endif //!_SDDS_CUSTOMER_ORDER_H