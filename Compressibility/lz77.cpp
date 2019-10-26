#include "lz77.h"

void lz77(std::string name) {
    //Tree suffixTree;

    std::string data;

    openFile(name, data);

    std::unordered_set<std::string> suffix;
    std::unordered_map<std::string, std::vector<unsigned int>> suffix1;
    std::unordered_map<std::string, std::vector<unsigned int>> suffix2;
    std::unordered_map<std::string, std::vector<unsigned int>> suffix4;
    std::unordered_map<std::string, std::vector<unsigned int>> suffix8;
    std::unordered_map<std::string, std::vector<unsigned int>> suffix16;

    unsigned int results = 0;

    /*data = "tobeornottobe";
    data += '\0';*/

    std::string subdata;

    /// loop for all the characters
    for(unsigned int i = 0; i < data.size()-1; ++i) {
        /// Loop starting with the i character and while we are not at the end and we haven't find a substring that doesn't match
        /*std::cout << std::endl << std::endl << std::endl << std::endl << "SUFFIX 1" << std::endl;
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
        std::cout << "FIN SUFFIX 4" << std::endl;

        std::cout << "SUFFIX 8" << std::endl;
        for(auto it : suffix8) {
            std::cout << it.first <<std::endl;
        }
        std::cout << "FIN SUFFIX 8" << std::endl;

        std::cout << "SUFFIX 16" << std::endl;
        for(auto it : suffix16) {
            std::cout << it.first <<std::endl;
            for(int i=0;i<it.second.size();i++)
                std::cout<<" "<<it.second[i];
            std::cout<<std::endl;
        }
        std::cout << "FIN SUFFIX 16" << std::endl << std::endl << std::endl << std::endl;*/

        for(unsigned int length = 1; length < data.size()-i+1; length++) {

            if(length >= 16) {
                bool verif = 0;
                subdata = data.substr(i, 16);
                auto it16 = suffix16.find(subdata);

                subdata = data.substr(i, length);

                if(it16 == suffix16.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                else if(length > 16) {
                    for(unsigned int k = 0; k < it16->second.size(); ++k) {
                        if(it16->second[k]+length-1 < i && data[it16->second[k]+length-1] == data[i+length-1]) { verif = 1; break; }
                    }
                    if(!verif) { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                }
            }


            else if(length >= 8) {

                bool verif = 0;
                subdata = data.substr(i, 8);
                auto it8 = suffix8.find(subdata);

                subdata = data.substr(i, length);

                if(it8 == suffix8.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                else if(length > 8) {
                    for(unsigned int k = 0; k < it8->second.size(); ++k) {
                        if(it8->second[k]+length-1 < i && data[it8->second[k]+length-1] == data[i+length-1]) { verif = 1; break; }
                    }
                    if(!verif) { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                }
            }

            else if(length >= 4) {
                bool verif = 0;
                subdata = data.substr(i, 4);
                auto it4 = suffix4.find(subdata);

                subdata = data.substr(i, length);

                if(it4 == suffix4.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                else if(length > 4) {
                    for(unsigned int k = 0; k < it4->second.size(); ++k) {
                        if(it4->second[k]+length-1 < i && data[it4->second[k]+length-1] == data[i+length-1]) { verif = 1; break; }
                    }
                    if(!verif) { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                }
            }

            else if(length >= 2) {
                bool verif = 0;
                subdata = data.substr(i, 2);
                auto it2 = suffix2.find(subdata);

                subdata = data.substr(i, length);

                if(it2 == suffix2.end())    { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                else if(length > 2) {
                    for(unsigned int k = 0; k < it2->second.size(); ++k) {
                        if(it2->second[k]+length-1 < i && data[it2->second[k]+length-1] == data[i+length-1]) { verif = 1; }
                    }
                    if(!verif){ insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
                }
            }

            else if(length == 1) {
                subdata = data[i];
                auto it = suffix1.find(subdata);
                if(it == suffix1.end())     { insertSuffix(data, suffix1, suffix2, suffix4, suffix8, suffix16, length, i); results++; i+=length-1; break; }
            }

            /*if(i+length == data.size()-1) {
                std::cout << "In last";
                results++;
                std::cout << data.substr(i) << std::endl;
                i+=length;
            }*/
        }
        //std::cout << subdata << std::endl;

    }

    std::cout << results;
}

void insertSuffix (std::string data, std::unordered_map<std::string, std::vector<unsigned int>>& suffix1,
                   std::unordered_map<std::string, std::vector<unsigned int>>& suffix2,
                   std::unordered_map<std::string, std::vector<unsigned int>>& suffix4,
                   std::unordered_map<std::string, std::vector<unsigned int>>& suffix8,
                   std::unordered_map<std::string, std::vector<unsigned int>>& suffix16, unsigned int j, unsigned int index)
{
    if(index > 15) {
        for(unsigned int i = index-15; i < j+index; ++i) {
            if(j+index-i >= 16) { suffix16[data.substr(i, 16)].push_back(i); } //suffix16.insert({data.substr(i, 16), i}); }
            if(j+index-i >= 8 && i >= index-7)  { suffix8[data.substr(i, 8)].push_back(i); } //suffix8.insert ({data.substr(i, 8), i});  }
            if(j+index-i >= 4 && i >= index-7)  { suffix4[data.substr(i, 4)].push_back(i); } //suffix4.insert ({data.substr(i, 4), i});  }
            if(j+index-i >= 2 && i >= index-7)  { suffix2[data.substr(i, 2)].push_back(i); } //suffix2.insert ({data.substr(i, 2), i});  }
            suffix1[data.substr(i, 1 && i >= index)].push_back(index); //suffix1.insert({data.substr(i, 1), i});
        }
    }
    else {
        for(unsigned int i = 0; i < j+index; ++i) {
            if(j+index-i >= 16) { suffix16[data.substr(i, 16)].push_back(i); } //suffix16.insert({data.substr(i, 16), i}); }
            if(j+index-i >= 8)  { suffix8[data.substr(i, 8)].push_back(i); } //suffix8.insert ({data.substr(i, 8), i});  }
            if(j+index-i >= 4)  { suffix4[data.substr(i, 4)].push_back(i); } //suffix4.insert ({data.substr(i, 4), i});  }
            if(j+index-i >= 2)  { suffix2[data.substr(i, 2)].push_back(i); } //suffix2.insert ({data.substr(i, 2), i});  }
            suffix1[data.substr(i, 1)].push_back(index); //suffix1.insert({data.substr(i, 1), i});
        }
    }
}
