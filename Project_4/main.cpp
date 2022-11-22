#include "board.h"

using namespace std;

int main() {
  board board1;
  if (board1.isSolved()) {
    cout << "board 1 is solved!\n";
  }
  board board2;
  if (board2.isSolved()) {
    cout << "board 1 is solved!\n";
  }
  board board3;
  if (board3.isSolved()) {
    cout << "board 1 is solved!\n";
  }
  cout << "Adding a nine to the board for testing!" << endl;
  board3.addRemoveNumber(9, 8, 8, 1);
  board3.printBoard();
  board3.printConflicts();

  cout << "Removing a nine from the board for testing!" << endl;
  board3.addRemoveNumber(9, 8, 8, 0);
  board3.printBoard();
  board3.printConflicts();
}