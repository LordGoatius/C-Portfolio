#ifndef MAZE_H
#define MAZE_H

#include"MazeInterface.h"
#include<iostream>
#include<sstream>

enum CellValue_t { OPEN = 0, BLOCKED = 1, VISITED = 2, EXIT = 3, LEFT = 4, RIGHT = 5, UP = 6, DOWN = 7, OUT = 8, IN = 9 };

using namespace std;

class Maze :  public MazeInterface {
private:
	int width;
	int height;
	int layer;
	CellValue_t*** maze;
	//rows is height, cols is width
	// maze[l][h][w]
public:
	Maze(int hei, int wid, int lay) : width(wid), height(hei), layer(lay) {
		CellValue_t*** arr = new CellValue_t ** [lay];
		for (int k = 0; k < layer; ++k) {
			arr[k] = new CellValue_t* [height];
			for (int i = 0; i < height; ++i) {
				arr[k][i] = new CellValue_t[width];
			}
		}
		maze = arr;
	}

	~Maze(void) {
		for (int k = 0; k < layer; ++k) {
			for (int i = 0; i < height; ++i) {
				delete[] maze[k][i];
			}
			delete[] maze[k];
		}
		delete[] maze;
	}

	virtual void setValue(int hei, int wid, int lay, int value) {
		CellValue_t inputTwo;
		inputTwo = OPEN;
		if (value == 1) inputTwo = BLOCKED;
		maze[lay][hei][wid] = inputTwo;
	}

	virtual bool find_maze_path() { 
		return find_maze_path(0, 0, 0);
	}

	bool find_maze_path(int l, int h, int w);

	virtual string toString() const;

};
#endif

