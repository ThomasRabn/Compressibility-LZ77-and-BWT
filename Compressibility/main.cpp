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

    std::string str = BWTstring(data, suffixTab);

    std::cout << str;

    return 0;
}

void openFile(std::string name, std::string& data) {
    std::ifstream file{name};

    if(!file)   { std::cout << "Error, file cannot be opened" << std::endl; }

    /// We put all the text of the file in the string and add a '\0' char at the end
    else {
        while(!file.eof()) {
            file >> data;
        }
        data += '\0';
    }
}

void fillSuffixTab(std::string data, std::vector<std::string*>& suffixTab) {
    std::string temp;
    std::string* value;
    for(unsigned int i = 0; i < data.length(); ++i) {
        value = new std::string;
        temp = data.substr(i);
        *value = temp;
        suffixTab.push_back(value);
    }
    /*std::ofstream ofs{"aaasuffixes.txt"};
    for(auto it : suffixTab) {
        ofs << *it << std::endl;
    }
    std::cout << "end";*/
}

std::string BWTstring(std::string data, std::vector<std::string*>& suffixTab) {
    std::string result;
    for(const auto& it : suffixTab) {
        if((*it).length() == data.length())     { result += '\0'; }
        else                                    { result += data[data.length()-(*it).length()-1]; }
    }
    return result;
}
