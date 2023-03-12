// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 21-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"


namespace sdds {

	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const std::string& str):Station(str) {} // All of the station info is manipulated and assigned by the base class sdds::Station

	void Workstation::fill(std::ostream& os) { 
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		bool isMove = false; // not necessary in my solutions but required by workshop instructions
		if (!m_orders.empty()) {  // prevent if all the orders are moved already / no orders has been move to this workstation // prevent pointer access violation
			//std::cout << "Current Station is: " << Station::getItemName() << std::endl;
			if (Station::getQuantity() <= 0 || m_orders.front().isItemFilled(Station::getItemName())) { // Not enough inventory Or the item that this station is responsible of is filled
				if (m_pNextStation) { // if there is next station
					*m_pNextStation += std::move(m_orders.front()); // move the first order to the next station by stealing the resource of the orders
					m_orders.pop_front(); // remove the first order since the resources is already stealed by others, so we can safety destroyed it
					isMove = true;
				}
				else {
					if (m_orders.front().isOrderFilled()) { // if the order is all filled, move it to completed double end que
						g_completed.push_back(std::move(m_orders.front()));
						m_orders.pop_front();
						isMove = true;
					}
					else {
						g_incomplete.push_back(std::move(m_orders.front()));
						m_orders.pop_front();
						isMove = true;
					}

				}
			}
		}
		return isMove;
	}



	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation()const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os)const {
		if (!m_pNextStation) {
			os << Station::getItemName() << " --> End of Line\n";
		}
		else {
			os << Station::getItemName() << " --> " << m_pNextStation->getItemName() << "\n";
		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}
