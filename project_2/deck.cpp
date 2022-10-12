#include "deck.h"
#include "d_node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Source file for deck class

deck::deck() {
  // declare num of suits and cards for iteration, 4 being spade, 13 being king
  int maxSuitNum = 4;
  int maxCardNum = 13;

  // complete first iteration (king of spades) outside of loop since it is a
  // special case where the next of this card is null since it is the last card
  newCard = new card(maxSuitNum, maxCardNum);

  // points front to the king of spades since it is the first card
  front = new node<card>(*newCard, NULL);

  // iter is used to keep track of the current node
  iter = front;
  bool flag = true;

  // build deck card by card, backwards from king-spade (bottom deck)
  // to ace-club (top deck) because of inserting at the front of list
  for (int i = maxSuitNum; i >= 1; i--) {
    for (int j = maxCardNum; j >= 1; j--) {
      // skip first iteration since treated the first front as a special case
      if (flag) {
        flag = false;
      } else {
        newCard = new card(i, j);
        iter = new node<card>(*newCard);
        iter->next = front;
        front = iter;
      }
    }
  }
}

void operator<<(ostream &ostr, deck rhs) {
  // overload << operation to print out each card
  rhs.iter = rhs.front;
  ostr << "printing!\n";
  while (rhs.iter != NULL) {
    ostr << rhs.iter->nodeValue;
    rhs.iter = rhs.iter->next;
  }
  rhs.iter = rhs.front;
}

// destructor for deck class
// not currently used but may be implemented later
/*
deck::~deck() {
    iter = front;
    while(iter != NULL) {
        cout << "deleting!\n";
        cout << iter->nodeValue;
        front = iter;
        iter = iter->next;
        delete front;
    }
}
*/

void deck::insert(node<card> *new_front_card) {
  // inserts a node at the front of the linked list
  new_front_card->next = front;
  front = new_front_card;
}

void deck::pushFrontRandomCard() {
  // iterates through the list to a random card, takes the next card
  // and places it on top of the deck
  int random_number = rand() % 50;
  int i = 0;
  iter = front;
  while (i != random_number) {
    iter = iter->next;
    ++i;
  }
  // special case for if the 2nd to last card is selected, places the
  // card at the bottom of the deck on top
  if (iter->next->next == NULL) {
    node<card> *new_front_card = iter->next;
    insert(new_front_card);
    iter->next = NULL;
  }
  // otherwise remove the next card and set current card's pointer
  // to the next next card.
  else {
    node<card> *new_front_card = iter->next;
    iter->next = iter->next->next;
    insert(new_front_card);
  }
}

void deck::shuffle() {
  // shuffles the deck by repeatedly taking a random card from somewhere
  // in the middle of the deck and placing it on top of the deck
  // 1000 repetitions was chosen to ensure thorough shuffling
  for (int i = 0; i < 1000; i++) {
    pushFrontRandomCard();
  }
}