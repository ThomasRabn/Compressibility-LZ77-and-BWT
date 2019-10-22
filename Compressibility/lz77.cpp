#include "lz77.h"

void lz77(std::string name) {
    //Tree suffixTree;

    std::string data;

    openFile(name, data);

    std::unordered_set<std::string> suix;
    unsigned int esults =0;

    //data = "abracadabra";
    //data += '\0';

    std::string subdata;

    for(unsigned int i = 0; i < data.size(); ++i) {
        for(unsigned int j = i; j < data.size(); ++j) {
            subdata = data.substr(i, j-i+1);
            auto it = suix.find(subdata);

            if(it == suix.end())    { insertSuix(data, suix, j); esults++; i=j; std::cout << subdata << std::endl; break; }
        }
    }

    std::cout << esults;
}

void insertSuix (std::string data, std::unordered_set<std::string>& suix, unsigned int j) {
    for(unsigned int i = 0; i < data.size(); ++i) {
        suix.insert(data.substr(i, j-i+1));
    }
}
