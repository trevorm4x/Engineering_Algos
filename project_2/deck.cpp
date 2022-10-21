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
  bottom = front;

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

deck::deck(node<card> *newTop) {
  // alternate constructor that creates deck containing single card
  newCard = NULL;
  front = newTop;
  bottom = newTop;
  iter = newTop;
  newTop->next = NULL;
}

void operator<<(ostream &ostr, deck &rhs) {
  // overloaded << operation to print out each card
  rhs.iter = rhs.front;
  ostr << "Here is your deck:\n";
  while (rhs.iter != NULL) {
    ostr << rhs.iter->nodeValue;
    rhs.iter = rhs.iter->next;
  }
  rhs.iter = rhs.front;
}

deck::~deck() {
  // destructor for the deck class that deletes the memory allocated at each
  // node within the deck
  iter = front;
  while (iter != NULL) {
    front = iter;
    iter = iter->next;
    delete front;
  }
}

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

node<card> *deck::deal() {
  // function to deal the top card of the deck to the user
  // returns the card as an output
  cout << front->nodeValue;
  node<card> *a = front;
  front = front->next;
  iter = front;
  a->next = NULL;
  return a;
}

void deck::replace(node<card> *new_bottom_card) {
  // function to put a card at the bottom of the deck
  // takes in a card node and has not return output
  bottom->next = new_bottom_card;
  bottom = new_bottom_card;
  new_bottom_card->next = NULL;
}

node<card> *deck::goToCard(int pos) {
  // function to navigate to a card at a specific position within the deck
  iter = front;
  for (int i = 1; i < pos; i++) {
    iter = iter->next;
  }
  return iter;
}
