#include "card.h"
#include "d_node.h"
#include <iostream>
#include <string>

// header file for deck class
using namespace std;

class deck {
public:
  deck();
  deck(node<card> *newTop);
  ~deck();
  node<card> *deal();
  friend void operator<<(ostream &ostr, deck &rhs);
  void shuffle();
  void insert(node<card> *new_front_card);
  void replace(node<card> *new_front_card);
  node<card> *goToCard(int pos);

private:
  node<card> *front;
  node<card> *bottom;
  node<card> *iter;
  card *newCard;
  void pushFrontRandomCard();
};
