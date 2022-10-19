#include "card.h"
#include "d_node.h"
#include <iostream>
#include <string>

// header file for deck class
using namespace std;

class deck {
public:
  deck();
  ~deck();
  deck deal();
  friend void operator<<(ostream &ostr, deck& rhs);
  void shuffle();
  void insert(node<card> *new_front_card);
  void replace(node<card> *new_front_card);

private:
  node<card> *front;
  node<card> *iter;
  card *newCard;
  void pushFrontRandomCard();
};
