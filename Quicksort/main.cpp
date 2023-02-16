#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>

#include"QuickSort.hpp"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int findChars(string toParse) {
    toParse = toParse.substr(11, toParse.size() - 11);
    istringstream iss = istringstream(toParse);
    int count = 0;
    int dummy = 0;
    while (iss >> dummy) {
        count++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    VS_MEM_CHECK
        //intalize command line args
        if (argc < 3) {
            cerr << "Please provide name of input and output files";
            return 1;
        }

    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }

    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out) {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
        return 3;
    }

    QuickSort<int>* qs = NULL;

    bool continueMenuLoop = true;
    while (continueMenuLoop) {
        string line;
        getline(in, line);
        istringstream iss(line);
        string userMenuChoice;
        iss >> userMenuChoice;

        if (userMenuChoice == "QuickSort") {
            int capacity;
            iss >> capacity;
            if (qs != NULL) delete qs;
            qs = new QuickSort<int>(capacity);
            out << line << " OK" << endl;
            
        }
        else if (userMenuChoice == "AddToArray") {
            int val = 0;
            int count = findChars(line) - 1;
            out << "AddToArray ";
            while (iss >> val) {
                --count;
                qs->addElement(val);
                out << val;
                if (count >= 0) out << ",";
                
            }
            out << " OK" << endl;
        }
        else if (userMenuChoice == "Capacity") {
            out << line << " " << qs->capacity() << endl;
        }
        else if (userMenuChoice == "Clear") {
            qs->clear();
            out << "Clear OK" << endl;
        }
        else if (userMenuChoice == "Size") {
            out << line << " " << qs->size() << endl;
        }
        else if (userMenuChoice == "Sort") {
            int left;
            int right;
            iss >> left;
            iss >> right;
            qs->comparison = 0;
            qs->exchanges = 0;
            qs->sort(left, right);
            out << "Sort " << left << "," << right << " OK" << endl;
        }
        else if (userMenuChoice == "SortAll") {
            qs->sortAll();
            out << line << " OK" << endl;
        }
        else if (userMenuChoice == "MedianOfThree") {
            int left;
            int right;
            iss >> left;
            iss >> right;
            int mid = qs->medianOfThree(left, right);
            out << "MedianOfThree " << left << "," << right << " = " << mid << endl;
        }
        else if (userMenuChoice == "Partition") {
            int left;
            int right;
            int pivot;
            iss >> left;
            iss >> right;
            iss >> pivot;
            int part = qs->partition(left, right, pivot);
            out << "Partition " << left << "," << right << "," << pivot << " = " << part << endl;
        } 
        else if (userMenuChoice == "PrintArray") {
            out << line << " " << qs->toString() << endl;
        }
        else if (userMenuChoice == "Stats") {
            out << line << " " << qs->comparison << "," << qs->exchanges << endl;
        }
        else {
            continueMenuLoop = false;
        }
    }

    delete qs;

    return 0;
}