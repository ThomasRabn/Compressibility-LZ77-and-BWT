#ifndef USEFUL_H_INCLUDED
#define USEFUL_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <queue>
#include <chrono>

#define RADIX 256
#define SORT_THRESHOLD 200
#define NUM_mSEC std::chrono::duration<double, std::milli>(t_end - t_start).count()

///**** COMPARE ****///
struct Compare {
    std::string* data;
    Compare(std::string* dataparam) { data = dataparam; }

    /* We tried to use .susbtr() function at first but it makes the program really slow (more than 1 hours for bibleline), so we made our own */
    bool operator () (unsigned int i, unsigned int j) const {
        unsigned int k = 0;
        while(true) {
            if((*data)[i+k] != (*data)[j+k])    { return (*data)[i+k] < (*data)[j+k]; }
            k++;
        }
    }
};


///**** OpenFile ****///
/** Store the content of a file in a string **/
/* Takes a file name (as a string) and a string to fill as parameters */
int openFile(std::string name, std::string& data);


///**** ChangeFile ****///
/** Ask the name of a text file and set it to the current file **/
/* Takes a file name (as a reference to a string) to change it */
void changeFile(std::string& name);


///**** MSD Radix Sort ****//
/** Recursive version was overflowing so I tried to implement a iterative version but it is slower than the recursive version (but better than std::sort) **/
/* Takes an array of unsigned int (which are indexes of the string) and a pointer to the original string as parameters */
void MSDRadixSort(std::vector<unsigned int>& tab, std::string* data);

#endif // USEFUL_H_INCLUDED
