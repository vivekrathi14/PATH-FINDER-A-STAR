#include "a_star.h"

int main() {
	int init[2]{ 0, 0 }; // starting position
	int goal[2]{ 4, 5 }; // goal position
	AStar maze; // create AStar object
	auto map = maze.ReadMazeFile("../map.maze"); // read maze file
	auto solution = maze.Search(map, init, goal); // serach the path
	maze.PrintMaze(solution); // print solution
	return 0;
}
