#ifndef BWT_H_INCLUDED
#define BWT_H_INCLUDED

#include "useful.h"

///**** BWT ****///
/** Print the final BWT string of the string that is given in parameter and the number of runs **/
/* Takes a file name as parameter */
void BWT(std::string name);

///**** BWTstring ****///
/** Compute and return the BWT string **/
/* Takes the original string and the ordered array of unsigned integers as parameters */
std::string BWTstring(std::string data, std::vector<unsigned int>& orderTab);

///**** NumerofRuns ****///
/** Compute the number of runs **/
/* Takes the BWT string as parameter */
int numberOfRuns(std::string result);

#endif // BWT_H_INCLUDED
