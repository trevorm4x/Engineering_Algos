#include "deck.h"
#include <iostream>

using namespace std;

int main() {
    deck my_deck = deck();
    cout << my_deck;
    card* new_card;
    new_card = new card(1, 1);

    node<card>* new_node;
    new_node = new node<card>(*new_card);
    my_deck.insert(new_node);
    cout << my_deck;
    return 0;
}