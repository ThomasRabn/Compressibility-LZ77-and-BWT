#include "useful.h"

///**** OpenFile ****///
/** Store the content of a file in a string **/
/* Takes a file name (as a string) and a string to fill as parameters */
int openFile(std::string name, std::string& data) {
    std::ifstream file{name};
    std::string temp;

    if(!file)   { std::cout << "Error, file cannot be opened" << std::endl; return 1; }

    /// We put all the text of the file in the string and add a '\0' char at the end
    else {
        while(getline(file, temp)) {
            data += temp;
        }
        data += '\0';
        return 0;
    }
}

///**** ChangeFile ****///
/** Ask the name of a text file and set it to the current file **/
/* Takes a file name (as a reference to a string) to change it */
void changeFile(std::string& name) {
    std::string temp;
    std::cout << std::endl << "What is the name of your file ? (make sure that it is in the \"files\" folder)" << std::endl << ">> ";
    std::cin >> temp;
    name = "files/" + temp + ".txt";
}


///**** METHODS USEFUL FOR RADIX SORTING ****///

short int getByte(std::string* elem, unsigned int i) {
	if (elem->size() > i)    { return (*elem)[i]; }
	else return -1;
}

///**** MSD Radix Sort ****//
/** Recursive version was overflowing so I tried to implement a iterative version but it is slower than the recursive version (but better than std::sort) **/
/* Takes an array of unsigned int (which are indexes of the string) and a pointer to the original string as parameters */
void MSDRadixSort(std::vector<unsigned int>& tab, std::string* data) {
    unsigned int low, high, currentDigit;
    std::queue<unsigned int> startPoint, endPoint, digit;
    std::vector<unsigned int> tabAux(tab.size());

    startPoint.push(0);
    endPoint.push(data->size());
    digit.push(0);

    while(!(digit.empty())) {
        low = startPoint.front();
        high = endPoint.front();
        currentDigit = digit.front();

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
