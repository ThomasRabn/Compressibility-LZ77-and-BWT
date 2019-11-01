#ifndef LZ77_H_INCLUDED
#define LZ77_H_INCLUDED

#include "useful.h"

void lz77(std::string name);

void searchInMap(std::string* data, unsigned int mapNumber, std::unordered_map<std::string, std::set<unsigned int>>* suffix, bool& found, unsigned int& i, unsigned int& j);

void insertSuffix (std::string* data, std::unordered_map<std::string, std::set<unsigned int>>* suffix1,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix2,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix4,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix8,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix16, unsigned int& j, unsigned int& index);

#endif // LZ77_H_INCLUDED
