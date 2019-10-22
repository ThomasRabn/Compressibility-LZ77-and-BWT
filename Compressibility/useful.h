#ifndef USEFUL_H_INCLUDED
#define USEFUL_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>

#define RADIX 256
#define SORT_THRESHOLD 0

///**** COMPARE ****///
struct Compare {
    std::string* data;
    Compare(std::string* dataparam) { data = dataparam; }

    bool operator () (unsigned int i, unsigned int j)   const { return data->substr(i) < data->substr(j); }
    bool operator () (std::string* a, std::string* b)   const { return *a < *b; }
};

void openFile(std::string name, std::string& data);
void MSDRadixSort(std::vector<unsigned int>& tab, std::string* data);

class Node {
    private:
        char value;
        std::unordered_map<char, Node*> next;
    public:
        Node(char newValue);
        Node* searchNode(char searchedValue);
        void addNode(char addValue);
};

class Tree {
    private:
        Node* root;
    public:
        Tree();
        void add(std::string addValue);
};


#endif // USEFUL_H_INCLUDED
