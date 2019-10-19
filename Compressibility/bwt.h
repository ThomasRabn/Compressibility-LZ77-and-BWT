#ifndef BWT_H_INCLUDED
#define BWT_H_INCLUDED

#include "useful.h"

void BWT(std::string name);
std::string BWTstring(std::string data, std::vector<unsigned int>& orderTab);
int numberOfRuns(std::string result);

#endif // BWT_H_INCLUDED
