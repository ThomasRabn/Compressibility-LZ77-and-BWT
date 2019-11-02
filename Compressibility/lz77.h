#ifndef LZ77_H_INCLUDED
#define LZ77_H_INCLUDED

#include "useful.h"

///**** LZ77 ****///
/** Compute and print the number runs for LZ77 **/
/* Takes a file name as parameter */
void lz77(std::string name);

///**** SearchInMap ****///
/** Search a substring of a precised length in a precised map and change values depending of the results **/
/* Takes a pointer to a string, a mapNumber (length of the word in the map), a map, a found boolean, an index named i, and finally a final length called j) */
void searchInMap(std::string* data, unsigned int mapNumber, std::unordered_map<std::string, std::set<unsigned int>>* suffix, bool& found, unsigned int& i, unsigned int& j);

///**** InsertSuffix ****///
/** Add every new suffixes (from 1 to 16) in the maps **/
/* Takes a pointer to the original string, the 5 maps (from 1 character to 16), the length of the word we add and the index of the first letter of t he word we add */
void insertSuffix (std::string* data, std::unordered_map<std::string, std::set<unsigned int>>* suffix1,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix2,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix4,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix8,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix16, unsigned int& j, unsigned int& index);

#endif // LZ77_H_INCLUDED
