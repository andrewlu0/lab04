//
//  table.h
//  S18 - Lab04
//
#ifndef table_h
#define table_h

#include "entry.h"
#include <vector>

void quickSort(std::vector<Entry>& v, int low, int high);

class Table
{
	public:
		Table (unsigned int max_entries = 100);
		Table (unsigned int entries, std::istream& input);
		void put (unsigned int key, std::string data);
		void put (Entry e);
		std::string get (unsigned int key) const;
		bool remove(unsigned int key);

		friend std::ostream& operator << (std::ostream& out, const Table& t);
	private:
		std::vector<Entry> *values;
		int hash(unsigned int key) const;
		int length;
};

#endif /* table_h */
