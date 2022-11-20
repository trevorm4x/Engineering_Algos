#include <iostream>
#include <vector>
#include <string>
#include "d_matrix.h"
#include "d_except.h"
#include <fstream>


class board
{
private:
	matrix<int> puzzleBoard;
	matrix<vector<bool>> conflicts;
	
public:
	board();
	void readValues(string response);
	void printBoard();
	void initializeConflicts();
	void updateConflicts();
	void printConflicts();
	//void addCellValue(int cellRow, int cellColumn, int value);
	//void clearCell(int cellRow, int cellColumn);
	//bool boardisSolved();
};

