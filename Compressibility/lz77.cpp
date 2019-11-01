#include "lz77.h"

void lz77(std::string name) {
    std::string data;

    openFile(name, data);

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

    /// loop for all the characters
    while(i < data.size()-1) {

        bool found = 0; // Is set to true when we found a match

        if(data.size()-1 > i+16) {
            searchInMap(&data, 16, &suffix16, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        if (data.size()-1 > i+8 && !found) {
            searchInMap(&data, 8, &suffix8, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        if (data.size()-1 > i+4 && !found) {
            searchInMap(&data, 4, &suffix4, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        if (data.size()-1 > i+2 && !found) {
            searchInMap(&data, 2, &suffix2, found, i, j);
            if(found)   { insertSuffix(&data, &suffix1, &suffix2, &suffix4, &suffix8, &suffix16, j, i); }
        }

        if (data.size()-1 > i+1 && !found) {
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
        results++;
        i+=j;
    }

    std::cout << results;
}

void searchInMap(std::string* data, unsigned int mapNumber, std::unordered_map<std::string, std::set<unsigned int>>* suffix, bool& found, unsigned int& i, unsigned int& j) {
    unsigned int verif = 0, tempVerif = 0;
    auto it = suffix->find(data->substr(i, mapNumber));
    if(it != suffix->end()) {
        for(j = mapNumber; i+j < data->size(); ++j) {
            verif = 0;
            for(auto eachIndex : it->second) {
                tempVerif = verif;
                for(unsigned int k = j; k >= mapNumber; --k) {
                    if(eachIndex+k >= i || (*data)[i+k] != (*data)[eachIndex+k]) {
                        verif++;
                        break;
                    }
                }
                if(tempVerif == verif) break;
            }
            if(verif == it->second.size())  { found=1; break; }
        }
    }
}


void insertSuffix (std::string* data, std::unordered_map<std::string, std::set<unsigned int>>* suffix1,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix2,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix4,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix8,
                   std::unordered_map<std::string, std::set<unsigned int>>* suffix16, unsigned int& j, unsigned int& index)
{
    j++;
    //std::cout << data->substr(index, j) << std::endl;
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
