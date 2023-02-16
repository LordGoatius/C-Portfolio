#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>

#include "Maze.h"

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

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

    /*----------------------MAZE INPUT----------------------*/
    int height = 0;
    int width = 0;
    int layers = 0;
    in >> height;
    in >> width;
    in >> layers;

    Maze myMaze(height, width, layers);

    int input;

    for (int k = 0; k < layers; ++k) {
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                in >> input;
                myMaze.setValue(j, i, k, input);
            }
        }
    }
    /*-----------------------MAZE OUTPUT----------------------*/
    out << "Solve Maze:" << endl << myMaze.toString() << endl;
    bool exists = myMaze.find_maze_path();
    if (exists) {
        out << "Solution:" << endl << myMaze.toString() << endl;
    }
    else {
        out << "No Solution Exists!" << endl;
    }
    /*-------------------------------------------------------*/
    return 0;
}