#include <iostream>
#include <string>

//header file for deck class
using namespace std;

class deck
{
    deck();
    friend void operator<<(ostream& ostr, deck rhs);
    void shuffle();
};
