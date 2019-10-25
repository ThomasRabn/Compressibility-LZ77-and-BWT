#include "lz77.h"

void lz77(std::string name) {
    //Tree suffixTree;

    std::string data;

    //openFile(name, data);

    std::unordered_set<std::string> suffix;
    std::unordered_map<std::string, unsigned int> suffix1;
    std::unordered_map<std::string, unsigned int> suffix2;
    std::unordered_map<std::string, unsigned int> suffix4;
    std::unordered_map<std::string, unsigned int> suffix8;
    std::unordered_map<std::string, unsigned int> suffix16;

    unsigned int results = 0;

    data = "abracadabra";
    data += '\0';

    std::string subdata;

    /// loop for all the characters
    for(unsigned int i = 0; i < data.size()-1; ++i) {
        /// Loop starting with the i character and while we are not at the end and we haven't find a substring that doesn't match
        std::cout << std::endl << std::endl << std::endl << std::endl << "SUFFIX 1" << std::endl;
        for(auto it : suffix1) {
            std::cout << it.first <<std::endl;
        }
        std::cout << "FIN SUFFIX 1" << std::endl;

        std::cout << "SUFFIX 2" << std::endl;
        for(auto it : suffix2) {
            std::cout << it.first <<std::endl;
        }
        std::cout << "FIN SUFFIX 2" << std::endl;

        std::cout << "SUFFIX 4" << std::endl;
        for(auto it : suffix4) {
            std::cout << it.first <<std::endl;
        }
        std::cout << "FIN SUFFIX 4" << std::endl << std::endl << std::endl << std::endl;

        for(unsigned int length = 1; length < data.size()-i; length++) {
            subdata = data.substr(i, length);

            if(length == 16) {
                std::cout << "In 16 : ";
                auto it16 = suffix16.find(subdata);
                if(it16 == suffix16.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; std::cout << subdata << std::endl; break; }
            }


            else if(length == 8) {
                std::cout << "In 8 : ";
                auto it8 = suffix8.find(subdata);
                if(it8 == suffix8.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; std::cout << subdata << std::endl; break; }
            }

            else if(length == 4) {
                std::cout << "In 4 : ";
                auto it4 = suffix4.find(subdata);
                if(it4 == suffix4.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; std::cout << subdata << std::endl; break; }
            }

            else if(length == 2) {
                std::cout << "In 2 : ";
                auto it2 = suffix2.find(subdata);
                if(it2 == suffix2.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; std::cout << subdata << std::endl; break; }
            }

            else if(length == 1) {
                std::cout << "In 1 : ";
                auto it = suffix1.find(subdata);
                if(it == suffix1.end())     { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; std::cout << subdata << std::endl; break; }
            }

            if(i+length == data.size()-1) {
                results++;
                std::cout << data.substr(i) << std::endl;
                i+=length;
            }
        }
    }

    std::cout << results;
}

void insertSuffix (std::string data, std::unordered_map<std::string, unsigned int>& suffix1,
                   std::unordered_map<std::string, unsigned int>& suffix2,
                   std::unordered_map<std::string, unsigned int>& suffix4,
                   std::unordered_map<std::string, unsigned int>& suffix8,
                   std::unordered_map<std::string, unsigned int>& suffix16, unsigned int j, unsigned int index)
{
    for(unsigned int i = 0; i < j+index; ++i) {
        if(j+index-i >= 16) { suffix16.insert({data.substr(i, 16), i}); }
        if(j+index-i >= 8)  { suffix8.insert ({data.substr(i, 8), i});  }
        if(j+index-i >= 4)  { suffix4.insert ({data.substr(i, 4), i});  }
        if(j+index-i >= 2)  { suffix2.insert ({data.substr(i, 2), i});  }
        suffix1.insert({data.substr(i, 1), i});
    }
}
