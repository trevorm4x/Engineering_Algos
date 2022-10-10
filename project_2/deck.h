#include <iostream>
#include <string>
#include "card.h"

//header file for deck class
using namespace std;

class deck
{
    public:
        deck();
        friend void operator<<(ostream& ostr, deck rhs);
        void shuffle();
    
    private:
        *card iter;
        *card front;
};