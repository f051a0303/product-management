// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 29-06-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Station.h"

namespace sdds {
	// initialize the class variable to value 0;
	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;

	// 1-argument constructor
	Station::Station(const std::string& str) {
		sdds::Utilities extractor;
		size_t next_pos{ 0 };
		bool more;
		std::string extractedStr[4];
		int i = 0;
		do {
			if (i == 3) {
				if (m_widthField < extractor.getFieldWidth())
					m_widthField = extractor.getFieldWidth();
			}

			extractedStr[i] = extractor.extractToken(str, next_pos, more);
			++i;
		} while (more);
		if (i == 4) {
			m_item = extractedStr[0];
			m_serialNo = std::stoul(extractedStr[1]);
			m_itemCnt = std::stoul(extractedStr[2]);
			m_description = extractedStr[3];
		}

		m_id = ++id_generator;
	}

	const std::string& Station::getItemName() const {
		return m_item;
	}

	size_t Station::getNextSerialNumber() {
		size_t temp = m_serialNo;
		++m_serialNo;
		return temp;
	}

	size_t Station::getQuantity() const {
		return m_itemCnt;
	}

	void Station::updateQuantity() {
		if (m_itemCnt >= 1) {
			--m_itemCnt;
		}
	}

	void Station::display(std::ostream& os, bool full) const {
		using namespace std;

		os << setw(3) << setfill('0') << m_id << " | " << setw(m_widthField) << setfill(' ') << left << m_item << " | " << right << setw(6) << setfill('0') << m_serialNo << " | " << setfill(' ');

		if (!full) {
			os << endl;
		}
		else {
			os << setw(4) << right << m_itemCnt << " | " << m_description << endl;
		}

	}

}