// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 25-06-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Utilities.h"

namespace sdds {

	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::size_t found = str.find(m_delimiter, next_pos);
		std::string str_copy{};

		if (found == next_pos) {
			more = false;
			throw std::string("Err: Delimiter found in next_pos: " + std::to_string(next_pos));
		}
		if (found != std::string::npos) {
			// copy the extracted token found
			str_copy = str.substr(next_pos, found - next_pos);
			// set the next_pos to one index after the delimiter
			next_pos = found + 1;
			// delimiter found means there are more string left behind;
			more = true;
		}
		else { // delimiter not found, no more string to extract
			str_copy = str.substr(next_pos, str.length() - next_pos);
			more = false;
		}

		if (m_widthField < str_copy.length()) {
			m_widthField = str_copy.length();
		}

		for (auto i = 0u; str_copy[i] == ' '; i++) {  // remove leading spaces
			str_copy.erase(i, 1);
			i--;
		}

		for (auto i = str_copy.length() - 1; str_copy[i] == ' '; i--) {// remove trailing spaces
			str_copy.erase(i, 1);
		}

		return str_copy;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}

}