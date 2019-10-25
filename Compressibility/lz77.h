#ifndef LZ77_H_INCLUDED
#define LZ77_H_INCLUDED

#include "useful.h"

void lz77(std::string name);

void insertSuffix (std::string data, std::unordered_map<std::string, unsigned int>& suffix1,
                   std::unordered_map<std::string, unsigned int>& suffix2,
                   std::unordered_map<std::string, unsigned int>& suffix4,
                   std::unordered_map<std::string, unsigned int>& suffix8,
                   std::unordered_map<std::string, unsigned int>& suffix16, unsigned int j, unsigned int index);

#endif // LZ77_H_INCLUDED
