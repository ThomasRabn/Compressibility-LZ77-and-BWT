#include "useful.h"

Node::Node(char newValue)
    : value{newValue}
{}

Node* Node::searchNode(char searchedValue) {
    auto it = next.find(searchedValue);

    if(it != next.end())    { return it->second; }
    else                    { return nullptr; }
}

void Node::addNode(char addValue) {
    Node* newNext = new Node(addValue);
    next.insert({addValue, newNext});
}

void Tree::add(std::string addValue) {
    Node* actualNode = root;
    for(unsigned int i = 0; i < addValue.size(); ++i) {
        if(actualNode->searchNode(addValue[i]) == nullptr) {
            actualNode->addNode(addValue[i]);
        }
    }
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



short int getByte(std::string* elem, unsigned int i) {
	if (elem->size() > i)    { return (*elem)[i]; }
	else return -1;
}


///**** MSD Radix Sort ****//
/// Recursive version was overflowing so I tried to implement a iterative version but it seems really slow ///

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

        std::cout << currentDigit << " ";

        startPoint.pop();
        endPoint.pop();
        digit.pop();

        if ((high-low) < SORT_THRESHOLD) {
            std::sort(tab.begin()+low, tab.begin()+high, Compare(data));
        }
        else {
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
        }
    }
}
