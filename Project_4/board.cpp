#include "board.h"
#include <vector>

int BoardSize = 9;
int SquareSize = 3;
long long int totalCalls = 0;
int numPuzzles = 0;
int puzzleNum = 1;

board::board()
// constructor that takes in a user input for which file to read in
// and then populates all puzzleboards and solves them
// once all boards are solved, it also prints out the average number of
// recursive calls to solve a puzzle
{
  string response;
  cout << "Please enter the name of the sudoku puzzle file" << endl;
  cin >> response;
  initializeConflicts();
  cout << "Initialized conflicts\n";
  readBigStringValues(response);
  cout << "total number of puzzles: " << numPuzzles << endl;
  cout << "total number of recursive calls: " << totalCalls << endl;
  cout << "Average number of recursive calls: " << totalCalls / numPuzzles
       << endl;
}

void board::addRemoveNumber(int num, int row, int col, bool val)
// add or remove a number from the board and conflicts tables based on the
// flag "val": if "true" add the number, if "false" remove it.
{
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

void board::readFromString(string puzzle)
// function that fills out the puzzleBoard matrix from the input string
// used in tandem with the getline command to fill in one puzzleboard
{
  int rows = 9;
  int cols = 9;
  puzzleBoard.resize(rows, cols);
  initializeConflicts();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      char temp;
      temp = puzzle[i * 9 + j];
      if (temp != '.') {
        addRemoveNumber(temp - '0', i, j, 1);
      } else {
        puzzleBoard[i][j] = -1;
      }
    }
  }
}

void board::readBigStringValues(string fileName)
// readBigStringValues function that takes in a user inputted string and reads
// in the values from that string to the puzzle board
{
  fstream myFile;
  myFile.open(fileName.c_str(), ios::in);
  if (myFile.is_open()) // ensures that the file is opened properly before
  // reading in words
  {
    string puzzle;
    while (getline(myFile, puzzle)) // reads in each line of the text file and
                                    // stores it in the puzzle string
    {
      readFromString(puzzle);
      cout << "Puzzle #" << puzzleNum << endl;
      cout << "Unsolved Board" << endl;
      printBoard();
      recurCalls = 0;
      int temp = solve();
      totalCalls += temp;
      cout << "Solved Board" << endl;
      printBoard();
      cout << "Recursive calls needed: " << temp << endl;
      numPuzzles++;
      puzzleNum++;
    }
  } else // prints error message in case the file is not able to be opened
  {
    cout << "File was not opened" << endl;
  }
}

void board::printBoard()
// printBoard function to print out the sudoku puzzle board
{
  // sudoku board
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (puzzleBoard[row][col] == -1) {
        cout << "0 ";
      } else {
        cout << puzzleBoard[row][col] << " ";
      }
    }
    cout << endl;
  }
}

void board::initializeConflicts()
// function to set all conflicts of all cells to 0 (default)
{
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      for (int k = 0; k < 3; k++) {
        for (int l = 0; l < 9; l++) {
          conflicts[i][j][k][l] = 0;
        }
      }
    }
  }
}

void board::printConflicts()
// function to print out the conflicts for each cell
// prints out the row, column and square conflicts
{
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      cout << row << ", " << col << ": " << endl;
      for (int conflictType = 0; conflictType < 3; conflictType++) {
        cout << (conflictType == 0   ? "row"
                 : conflictType == 1 ? "col"
                                     : "sqr")
             << " conflicts: {";
        for (int i = 0; i < 9; i++) {
          cout << " " << conflicts[row][col][conflictType][i] << " ";
        }

        cout << "}" << endl;
      }
    }
  }
}

bool board::isSolved()
// boolean function that returns true if every cell on the board has been filled
// out
{
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (puzzleBoard[row][col] < 0) {
        return false;
      }
    }
  }
  return true;
}

