#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// container for a location and list of allowed
// numbers to try
typedef struct trynum {
  int row;
  int col;
  int num[9];
} trynum_t;

class board {
private:
  matrix<int> puzzleBoard;
  // matrix<matrix<bool>> conflicts;
  bool conflicts[9][9][3][9];
  int recurCalls;

public:
  board();
  void readValues(string response);
  void readFromString(string puzzle);
  void readBigStringValues(string filename);
  void printBoard();
  void initializeConflicts();
  void printConflicts();
  int getCell(int i, int j);
  void addRemoveNumber(int num, int row, int col, bool val);
  bool isSolved();
  int solve();
  trynum_t bestConflict();
  trynum_t oneLegalSpotNumber();
  vector<int> numRank();
  // void addCellValue(int cellRow, int cellColumn, int value);
  // void clearCell(int cellRow, int cellColumn);
};
