#include "deck.h"
#include "d_node.h"
#include "card.h"

// Source file for deck class

deck::deck() 
{
    int maxSuitNum = 4;
    int maxCardNum = 13;
    node<card> **front = NULL;
    node<card> *temp;
    for (int i = maxSuitNum; i >= 0; i--) {
        for (int j = maxCardNum; j >= 0; j--) {
            card curCard = card(i, j);
            temp = new node(curCard);
            temp->next = (*front);
            (*front) = temp;
        }
    }
}