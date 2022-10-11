#include <iostream>
#include <string>
#include "card.h"
#include "d_node.h"

//header file for deck class
using namespace std;

class deck
{
    public:
        deck();
        ~deck();
        friend void operator<<(ostream& ostr, deck rhs);
        void shuffle();
        void insert(node<card>* new_front_card);
    
    private:
        node<card> *front;
        node<card> *iter;
        card *newCard;
};
