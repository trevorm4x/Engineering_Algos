#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class board {
private:
  matrix<int> puzzleBoard;
  // matrix<matrix<bool>> conflicts;
  bool conflicts[9][9][3][9];

public:
  board();
  void readValues(string response);
  void printBoard();
  void initializeConflicts();
  void updateConflicts();
  void printConflicts();
  bool isBlank(int i, int j);
  int getCell(int i, int j);
  void addRemoveNumber(int num, int row, int col, bool val);
  int squareNumber(int i, int j);
  bool isSolved();
  // void addCellValue(int cellRow, int cellColumn, int value);
  // void clearCell(int cellRow, int cellColumn);
  // bool boardisSolved();
};
