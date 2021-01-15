#pragma once
#include<iostream>
#include<vector>
#include<sstream>
#include<algorithm>
#include<fstream>
#include<string>

// resolving namespaces
using std::cout;
using std::string;
using std::vector;
using std::abs;
using std::sort;
using std::ifstream;
using std::istringstream;
using std::getline;

// create class
class AStar {
private:
	// state class
	enum class State { mEmpty, mObstacle, mClosed, mPath, mStart, mFinish };
	// direction
	const int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
public:
	// methods declarations
	vector<State> ParseLine(string line);
	vector<vector<State>> ReadMazeFile(string path);
	int Heuristic(int r1, int c1, int r2, int c2);
	void SortCells(vector<vector<int>>* v);
	bool ValidCell(int r, int c, vector<vector<State>>& matrix);
	void AddToList(int r, int c, int d, int h, vector<vector<int>>& openlist, vector<vector<State>>& matrix);
	void ExpandNeighbors(const vector<int>& current, int goal[2], vector<vector<int>>& openlist, vector<vector<State>>& matrix);
	vector<vector<State>> Search(vector<vector<State>>& matrix, int init[2], int goal[2]);
	string CellString(State cell);
	void PrintMaze(const vector<vector<State>>& maze);
};