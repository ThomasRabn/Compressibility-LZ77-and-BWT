#include "bwt.h"


void BWT(std::string name) {
    std::string data;
    openFile(name, data);

    /*data = "abracadabra";
    data += '\0';*/

    std::vector<unsigned int> orderTab;
    for(size_t i = 0; i < data.size(); ++i) {
        orderTab.push_back(i);
    }
    std::cout << "Starting to sort..." << std::endl;
    //std::sort(orderTab.begin(), orderTab.end(), Compare(&data));
    MSDRadixSort(orderTab, &data);

    for(unsigned int i = 300000; i < orderTab.size(); ++i) {
        std::cout << data[orderTab[i]] << std::endl;
    }

    std::string resultBWT = BWTstring(data, orderTab);

    std::cout << resultBWT << std::endl;
    std::cout << numberOfRuns(resultBWT);
}

std::string BWTstring(std::string data, std::vector<unsigned int>& orderTab) {
    std::string result;
    for(const auto& it : orderTab) {
        if(it == 0)                         { result += '\0'; }
        else                                { result += data[it-1]; }
    }
    return result;
}

int numberOfRuns(std::string result) {
    char lastchar;
    int number = 0;

    if(result.size() > 0)  { lastchar = result[0]; ++number; }

    for(size_t i = 1; i < result.size(); ++i) {
        if (result[i] != lastchar) {
            lastchar = result[i];
            if(result[i] != 0)      { ++number; }
        }
    }

    return number;
}
