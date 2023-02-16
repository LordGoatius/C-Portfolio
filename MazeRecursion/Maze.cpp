#include "Maze.h"

//recursive backtracting function
bool Maze::find_maze_path(int l, int h, int w) {
	if (l < 0 || h < 0 || w < 0 || l >= layer || h >= height || w >= width) return false;
	if (maze[l][h][w] != OPEN) return false;
	if (l == layer - 1 && h == height - 1 && w == width - 1) {
		maze[l][h][w] = EXIT;
		return true;
	}

	maze[l][h][w] = VISITED;

	if (find_maze_path(l, h, w - 1)) {
		maze[l][h][w] = LEFT;
		return true;
	}
	else if (find_maze_path(l, h, w + 1)) {
		maze[l][h][w] = RIGHT;
		return true;
	}
	else if (find_maze_path(l, h - 1, w)) {
		maze[l][h][w] = UP;
		return true;
	}
	else if (find_maze_path(l, h + 1, w)) {
		maze[l][h][w] = DOWN;
		return true;
	}
	else if (find_maze_path(l - 1, h, w)) {
		maze[l][h][w] = OUT;
		return true;
	}
	else if (find_maze_path(l + 1, h, w)) {
		maze[l][h][w] = IN;
		return true;
	}
	else {
		maze[l][h][w] = VISITED;
		return false;
	}
}

string Maze::toString() const {
	//CellValue_t { OPEN = 0, BLOCKED = 1, VISITED = 2, EXIT = 3, LEFT = 4, RIGHT = 5, UP = 6, DOWN = 7, OUT = 8, IN = 9 };
	ostringstream oss;
	char choose[10] = { '_','X','*','E','L','R','U','D','O','I' };
	for (int k = 0; k < layer; ++k) {
		oss << "Layer " << k + 1 << endl;
		for (int j = 0; j < height; ++j) {
			for (int i = 0; i < width; ++i) {
				oss << choose[maze[k][j][i]] << " ";
			}
			oss << endl;
		}
	}
	return oss.str();
}
