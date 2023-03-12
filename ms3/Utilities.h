// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 25-06-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#ifndef _SDDS_UTILITIES_H
#define _SDDS_UTILITIES_H

#include<string>

namespace sdds {
	class Utilities {
		size_t m_widthField{ 1 };
		static char m_delimiter;
	public:
		void setFieldWidth(size_t newWidth);

		size_t getFieldWidth() const;

		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		//Class functions
		static void setDelimiter(char newDelimiter);

		static char getDelimiter();



	};


}

#endif //!_SDDS_UTILITIES_H