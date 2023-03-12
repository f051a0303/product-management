// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 29-06-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef _SDDS_STATION_H
#define _SDDS_STATION_H

#include <string>
#include <iostream>
#include <iomanip>
#include "Utilities.h"

namespace sdds {
	class Station {
		int m_id{};
		std::string m_item{};
		std::string m_description{};
		size_t m_serialNo{};
		size_t m_itemCnt{};
		static size_t m_widthField;
		static int id_generator;
	public:
		Station(const std::string& str);

		const std::string& getItemName() const;

		size_t getNextSerialNumber();

		size_t getQuantity() const;

		void updateQuantity();

		void display(std::ostream& os, bool full) const;


	};



}

#endif //!_SDDS_STATION_H