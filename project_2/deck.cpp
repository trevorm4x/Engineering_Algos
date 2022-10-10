#include "deck.h"
#include "d_node.h"
#include <iostream>

using namespace std;

// Source file for deck class

deck::deck() 
{
    int maxSuitNum = 4;
    int maxCardNum = 13;
    node<card> *front = NULL;
    node<card> *temp;
    for (int i = 1; i <= maxSuitNum; i++) {
        for (int j = maxCardNum; j > 0; j--) {
            card *curCard = new card(i, j);
            if ((i == 1) and (j == maxCardNum)) {
                front = new node<card>(*curCard);
            }
            else {
                temp = new node<card>(*curCard);
                temp->next = front;
                front = temp;
            }
        }
    }
}

void operator<<(ostream& ostr, deck rhs) {
    rhs.iter = rhs.front;
    while(rhs.iter != NULL) {
        ostr << rhs.iter->nodeValue.getValue() << endl;
        rhs.iter = rhs.iter->next;
    }
}