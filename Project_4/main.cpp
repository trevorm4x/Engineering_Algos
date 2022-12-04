#include "board.h"

using namespace std;


int readBigFile(string fileName)
// takes in the filename of the big puzzles file and reads in each line
// to a new board and solves it, storing the number of recursive calls
{
  int total_calls = 0;
  int num_puzzles = 0;
  fstream myFile;
  myFile.open(fileName.c_str(), ios::in);
  int rows, cols;
  // z character for finding end of file
  char Z = 90;
  if (myFile.is_open()) // ensures that the file is opened properly before
                        // reading in words
  {
    bool file_read = false;
    // loop on each line of the file and make a board with each until we get
    // the one that ends with a "z"
    while (!file_read) {
      // 81-length string
      string puzzle;
      // this probably doesn't work but not sure how to ATM
      myFile >> puzzle;
      ++num_puzzles;
      if (puzzle[puzzle.length() - 1] == Z) {
        // remove the "Z"
        puzzle.pop_back();
        file_read = true;
      }
      board newboard;
      newboard.readFromString(puzzle);
      int num_calls = newboard.solve();
      if (num_calls == -1) {
        cout << "FAILED!\n";
      }
      else {
        total_calls += num_calls;
      }
    }
  }
  return total_calls / num_puzzles;
}
 
// main function that initializes a game board and executes methods for testing
int main() {
  board board1;
  int numcalls = board1.solve();
  board1.printBoard();
  if (board1.isSolved()) {
    cout << "board 1 is solved in " << numcalls << " calls!\n";
  }
  else {
    cout << "failed to solve board!!\n";
  }
  board board2;
  numcalls = board2.solve();
  board2.printBoard();
  if (board2.isSolved()) {
    cout << "board 2 is solved in " << numcalls << " calls!\n";
  }
  else {
    cout << "failed to solve board!!\n";
  }
  board board3;
  numcalls = board3.solve();
  board3.printBoard();
  if (board3.isSolved()) {
    cout << "board 3 is solved in " << numcalls << " calls!\n";
  }
  else {
    cout << "failed to solve board!!\n";
  }
}