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

public:
	board();
	void readValues(string response);
	void printBoard();
	//void addCellValue(int cellRow, int cellColumn, int value);
	//void clearCell(int cellRow, int cellColumn);
	//bool boardisSolved();
};

