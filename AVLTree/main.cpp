#include <iostream>
#include "avltree.h"
#include <sstream>
using namespace std;

int main() {
    short operationCount;
    std::cin >> operationCount;
    AVLTree GatorAVLTree;
    cin.ignore();
    while (operationCount > 0) {
        string currLine;
        getline(cin, currLine);
        istringstream lineStream(currLine);
        string command;
        lineStream >> command;
        if (command == "insert") {
            string name, ID;
            getline(lineStream, name, '"');
            getline(lineStream, name, '"');
            lineStream >> ws;
            getline(lineStream, ID);
            if (verName(name) && verID(ID))
                GatorAVLTree.insert(name, ID);
            else
                cout << "unsuccessful\n";
            operationCount--;
        }
        else if (command == "printPreorder") {
            GatorAVLTree.printPreorder();
            operationCount--;
        }
        else if (command == "remove") {
            string ID;
            lineStream >> ws;
            getline(lineStream, ID);
            if (verID(ID))
                GatorAVLTree.remove(ID);
            else
                cout << "unsuccessful\n";
            operationCount--;
        }
        else if (command == "printPostorder") {
            GatorAVLTree.printPostorder();
            operationCount--;
        }
        else if (command == "search") {
            string name_or_ID;
            lineStream >> ws;
            getline(lineStream, name_or_ID);
            if (name_or_ID.front() == '"' && name_or_ID.back() == '"')
                name_or_ID = name_or_ID.substr(1, name_or_ID.size() - 2);
            GatorAVLTree.search(name_or_ID);
            operationCount--;
        }
        else if (command == "removeInorder") {
            string str_n;
            int n;
            getline(lineStream, str_n);
            n = stoi(str_n);
            GatorAVLTree.removeInorder(n);
            operationCount--;
        }
        else if (command == "printLevelCount") {
            GatorAVLTree.printLevelCount();
            operationCount--;
        }
        else if (command == "printInorder") {
            GatorAVLTree.printInorder();
            operationCount--;
        }
        else {
            cout << "unsuccessful\n";
            operationCount--;
        }
    }
    return 0;
}