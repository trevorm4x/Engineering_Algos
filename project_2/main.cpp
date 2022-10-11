#include "deck.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// runs the main function that creates a deck and prints it,
// and then shuffles before reprinting to confirm changes
int main() {
  deck my_deck = deck();
  cout << my_deck;
  // provides random shuffling seed each time the program is run
  // srand (time(NULL));
  my_deck.shuffle();
  cout << my_deck;
  return 0;
}