int board::solve()
// function that solves the sudoku board using backtracking and recursion
// once the board is solved, it returns the number of recursive calls made in
// the function
{
  if (isSolved()) {
    return recurCalls;
  }

  trynum_t bestnum = bestConflict();
  // early fail condition if we found an empty cell with no legal moves
  if (bestnum.row == -1)
    return -1;
  // numbers in descending order of occurances
  vector<int> sorted_nums = numRank();
  // check all numbers, if none allowed then we found a cell with no
  // number and no allowed numbers, need to backtrack
  for (int inum = 0; inum < 9; inum++) {
    // prefer numbers that have more occurances first
    // subtract 1 for legacy support
    // this makes literally the tiniest of differences
    int num = sorted_nums[inum] - 1;
    if (bestnum.num[num] == 1) {
      // add number to board and update conflicts
      addRemoveNumber(num + 1, bestnum.row, bestnum.col, 1);
      ++recurCalls;
      // solve new board state
      int success = solve();
      // if we failed, backtrack
      if (success == -1)
        addRemoveNumber(num + 1, bestnum.row, bestnum.col, 0);
      // if we succeeded, pass success upwards
      else
        return success;
    }
  }
  // if we tried all allowed numbers and never succeeded, we failed
  return -1;
}

int board::getCell(int row, int col)
// function to get the number value stored at the specified cell
{
  return puzzleBoard[row][col];
}

vector<int> board::numRank() {
  // counts the occurance of each number on the board and
  // returns the board numbers in descending order of occurance
  int intscores[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int cell = getCell(i, j);
      if (cell > 0)
        intscores[cell - 1]++;
    }
  }
  vector<int> sorted_nums;
  sorted_nums.resize(9);
  int inum = 0;
  // finds the highest occurance numbers first OR NOT???
  for (int occ = 9; occ >= 0; occ--) {
    for (int num = 0; num < 9; num++) {
      if (intscores[num] == occ) {
        // add 1 to go back from intscores index to sudoku numbers
        sorted_nums[inum] = num + 1;
        ++inum;
      }
    }
  }
  return sorted_nums;
}

trynum_t board::bestConflict() {
  // naive approach just gets the first number not solved
  // with possible nums

  // container for best conflict to use
  trynum_t best;
  // container for iterating
  trynum_t some;
  // larger than the max number of legal moves
  int best_num_legal_moves = 10;
  best.row = -1;
  best.col = -1;
  for (int i = 0; i < 9; i++) {
    best.num[i] = 0;
  }

  // check each cell for the number of legal moves it has and track the best one
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      // find the cells with no entry
      if (getCell(i, j) == -1) {
        // count number of legal moves (and store legal moves in temp struct)
        int num_legal = 0;
        for (int num = 0; num < 9; ++num) {
          // check that number has no conflicts on row, column, and square
          some.row = i;
          some.col = j;
          // check no conflicts on squares, rows, or columns
          if (conflicts[i][j][0][num] == 0 && conflicts[i][j][1][num] == 0 &&
              conflicts[i][j][2][num] == 0) {
            some.num[num] = 1;
            num_legal++;
          } else {
            some.num[num] = 0;
          }
        }
        // if we found there's no legal moves for any empty cell we can quit
        // this line early
        if (num_legal == 0) {
          best.row = -1;
          return best;
        }
        // check if this cell has fewer legal moves than the best one we've
        // found so far
        if (num_legal < best_num_legal_moves) {
          best = some;
          // cout << num_legal << endl;
        }
        if (num_legal == 1)
          return best;
      }
    }
  }

  return best;
}

trynum_t board::oneLegalSpotNumber() {
  // attempts to prioritize numbers with one legal spot to place first. Doesn't
  // work yet - could be improved by working in conjuction with the other
  // conflicFinder better, and by breaking early if there is only one legal spot
  // for a number but fewer than 8 of that number on the board currently
  trynum_t best;
  // try finding a number with one possible location
  for (int num = 0; num < 9; num++) {
    int num_legal_spots = 0;
    int legalrow;
    int legalcol;
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        // if allowed, count it
        if (conflicts[i][j][0][num] == 0 && conflicts[i][j][1][num] == 0 &&
            conflicts[i][j][2][num] == 0) {
          num_legal_spots++;
          legalrow = i;
          legalcol = j;
        }
      }
    }
    // if we found a number with exactly one legal spot, return it
    if (num_legal_spots == 1) {
      best.row = legalrow;
      best.col = legalcol;
      // zero out other numbers
      for (int i = 0; i < 9; i++) {
        best.num[i] = 0;
      }
      best.num[num] = 1;
      // printBoard();
      // cout << "num with one legal spot: " << num << ", goes here " <<
      // legalrow << legalcol << endl;
      return best;
    }
  }
  return best;
}