#include "lz77.h"

///**** LZ77 ****///
/** Compute and print the number runs for LZ77 **/
/* Takes a file name as parameter */
void lz77(std::string name) {
    std::string data;
    openFile(name, data);

    auto t_start = std::chrono::high_resolution_clock::now();

    // We create 5 differents hash tables that will only store the suffixes of 1 length (1 cahracter, 2 characters, 4, 8 or 16) //
    std::unordered_map<std::string, std::set<unsigned int>> suffix1;
    std::unordered_map<std::string, std::set<unsigned int>> suffix2;
    std::unordered_map<std::string, std::set<unsigned int>> suffix4;
    std::unordered_map<std::string, std::set<unsigned int>> suffix8;
    std::unordered_map<std::string, std::set<unsigned int>> suffix16;

    unsigned int i = 0;
    unsigned int j = 1;
    unsigned int results = 0;

    /*data = "abracadabra";
    data += '\0';*/

    /// loop for all the characters ///
    while(i < data.size()-1) {

        bool found = 0; // Is set to true when we find a match

        /// We start by searching the next 16 characters (if the substring is greater that 16 characters) ///
        /* If we find it we add it in our suffix list */
        if(data.size()-1 > i+16) {
            searchInMap(&data, 16, &suffix16, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        /// We search the next 8 characters if the 16 haven't been found (and the substring is longer than 8 characters ///
        if (data.size()-1 > i+8 && !found) {
            searchInMap(&data, 8, &suffix8, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        /// We search the next 4 characters ///
        if (data.size()-1 > i+4 && !found) {
            searchInMap(&data, 4, &suffix4, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        /// We search the next 2 characters ///
        if (data.size()-1 > i+2 && !found) {
            searchInMap(&data, 2, &suffix2, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        /// Special case if we haven't found any of the above ///
        if (data.size()-1 > i+1 && !found) {
            /// We search the next letter. If we find it we add the next 2, else we only add 1 letter ///
            auto it = suffix1.find(data.substr(i, 1));
            if(it != suffix1.end()) {
                j=1;
                insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i);
            }
            else {
                j=0;
                insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i);
            }
        }
        /// After 1 loop we increase the results and change i to its new value ///
        results++;
        i+=j;
    }

    std::cout << std::endl << results << std::endl << std::endl;

    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::endl << "       LZ77 was : " << NUM_mSEC/1000 << " s long" << std::endl;
}


///**** SearchInMap ****///
/** Search a substring of a precised length in a precised map and change values depending of the results **/
/* Takes a pointer to a string, a mapNumber (length of the word in the map), a map, a found boolean, an index named i, and finally a final length called j) */
void searchInMap(std::string* data, unsigned int mapNumber, std::unordered_map<std::string, std::set<unsigned int>>* suffix, bool& found, unsigned int& i, unsigned int& j) {
    unsigned int verif = 0, tempVerif = 0;

    // We search the substring strating at index i and of mapNumber length in the map //
    auto it = suffix->find(data->substr(i, mapNumber));

    // If we find it we enter the condition //
    if(it != suffix->end()) {
        // For all j from mapNumber to data->size-i-1 //
        for(j = mapNumber; i+j < data->size(); ++j) {
            verif = 0;
            // We run through each occurrence of the word we found in the map //
            for(auto eachIndex : it->second) {
                // We store the value of verif //
                tempVerif = verif;
                // We run through all the letters, if one is different we add 1 to verif and we go out of the loop //
                for(unsigned int k = j; k >= mapNumber; --k) {
                    if(eachIndex+k >= i || (*data)[i+k] != (*data)[eachIndex+k]) {
                        verif++;
                        break;
                    }
                }
                // If we found a word which is the same as the previous one, we go out of the loop and go to the next character //
                if(tempVerif == verif) break;
            }
            // If all the word have been verified, we set found to true and we break //
            if(verif == it->second.size())  { found=1; break; }
        }
    }
}

///**** InsertSuffix ****///
/** Add every new suffixes (from 1 to 16) in the maps **/
/* Takes a pointer to the original string, the 5 maps (from 1 character to 16), the length of the word we add and the index of the first letter of t he word we add */
void insertSuffix (std::string* data, std::unordered_map<std::string, std::set<unsigned int>>* suffix1,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix2,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix4,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix8,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix16, unsigned int& j, unsigned int& index)
{
    // We add 1 to j because of how substr() works
    j++;

    /* If uncommented we can see each substring added */
    //std::cout << data->substr(index, j) << std::endl;

    // As we only store up to 16 characters, we can start the insertion at index-15 but we have to verify that index is greater than 15 //
    /** Everything is then added in each map **/
    if(index > 15) {
        for(unsigned int i = index - 15; i < j+index; ++i) {
            if(j+index-i >= 16) { (*suffix16)[data->substr(i, 16)].insert(i); }
            if(j+index-i >= 8)  { (*suffix8)[data->substr(i, 8)].insert(i); }
            if(j+index-i >= 4)  { (*suffix4)[data->substr(i, 4)].insert(i); }
            if(j+index-i >= 2)  { (*suffix2)[data->substr(i, 2)].insert(i); }
            if(i >= index)      { (*suffix1)[data->substr(i, 1)].insert(i); }
        }
    }
    else {
        for(unsigned int i = 0; i < j+index; ++i) {
            if(j+index-i >= 16) { (*suffix16)[data->substr(i, 16)].insert(i); }
            if(j+index-i >= 8)  { (*suffix8)[data->substr(i, 8)].insert(i); }
            if(j+index-i >= 4)  { (*suffix4)[data->substr(i, 4)].insert(i); }
            if(j+index-i >= 2)  { (*suffix2)[data->substr(i, 2)].insert(i); }
            if(i >= index)      { (*suffix1)[data->substr(i, 1)].insert(i); }
        }
    }
}
