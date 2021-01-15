#include "a_star.h"

// class methods

// Parse a single line i.e. string
vector<AStar::State> AStar::ParseLine(string line) {
	istringstream sline(line);
	int num;
	char ch;
	vector<AStar::State> row;
	while (sline >> num >> ch && ch == ',') {
		if (num == 0) {
			row.push_back(AStar::State::mEmpty);
		}
		else {
			row.push_back(AStar::State::mObstacle);
		}
	}
	return row;
}


// Read and parse entire maze file
vector<vector<AStar::State>> AStar::ReadMazeFile(string path) {
	ifstream mazefile(path); // create mazefile object
	vector<vector<AStar::State>> maze = {};

	if (mazefile) {
		string line;
		while (getline(mazefile, line)) {
			vector<AStar::State> row = ParseLine(line);
			maze.push_back(row);
		}

	}
	return maze;
}


// Heuristic - Calculate Manhattan Distance
int AStar::Heuristic(int r1, int c1, int r2, int c2) {
	return abs(c1 - c2) + abs(r1 - r2);
}

// compare cost of 2 cells
bool Compare(const vector<int> a, const vector<int> b) {
	int cost1 = a[2] + a[3]; //(d+h) i.e. depth + heuristic
	int cost2 = b[2] + b[3]; //(d+h)
	return cost1 > cost2;
}

// sort the neighbor cells wrt to cost
void AStar::SortCells(vector<vector<int>>* v) {
	sort(v->begin(), v->end(),Compare);
}

// check if neighbor cell is valid
bool AStar::ValidCell(int r, int c, vector<vector<AStar::State>>& matrix) {
	if ((r >= 0 && r < matrix.size()) && (c >= 0 && c < matrix[0].size())) {
		return matrix[r][c] == AStar::State::mEmpty;
	}
	return false;
}

// add cell to openlist
void AStar::AddToList(int r, int c, int d, int h, vector<vector<int>>& openlist, vector<vector<AStar::State>>& matrix) {
	openlist.push_back(vector<int>{r, c, d, h});
	matrix[r][c] = AStar::State::mClosed;
}

// expand the neighbors
void AStar::ExpandNeighbors(const vector<int>& current, int goal[2], vector<vector<int>>& openlist, vector<vector<AStar::State>>& matrix) {
	// Get current node's data.
	int r = current[0];
	int c = current[1];
	int d = current[2];

	// Loop through current node's potential neighbors.
	for (int i = 0; i < 4; i++) {
		int r2 = r + dir[i][0];
		int c2 = c + dir[i][1];

		// Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
		if (AStar::ValidCell(r2, c2, matrix)) {
			// Increment d value and add neighbor to open list.
			int d2 = d + 1;
			int h2 = AStar::Heuristic(r2, c2, goal[0], goal[1]);
			AStar::AddToList(r2, c2, d2, h2, openlist, matrix);
		}
	}
}

// A* (A Star)

vector<vector<AStar::State>> AStar::Search(vector<vector<AStar::State>>& matrix, int init[2], int goal[2]) {
	// Create the vector of nodes.
	vector<vector<int>> open{};

	// Initialize the starting node.
	int r = init[0];
	int c = init[1];
	int d = 0;
	int h = AStar::Heuristic(r, c, goal[0], goal[1]);
	AStar::AddToList(r, c, d, h, open, matrix);

	while (open.size() > 0) {
		// Get the next node
		AStar::SortCells(&open);
		auto current = open.back();
		open.pop_back();
		r = current[0];
		c = current[1];
		matrix[r][c] = AStar::State::mPath;

		// Check if we're done.
		if (r == goal[0] && c == goal[1]) {
			matrix[init[0]][init[1]] = AStar::State::mStart;
			matrix[goal[0]][goal[1]] = AStar::State::mFinish;
			return matrix;
		}

		// If we're not done, expand search to current node's neighbors.
		AStar::ExpandNeighbors(current, goal, open, matrix);
	}

	// Np new nodes to explore and path doesn't exist.
	cout << "No path found!" << "\n";
	return std::vector<vector<AStar::State>>{};
}

// Convert maze into symboled maze
string AStar::CellString(AStar::State cell) {
	switch (cell) {
	case AStar::State::mObstacle: return "X  ";
	case AStar::State::mPath: return "@  ";
	case AStar::State::mStart: return "#  ";
	case AStar::State::mFinish: return "$ ";
	default: return "0  ";
	}
}

// Convert maze into game based maze
//string CellString(AStar::State cell) {
//	switch (cell) {
//	case AStar::State::mObstacle: return "\xF0\x9F\x9A\x80 ";
//	case AStar::State::mPath: return "🚗   ";
//	case AStar::State::mStart: return "🚦   ";
//	case AStar::State::mFinish: return "🏁 ";
//	default: return "0  ";
//	}
//}

// print the maze
void AStar::PrintMaze(const vector<vector<AStar::State>> &maze) {
	for (int i = 0; i < maze.size(); i++) {
		for (int j = 0; j < maze[0].size(); j++) {
			cout << AStar::CellString(maze[i][j]);
		}
		cout << "\n";
	}
}