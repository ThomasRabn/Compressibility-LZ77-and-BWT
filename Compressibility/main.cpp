#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#define RADIX 256
#define SORT_THRESHOLD 75000

///**** COMPARE ****///
struct Compare {
    std::string* data;
    Compare(std::string* dataparam) { data = dataparam; }
    bool operator () (unsigned int i, unsigned int j) { return data->substr(i) < data->substr(j); }
};

void BWT(std::string name);
void openFile(std::string name, std::string& data);
std::string BWTstring(std::string data, std::vector<unsigned int>& orderTab);
int numberOfRuns(std::string result);

template<typename T> void MSDRadixSort(std::vector<T>& tab, std::string* data);
template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit, std::string* data);


int main()
{
    BWT("files/aaa.txt");
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
}

void BWT(std::string name) {
    std::string data;
    openFile(name, data);

    //data = "abracadabra";
    //data += '\0';

    std::vector<unsigned int> orderTab;
    for(size_t i = 0; i < data.size(); ++i) {
        orderTab.push_back(i);
    }
    std::cout << "Starting to sort..." << std::endl;
    std::sort(orderTab.begin(), orderTab.end(), Compare(&data));
    //MSDRadixSort(orderTab, &data);

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

    for(size_t i = 0; i < result.size(); ++i) {
        if (result[i] != lastchar) {
            lastchar = result[i];
            if(result[i] != 0)      { ++number; }
        }
    }

    return number;
}

short int getByte(std::string* elem, unsigned int i) {
	if (elem->size() > i)    { return (*elem)[i]; }
	else return -1;
}

///**** MSD Radix Sort ****//

template<typename T> void MSDRadixSort(std::vector<T>& tab, std::string* data) {
	std::vector<T> tabAux(tab.size());
	MSDRadixSort(tab, tabAux, 0, tab.size(), 0, data);
}

template<typename T> void MSDRadixSort(std::vector<T>& tab, std::vector<T>& tabAux, int low, int high, int digit, std::string* data) {
    /// If the two bounds are too close to each other we sort it using the std::sort function
    if ((high-low) < SORT_THRESHOLD) {
        std::sort(tab.begin()+low, tab.begin()+high, Compare(data));
    }
    else {
        std::vector<int> counter(RADIX+2);

        for (int i = low; i < high; ++i) {
            std::string dataText = data->substr(tab[i]);
            counter[getByte(&dataText, digit) + 2]++;
        }

        for (int r = 0; r < RADIX+1; ++r) {
            counter[r+1] += counter[r];
        }

        for (int i = low; i < high; ++i) {
            std::string dataText = data->substr(tab[i]);
            tabAux[counter[getByte(&dataText, digit)+1]++] = tab[i];
        }

        for (int i = low; i < high; ++i) {
            tab[i] = tabAux[i-low];
        }

        for(int r = 0; r < RADIX+1; ++r) {
            /// if there is many times the same letter we launch a sort for all of them
            if(counter[r] < counter[r+1])    MSDRadixSort(tab, tabAux, low+counter[r], low+counter[r+1], digit+1, data);
        }
    }
}
