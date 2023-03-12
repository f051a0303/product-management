// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 21-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef _SDDS_WORKSTATION_H
#define _SDDS_WORKSTATION_H

#include <iostream>
#include <deque>
#include <string>
#include <utility>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		// Each Workstation is unique, so I delete all the copy and move constructor, assignment operator
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		// ---------------------
		
		Workstation(const std::string& str);
		// Try to filled the FIRST ORDER in the que by ONE item each time the function called
		void fill(std::ostream& os);
		// The function will move the FIRST ORDER in the que to the NEXT STATION IF: 
		//		1. The NEXT STATION exist (NOT nullptr) AND
		//		2. The items in the order are not responsible by this station OR
		//		3. The items in the order are responsible by this station, but this station don't have enough inventory OR
		//		4. The items responsible by this station are fully filled
		// The function will move the order into "g_completed" IF:
		//		1. There are no NEXT STATION (IS nullptr) AND
		//		2. ALL items in the order are fully filled
		// The function will move the order into "g_incompleted" IF:
		//		1. There are no NEXT STATION (IS nullptr) AND
		//		2. There are still items in the order are NOT fully filled
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation()const;
		void display(std::ostream& os)const;
		// received an order and put it at the end of the que
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}

#endif // !_SDDS_WORKSTATION_H


