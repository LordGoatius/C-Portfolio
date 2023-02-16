#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
#include"LinkedListInterface.h"
#include"LinkedList.h"


#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

int countSpaces(const string& str) {
    int spaces = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') ++spaces;
    }
    return spaces;
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

    LinkedList<string> ll;
    string llCopyOutput = "";

    bool continueMenuLoop = true;
    while (continueMenuLoop) {
        string line;
        getline(in, line);
        istringstream iss(line);
        string userMenuChoice;
        iss >> userMenuChoice;

        if (userMenuChoice == "Clear") {
            ll.clear();
            out << "Clear OK" << endl;
        }
        else if (userMenuChoice == "Empty") {
            out << "Empty ";
            if (ll.empty()) {
                out << "true" << endl;
            } else {
                out << "false" << endl;
            }
        }
        else if (userMenuChoice == "Delete") {
            out << "Delete ";
            try {
                if (ll.empty()) throw 1;
                ll.pop_front();
                out << "OK" << endl;
            } catch (...) {
                out << "Empty!" << endl;
            }
        }
        else if (userMenuChoice == "First") {
            out << "First ";
            try {
                if (ll.empty()) throw 1;
                out << ll.front() << endl;
            } catch (...) {
                out << "Empty!" << endl;
            }
        }
        else if (userMenuChoice == "Insert") {
            string temp = "";
            for (int i = 0; i < countSpaces(line); ++i) {
                iss >> temp;
                ll.push_front(temp);
            }
            out << line << endl;
        }
        else if (userMenuChoice == "PrintList") {
            out << "PrintList ";
            if (ll.empty() == false)
                out << ll.toString() << endl;
            else
                out << "Empty!" << endl;
        }
        else if (userMenuChoice == "Remove") {
            string temp = "";
            iss >> temp;
            try {
                ll.remove(temp);
                out << line << endl;
            }
            catch (...) {
                out << "RM ERROR" << endl;
            }
        }
        else if (userMenuChoice == "Reverse") {
            out << "Reverse ";
            try {
                if (ll.empty()) throw 1;
                ll.reverse();
                out << "OK" << endl;
            } catch (...) {
                out << "Empty!" << endl;
            }
        }
        else if (userMenuChoice == "Size") {
            out << "Size " << ll.size() << endl;
        }
        else if (userMenuChoice == "Copy") {
            LinkedList<string> llCopy = ll;
            llCopyOutput = llCopy.toString();
            out << "Copy OK" << endl;
        }
        else if (userMenuChoice == "PrintCopy") {
            out << "PrintCopy ";
            if (llCopyOutput == "") {
                out << "Empty!" << endl;
            } else
                out << llCopyOutput << endl;
        }
        else {
            continueMenuLoop = false;
        }
    }
	return 0;
}