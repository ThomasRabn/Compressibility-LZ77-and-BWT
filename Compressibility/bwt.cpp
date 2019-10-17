#include "bwt.h"

void openFile(std::string name, std::string& data);

void MSDRadixSort(std::vector<unsigned int>& tab, std::string* data);

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

short int getByte(std::string* elem, unsigned int i) {
	if (elem->size() > i)    { return (*elem)[i]; }
	else return -1;
}

///**** MSD Radix Sort ****//

void MSDRadixSort(std::vector<unsigned int>& tab, std::string* data) {
    /// If the two bounds are too close to each other we sort it using the std::sort function
    unsigned int low, high, currentDigit;
    std::queue<unsigned int> startPoint, endPoint, digit;
    std::vector<unsigned int> tabAux(tab.size());

    startPoint.push(0);
    endPoint.push(data->size());
    digit.push(0);

    std::cout << data->size() << std::endl;

    while(!(digit.empty())) {
        low = startPoint.front();
        high = endPoint.front();
        currentDigit = digit.front();

        //std::cout << currentDigit << std::endl;

        startPoint.pop();
        endPoint.pop();
        digit.pop();

        /*if ((high-low) < SORT_THRESHOLD) {
            std::sort(tab.begin()+low, tab.begin()+high, Compare(data));
        }
        else {*/
            std::vector<int> counter(RADIX+2);

            for (unsigned int i = low; i < high; ++i) {
                counter[getByte(data, currentDigit+tab[i]) + 2]++;
            }

            for (unsigned int r = 0; r < RADIX+1; ++r) {
                counter[r+1] += counter[r];
            }

            for (unsigned int i = low; i < high; ++i) {
                tabAux[counter[getByte(data, currentDigit+tab[i])+1]++] = tab[i];
            }

            for (unsigned int i = low; i < high; ++i) {
                tab[i] = tabAux[i-low];
            }

            for(int r = 2; r < RADIX; ++r) {
                /// if there is many times the same letter we launch a sort for all of them
                if(counter[r] < counter[r+1]) {
                    startPoint.push(low+counter[r]);
                    endPoint.push(low+counter[r+1]);
                    digit.push(currentDigit+1);
                }

            }
        //}
    }
}


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

    for(int i = 300000; i < orderTab.size(); ++i) {
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
