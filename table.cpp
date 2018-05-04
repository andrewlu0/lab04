#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include "table.h"

Table::Table(unsigned int max_entries){
	length = 2*max_entries;
	values = new std::vector<Entry>[length];
}

Table::Table(unsigned int entries, std::istream& input){
	length = 2*entries;	
	values = new std::vector<Entry>[length];
	std::string str;
	for (int i = 0; i < entries; i++){
		getline(input, str);
		std::string key = "";
		std::string data = "";
		int j = 0;
		while (str[j] != '\t')
			key += str[j++];
		j++;
		while (j < str.size())
			data += str[j++];
		put(Entry(stoi(key),data));
	}
}

void Table::put(unsigned int key, std::string data){
	std::vector<Entry>& check = values[hash(key)];
	for (int i = 0; i < check.size(); i++){
		if (check.at(i).get_key() == key){
			check.at(i).set_data(data);
			return;
		}
	}
	Entry e(key,data);
	check.push_back(e);
}

void Table::put(Entry e){
	std::vector<Entry>& check = values[hash(e.get_key())];
	for (int i = 0; i < check.size(); i++){
		if (check.at(i).get_key() == e.get_key()){
			check.at(i).set_data(e.get_data());
			return;
		}
	}
	check.push_back(e);
}

std::string Table::get(unsigned int key) const{
	std::string result = "";
	std::vector<Entry>& check = values[hash(key)];
	for (int i = 0; i < check.size(); i++){
		if (check.at(i).get_key() == key){
			result = values[hash(key)].at(i).get_data();
		}
	}
	return result;
}

bool Table::remove(unsigned int key){
	std::vector<Entry>& check = values[hash(key)];
	for (int i = 0; i < check.size(); i++){
		if (check.at(i).get_key() == key){
			check.erase(check.begin() + i);
			return true;
		}
	}
	return false;
}

int Table::hash(unsigned int key) const{
	return key % length;
}

std::ostream& operator << (std::ostream& out, const Table& t){
	std::vector<Entry> output;
	for (int i = 0; i < t.length; i++){
		if (t.values[i].size()){
			for (int j = 0; j < t.values[i].size(); j++)
				output.push_back(t.values[i].at(j));
		}
	}

	quickSort(output,0,output.size()-1);
	for (int i = 0; i < output.size(); i++){
		out  << output.at(i).get_key() << ": " << output.at(i).get_data() << std::endl;
	}
}

void quickSort(std::vector<Entry>& v, int low, int high){
	int i = low;
	int p = low;
	if (low < high){
		for (int j = low+1; j <= high; j++){
			if (v[j].get_key() <= v[low].get_key()){
				i++;
				Entry temp = v[i];
				v[i] = v[j];
				v[j] = temp;
			}
		}
 		Entry temp = v[low];
		v[low] = v[i];
		v[i] = temp;	
		quickSort(v,low,i-1);
		quickSort(v,i+1,high);
	}	
}


