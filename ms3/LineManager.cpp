// Name: Chi Ming Lai
// Seneca Student ID: 158400200
// Seneca email: cmlai@myseneca.ca
// Date of completion: 22-07-2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"

namespace sdds {
	
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		Utilities::setDelimiter('|');
		sdds::Utilities extractor;
		bool more;
		size_t next_pos{ 0 };
		std::string line{}, workStation{}, nextWorkStation{};

		std::ifstream f(file);

		if (!f) {
			throw "Error to open file";
		}

		try {
			while (std::getline(f, line)) {
				workStation = extractor.extractToken(line, next_pos, more);
				auto it = std::find_if(stations.begin(), stations.end(), [&workStation](Workstation* ws) {return workStation == ws->getItemName(); });
				if (it != stations.end()) { // std::find_if will return Iterator to the last element if no such element is found
					m_activeLine.push_back(*it); // dereference the iterator to return the pointer of a workStation object 
				}
				else {
					std::string err("workstation [" + workStation + "] not found");
					throw err;
				}
				if (more) {
					nextWorkStation = extractor.extractToken(line, next_pos, more);
					auto it = std::find_if(stations.begin(), stations.end(), [&nextWorkStation](Workstation* ws) {return nextWorkStation == ws->getItemName(); }); 
					if (it != stations.end()) { // std::find_if will return Iterator to the last element if no such element is found
						m_activeLine.back()->setNextStation(*it); // dereference the iterator to return the pointer of a workStation object 
					}
					else {
						std::string err("workstation [" + nextWorkStation + "] not found");
						throw err;
					}
				}
				next_pos = 0;
			}
			f.close();
		}
		catch (const std::string& err) {
			throw err;
		}
		catch (...) {
			throw "error on extracting workstation data from file";
		}

		// find which is the first workstation in the assembly line
		// Logic: Compare each workstation pointer to every m_pNextStation pointer, we know if the workstation didn't appear in any m_pNextStation, it will be the first station in the assembly line
		auto it = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws) {
			bool notFirst;
			notFirst = std::any_of(m_activeLine.begin(), m_activeLine.end(), [&ws](Workstation* innerWs) {
				return ws == innerWs->getNextStation();
				}); // if notFirst is false, that means no nextWs is found in ws;
			return !notFirst;
			});

		if (it != m_activeLine.end()) {
			m_firstStation = *it;
		}
		else {
			std::string err("Can't determine first workstation");
			throw err;
		}
		
		m_cntCustomerOrder = g_pending.size();
	}

	void LineManager::display(std::ostream& os)const {
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* ws) {ws->display(os); });
	}


	void LineManager::reorderStations() {
		try {
			m_activeLine[0] = m_firstStation;
			for (auto i = 1u; i < m_activeLine.size(); ++i) {
				if (m_activeLine[i - 1]->getNextStation()) {
					m_activeLine[i] = m_activeLine[i - 1]->getNextStation();
				}
			}
		}
		catch (...) {
			std::string err("Error occur in reorderStations");
			throw err;
		}
	}


	bool LineManager::run(std::ostream& os) {
		try {
			static size_t count{};
			os << "Line Manager Iteration: " << ++count << std::endl;
			try {
				if (!g_pending.empty()) {	// prevent read access violation error because accessing nullptr;
					*m_firstStation += std::move(g_pending.front()); // move one customerOrder to the first station each time when this function is called
					g_pending.pop_front();
				}
			}
			catch (...) {
				std::string err("Error in adding order from pending");
				throw err;
			}

			try {
				for (auto& i : m_activeLine) {
					i->fill(os);
				}
			}
			catch (...) {
				std::string err("Error in filling order");
				throw err;
			}

			try {
				for (auto& i : m_activeLine) {
					i->attemptToMoveOrder();

				}
			}
			catch (...) {
				std::string err("Error in attempt to move order");
				throw err;
			}

			return m_cntCustomerOrder == g_completed.size() + g_incomplete.size(); // all orders are either completed or incomplete in the end, so it will be equals to the total number of CustomerOrders
		}
		catch (std::string& e) {
			throw e;
		}
		catch (...) {
			std::string err("Error in running assembly line");
			throw err;
		}
	}
}