// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 22-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef _SDDS_LINE_MANAGER_H
#define _SDDS_LINE_MANAGER_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <utility>
#include "Workstation.h"
#include "Utilities.h"

namespace sdds {
	class LineManager {
		std::vector<Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);


		void display(std::ostream& os)const;
	};


}

#endif // !_SDDS_LINE_MANAGER_H
