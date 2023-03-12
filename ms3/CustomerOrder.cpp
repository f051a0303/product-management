// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 03-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"

namespace sdds {
	// initialize class memeber
	size_t CustomerOrder::m_widthField = 0;

	// default constructor
	CustomerOrder::CustomerOrder() {};


	// 1-argument custom constructor
	CustomerOrder::CustomerOrder(const std::string& str) {
		sdds::Utilities extractor;
		std::vector<std::string> items{};
		size_t next_pos{ 0 };
		bool more;
		size_t itemCnt{ 0 };
		int i = 0;
		do {
			// First one is the customer name
			if (i == 0) {
				m_name = extractor.extractToken(str, next_pos, more);
			}
			// Second one is the product name
			if (i == 1) {
				m_product = extractor.extractToken(str, next_pos, more);
			}

			// extract all the item left
			if (i != 0 && i != 1) {
				items.push_back(extractor.extractToken(str, next_pos, more));
				itemCnt++; // count how many item has been extracted to the vector
			}
			i++;

		} while (more);

		if (m_widthField < extractor.getFieldWidth())
			m_widthField = extractor.getFieldWidth();


		m_cntItem = itemCnt; // save the itemCnt to the member

		m_lstItem = new Item * [m_cntItem];
		for (auto i = 0u; i < m_cntItem; ++i) {
			m_lstItem[i] = new Item(items[i]); // items[i] stored the item's name, used to construct the sdds::Item object
		}


	}

	// copy constructor
	CustomerOrder::CustomerOrder(const CustomerOrder&) {
		throw "Copy constructor for [CustomerOrder] is not available";
	}

	// move constructor
	CustomerOrder::CustomerOrder(CustomerOrder&& src)noexcept {
		*this = std::move(src);
	}

	// move assignment
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)noexcept {
		if (this != &src) {
			m_name = src.m_name;
			m_product = src.m_product;
			for (auto i = 0u; i < m_cntItem; i++) { // when m_cntItem = 0, the loop will not operated, so it is suitable for copy constructor to use;
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
			src.m_name.clear();
			src.m_product.clear();
		}
		return *this;
	}

	// destructor
	CustomerOrder::~CustomerOrder() {
		for (auto i = 0u; i < m_cntItem; i++) {
			delete m_lstItem[i]; // delete each pointer element
		}
		delete[] m_lstItem; // delete the container array itself
	}


	bool CustomerOrder::isOrderFilled()const {
		for (auto i = 0u; i < m_cntItem; i++) {
			if (!(m_lstItem[i]->m_isFilled))
				return false;
		}
		return true;
	}


	bool CustomerOrder::isItemFilled(const std::string& itemName)const {
		size_t j{}, k{};
		// j counts how many "itemName" is in the array, k counts how many "itemName" is filled
		for (auto i = 0u; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				j++;
				if (m_lstItem[i]->m_isFilled) {
					k++;
				}  
			}
		}
		if (j == 0) // j = 0 means the "itemName" is not in the array
			return true;
		if (j == k) // j = k means all "itemName" in the array is filled
			return true;

		return false;

	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		bool filledOne = false; // use this to control only one item filled each time

		for (auto i = 0u; i < m_cntItem && !filledOne; ++i) {
			if (m_lstItem[i]->m_itemName == station.getItemName()) {
				if (station.getQuantity() >= 1 && !m_lstItem[i]->m_isFilled) {
					if (!m_lstItem[i]->m_isFilled) {
						station.updateQuantity();
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						m_lstItem[i]->m_isFilled = true;
						os << std::setw(11) << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
						filledOne = true; 
					}
				}
				else if(station.getQuantity() == 0 && !m_lstItem[i]->m_isFilled) {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}


	// display function
	void CustomerOrder::display(std::ostream& os)const {
		using namespace std;
		os << m_name << " - " << m_product << "\n";

		for (auto i = 0u; i < m_cntItem; ++i) {
			os << "[" << setfill('0') << setw(6) << m_lstItem[i]->m_serialNumber << "] " << left << setfill(' ') << setw(CustomerOrder::m_widthField) << m_lstItem[i]->m_itemName << " - " << right << (m_lstItem[i]->m_isFilled == true ? "FILLED" : "TO BE FILLED") << endl;

		}
		os << setfill(' ');
	}

}