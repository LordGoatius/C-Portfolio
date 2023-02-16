#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include "ExpressionManager.h"
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>

using namespace std;

int main(int argc, char* argv[]) {
    //hidden cm line args and VALGRIND
    VS_MEM_CHECK
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

    ExpressionManager* expression = NULL;

    bool continueMenuLoop = true;
    while (continueMenuLoop) { 

        string line;
        getline(in, line);
        istringstream iss(line);
        string userMenuChoice;
        iss >> userMenuChoice;

        if (userMenuChoice == "Expression:") {
            if (expression != NULL) {
                delete expression;
                out << endl;
            }
            string exp = line.substr(12, line.size() - 11);
            expression = new ExpressionManager(exp);
            out << "Expression: " << exp << endl;
        }
        else if (userMenuChoice == "Postfix:") {
            out << "Postfix: ";
            try {
                out << expression->postfix() << endl;
            }
            catch (string error) {
                out << error << endl;
            }
        }
        else if (userMenuChoice == "Prefix:") {
            out << "Prefix: ";
            try {
                out << expression->prefix() << endl;
            }
            catch (string error) {
                out << error << endl;
            }
        }
        else if (userMenuChoice == "Infix:") {
            out << "Infix: ";
            try {
                out << expression->infix() << endl;
            }
            catch (string error) {
                out << error << endl;
            }
        }
        else if (userMenuChoice == "Value:") {
            out << "Value: ";
            try {
                out << expression->value() << endl;
            }
            catch (string error) {
                out << error << endl;
            }
        }
        else {
            continueMenuLoop = false;
        }
    }

    delete expression;
}