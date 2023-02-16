#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
#include<iostream>
#include<vector>

#include "Course.h"
#include "Csg.h"
#include "Cdh.h"
#include "Cr.h"
#include "Snap.h"

string parseInput(string input) {
    size_t i = input.find('(');
    if (input.find('(') == string::npos) return "";
    return input.substr(0, i);
}

Snap parseSnap(string input) {
    size_t i = input.find('(');
    size_t j = input.find(')');
    string to_parse = input.substr(i + 1, j - i -1);

    string first = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string second = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string third = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string fourth = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);
    
    return Snap(first, second, third, fourth);
}

Csg parseCsg(string input) {
    size_t i = input.find('(');
    size_t j = input.find(')');
    string to_parse = input.substr(i + 1, j - i - 1);

    string first = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string second = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string third = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    return Csg(first, second, third);
}

Cdh parseCdh(string input) {
    size_t i = input.find('(');
    size_t j = input.find(')');
    string to_parse = input.substr(i + 1, j - i - 1);

    string first = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string second = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string third = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    return Cdh(first, second, third);
}

Cr parseCr(string input) {
    size_t i = input.find('(');
    size_t j = input.find(')');
    string to_parse = input.substr(i + 1, j - i - 1);

    string first = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    string second = to_parse.substr(0, to_parse.find(','));
    to_parse = to_parse.substr(to_parse.find(',') + 1);

    return Cr(first, second);
}



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

    vector<Snap> snaps;
    vector<Csg> csgs;
    vector<Cdh> cdhs;
    vector<Cr> crs;

    bool err = false;
    bool continueMenuLoop = true;
    out << "Input Strings:" << endl;

    while (continueMenuLoop) {
        err = false;
        string line;
        getline(in, line);
        //istringstream iss(line);

        try {
            string userMenuChoice;
            userMenuChoice = parseInput(line);
            if (userMenuChoice != "snap" && userMenuChoice != "csg" && userMenuChoice != "cdh" && userMenuChoice != "cr" && userMenuChoice != "")
                throw 1;
        } catch (...) {
            out << "**Error: ";
            err = true;
        }

        string userMenuChoice;
        userMenuChoice = parseInput(line);
        out << line << endl;
        //iss >> userMenuChoice;

        if (userMenuChoice == "snap") {
            Snap snap = parseSnap(line);
            snaps.push_back(snap);
        }
        else if (userMenuChoice == "csg") {
            Csg csg = parseCsg(line);
            csgs.push_back(csg);
        }
        else if (userMenuChoice == "cdh") {
            Cdh cdh = parseCdh(line);
            cdhs.push_back(cdh);
        }
        else if (userMenuChoice == "cr") {
            Cr cr = parseCr(line);
            crs.push_back(cr);
        }
        else if (err == true) {
            //used to skip ending statement if there's an error
        }
        else {
            continueMenuLoop = false;
        }
    }

    out << "Vectors:" << endl;

    for (unsigned i = 0; i < snaps.size(); ++i) {
        out << snaps.at(i).toString() << endl;
    }

    for (unsigned i = 0; i < csgs.size(); ++i) {
        out << csgs.at(i).toString() << endl;
    }

    for (unsigned i = 0; i < cdhs.size(); ++i) {
        out << cdhs.at(i).toString() << endl;
    }

    for (unsigned i = 0; i < crs.size(); ++i) {
        out << crs.at(i).toString() << endl;
    }

    out << endl << "Course Grades: " << endl;

    for (unsigned i = 0; i < csgs.size(); ++i) {
        out << csgs.at(i).getCourse() << ",";
        for (unsigned j = 0; j < snaps.size(); ++j) {
            if (csgs.at(i).getID() == snaps.at(j).getID()) {
                out << snaps.at(j).getName() << ",";
            }
        }
        out << csgs.at(i).getGrade() << endl;
    }

    out << endl << "Student Schedules: " << endl;

    for (unsigned i = 0; i < snaps.size(); ++i) {
        out << snaps.at(i).getName() << ", " << snaps.at(i).getID() << ", " <<
            snaps.at(i).getAddress() << ", " << snaps.at(i).getNumber() << endl;

        vector<string> courses;

        for (unsigned j = 0; j < csgs.size(); j++)
        {
            if (csgs.at(j).getID() == snaps.at(i).getID())
            {
                courses.push_back(csgs.at(j).getCourse());
            }
        }
        for (unsigned j = 0; j < courses.size(); j++)
        {
            bool printed = false;
            out << "\t" << courses.at(j) << " ";
            for (unsigned k = 0; k < cdhs.size(); k++)
            {
                if (courses[j] == cdhs.at(k).getCourse())
                {
                    out << cdhs.at(k).getDay();
                }
            }
            for (unsigned k = 0; k < cdhs.size(); k++)
            {
                if (courses[j] == cdhs.at(k).getCourse())
                {
                    if (!printed)
                    {
                        out << " " << cdhs.at(k).getTime() << ", ";
                        printed = true;
                    }
                }
            }
            for (unsigned k = 0; k < crs.size(); k++)
            {
                if (courses[j] == crs.at(k).getCourse())
                {
                    out << crs.at(k).getRoom() << endl;
                }
            }
        }
    }
}