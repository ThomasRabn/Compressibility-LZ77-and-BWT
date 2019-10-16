#ifndef BWT_H_INCLUDED
#define BWT_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#define RADIX 256
#define SORT_THRESHOLD 0

void BWT(std::string name);
std::string BWTstring(std::string data, std::vector<unsigned int>& orderTab);
int numberOfRuns(std::string result);

///**** COMPARE ****///
struct Compare {
    std::string* data;
    Compare(std::string* dataparam) { data = dataparam; }

    bool operator () (unsigned int i, unsigned int j)   const { return data->substr(i) < data->substr(j); }
    bool operator () (std::string* a, std::string* b)   const { return *a < *b; }
};

#endif // BWT_H_INCLUDED
