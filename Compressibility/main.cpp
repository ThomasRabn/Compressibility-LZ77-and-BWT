#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

///**** COMPARE ****///
struct Compare {
    template<typename T>
        bool operator()(T* a, T* b) const { return *a < *b; }
    template<typename T>
        bool operator()(T a, T b) const { return a < b; }
};

void openFile(std::string name, std::string& data);
void fillSuffixTab(std::string data, std::vector<std::string*>& suffixTab);
std::string BWTstring(std::string data, std::vector<std::string*>& suffixTab);
int numberOfRuns(std::string result);

int main()
{
    std::string data;
    std::vector<std::string*> suffixTab;

    //openFile("files/aaa.txt", data);

    data = "abracadabra";
    data += '\0';

    fillSuffixTab(data, suffixTab);

    std::sort(suffixTab.begin(), suffixTab.end(), Compare());

    /*for(auto it : suffixTab) {
        std::cout << *it << std::endl;
    }*/

    std::string resultBWT = BWTstring(data, suffixTab);

    std::cout << resultBWT << std::endl;
    std::cout << numberOfRuns(resultBWT);

    return 0;
}

void openFile(std::string name, std::string& data) {
    std::ifstream file{name};
    std::string temp;

    if(!file)   { std::cout << "Error, file cannot be opened" << std::endl; }

    /// We put all the text of the file in the string and add a '\0' char at the end
    else {
        while(getline(file, temp)) {
            data += temp;
        }
        data += '\0';
    }

    std::cout << data << std::endl;
}

void fillSuffixTab(std::string data, std::vector<std::string*>& suffixTab) {
    std::string temp;
    std::string* value;

    /*for(unsigned int i = data.size()-1; i < data.size(); i--) {
        value = new std::string;
        temp = data.substr(i);
        *value = temp;
        suffixTab.push_back(value);
    }*/

    for(unsigned int i = 0; i < data.size(); ++i) {
        value = new std::string;
        temp = data.substr(i);
        *value = temp;
        suffixTab.push_back(value);
    }
}

std::string BWTstring(std::string data, std::vector<std::string*>& suffixTab) {
    std::string result;
    for(const auto& it : suffixTab) {
        if((*it).size() == data.size())     { result += '\0'; }
        else                                { result += data[data.size()-(*it).size()-1]; }
    }
    return result;
}

int numberOfRuns(std::string result) {
    char lastchar;
    int number = 0;
    if(result.size() > 0)  { lastchar = result[0]; ++number; }

    for(unsigned int i = 0; i < result.size(); ++i) {
        if (result[i] != lastchar) {
            lastchar = result[i];
            if(result[i] != 0)      { ++number; }
        }
    }

    return number;
}
