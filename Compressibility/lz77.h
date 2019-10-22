#ifndef LZ77_H_INCLUDED
#define LZ77_H_INCLUDED

#include "useful.h"

void lz77(std::string name);
void insertSuix (std::string data, std::unordered_set<std::string>& suix, unsigned int j);

#endif // LZ77_H_INCLUDED
