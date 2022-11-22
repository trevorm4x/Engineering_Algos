#include "board.h"

int BoardSize = 9;
int SquareSize = 3;

board::board() {
  string response;
  cout << "Please enter the name of the sudoku puzzle file" << endl;
  cin >> response;
  initializeConflicts();
  readValues(response);
  // updateConflicts();
  cout << "Initialized conflicts\n";
  printBoard();
  cout << "\n\n\n";
  printConflicts();
}

void board::addRemoveNumber(int num, int row, int col, bool val) {
  // add or remove a number from the board and conflicts tables based on the
  // flag "val".

  if (val)
    puzzleBoard[row][col] = num;
  else
    puzzleBoard[row][col] = -1;

  // row conflicts, iterate across each row adding conflicts for that column
  for (int j_col = 0; j_col < 9; j_col++) {
    conflicts[row][j_col][0][num - 1] = val;
  }

  // col conflicts, iterate across each row adding conflicts for that column
  for (int i_row = 0; i_row < 9; i_row++) {
    conflicts[i_row][col][1][num - 1] = val;
  }

  // int square = squareNumber(row, col);
  int s_row = (row / 3) * 3;
  int s_col = (col / 3) * 3;
  for (int i_row = s_row; i_row < s_row + 3; i_row++)
    for (int j_col = s_col; j_col < s_col + 3; j_col++)
      conflicts[i_row][j_col][2][num - 1] = val;
}
void board::readValues(string fileName)
// readValues function that takes in a user inputted string and reads in the
// values from that string to the puzzle board
{
  fstream myFile;
  myFile.open(fileName.c_str(), ios::in);
  int rows, cols;
  if (myFile.is_open()) // ensures that the file is opened properly before
                        // reading in words
  {
    rows = 9;
    cols = 9;
    puzzleBoard.resize(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        char temp;
        myFile >> temp;
        if (temp != '.') {
          addRemoveNumber(temp - '0', i, j, 1);
          // puzzleBoard[i][j] = temp - '0';
        } else {
          puzzleBoard[i][j] = -1;
        }
      }
    }
  } else // prints error message in case the file is not able to be opened
  {
    cout << "File was not opened" << endl;
  }
}

void board::printBoard()
// printBoard function to print out the sudoku puzzle board and later on the
// conflicts
{
  // sudoku board
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (puzzleBoard[row][col] == -1)
        cout << "0 ";
      else
        cout << puzzleBoard[row][col] << " ";
    }
    cout << endl;
  }
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
  // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
  // coordinates of the square that i,j is in.
  return SquareSize * (i / SquareSize) + j / SquareSize;
}

void board::initializeConflicts() {
  // matrix<bool> initVal = matrix<bool>(3, 9, true);
  // matrix<matrix<bool>> conflicts = matrix<matrix<bool>>(9, 9, initVal);
  // cout << initVal[0][0] << endl;
  // cout << conflicts[0][0][0][0] << endl;
  // for (int i = 0; i < 9; i++) {
  // for (int j = 0; j < 9; j++) {
  // conflicts[i][j] = { false, false, false, false, false, false, false, false,
  // false };
  // }
  // }

  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      for (int k = 0; k < 3; k++)
        for (int l = 0; l < 9; l++)
          conflicts[i][j][k][l] = 0;
}

void board::printConflicts() {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      cout << row << ", " << col << ": " << endl;
      for (int conflictType = 0; conflictType < 3; conflictType++) {
        cout << (conflictType == 0   ? "row"
                 : conflictType == 1 ? "col"
                                     : "sqr")
             << " conflicts: {";
        for (int i = 0; i < 9; i++)
          cout << " " << conflicts[row][col][conflictType][i] << " ";

        cout << "}" << endl;
      }
    }
  }
}

bool board::isSolved() {
  for (int row = 0; row < 9; row++)
    for (int col = 0; col < 9; col++)
      if (puzzleBoard[row][col] < 0)
        return false;
  return true;
}