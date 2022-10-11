#include "deck.h"
#include "d_node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;

// Source file for deck class

deck::deck() 
{
    int maxSuitNum = 4;
    int maxCardNum = 13;
    newCard = new card(maxSuitNum, maxCardNum);
    front = new node<card>(*newCard, NULL);
    iter = front;
    bool flag = true;
    for (int i = maxSuitNum; i >= 1; i--) {
        for (int j = maxCardNum; j >= 1; j--) {
            // skip first iteration since we had to treat the first front as a special case
            if (flag) {
                flag = false;
            }
            else {
                newCard = new card(i, j);
                iter = new node<card>(*newCard);
                iter->next = front;
                front = iter;
            }
        }
    }
}

void operator<<(ostream& ostr, deck rhs) {
    rhs.iter = rhs.front;
    ostr << "printing!\n";
    while(rhs.iter != NULL) {
        ostr << rhs.iter->nodeValue;
        rhs.iter = rhs.iter->next;
    }
    rhs.iter = rhs.front;
}

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
    new_front_card->next = front;
    front = new_front_card;
}

void deck::pushFrontRandomCard() {
    int random_number = rand() % 50;
    cout << "rand called" << random_number << "\n";
    int i = 0;
    iter = front;
    while (i != random_number){
        iter = iter->next;
        ++i;
    }
    if (iter->next->next == NULL) {
        node<card>* new_front_card = iter->next;
        insert(new_front_card);
        iter->next = NULL;
    }
    else {
        node<card>* new_front_card = iter->next;
        iter->next = iter->next->next;
        insert(new_front_card);
    }
}

void deck::shuffle() {
    for (int i = 0; i < 1000; i++) {
        pushFrontRandomCard();
    }
}