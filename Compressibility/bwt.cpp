#include "bwt.h"

///**** BWT ****///
/** Print the final BWT string of the string that is given in parameter and the number of runs **/
/* Takes a file name as parameter */
void BWT(std::string name) {
    std::string data;
    if(openFile(name, data) == 0) {

        /*data = "abracadabra";
        data += '\0';*/

        auto t_start = std::chrono::high_resolution_clock::now();

        // We fill a vector with number from 1 to data.size()-1 //
        std::vector<unsigned int> orderTab;
        for(size_t i = 0; i < data.size(); ++i) {
            orderTab.push_back(i);
        }

        // We sort the array //
        std::cout << std::endl << "Sorting..." << std::endl;
        MSDRadixSort(orderTab, &data);

        // We compute the string, we print it and we compute and print the number of runs //
        std::string resultBWT = BWTstring(data, orderTab);
        std::cout << resultBWT << std::endl << std::endl;
        std::cout << "Number of runs: " << numberOfRuns(resultBWT) << std::endl << std::endl;

        auto t_end = std::chrono::high_resolution_clock::now();

        std::cout << std::endl << "       BWT was : " << NUM_mSEC/1000 << " s long" << std::endl;
    }
}



///**** BWTstring ****///
/** Compute and return the BWT string **/
/* Takes the original string and the ordered array of unsigned integers as parameters */
std::string BWTstring(std::string data, std::vector<unsigned int>& orderTab) {
    std::string result;
    // For each number in the array we add the letter at the place number-1 of the original string. If the number is 0 we add '\0' //
    for(const auto& it : orderTab) {
        if(it == 0)                         { result += '\0'; }
        else                                { result += data[it-1]; }
    }
    return result;
}


///**** NumerofRuns ****///
/** Compute the number of runs **/
/* Takes the BWT string as parameter */
int numberOfRuns(std::string result) {
    char lastchar;
    int number = 0;

    // If the string isn't empty we initialize the first character and increment the number //
    if(result.size() > 0)  { lastchar = result[0]; if(result[0] != 0) {++number; } }

    // For all the other letters, we change lastchar if the new character is different. If it is different and the new isn't '\0', we increment the number //
    for(size_t i = 1; i < result.size(); ++i) {
        if (result[i] != lastchar) {
            lastchar = result[i];
            if(result[i] != 0)      { ++number; }
        }
    }

    return number;
}
