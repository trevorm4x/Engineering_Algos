#include <iostream>
#include <string>

//header file for deck class
using namespace std;

class deck
{
    public:
        deck();
        friend void operator<<(ostream& ostr, deck rhs);
        void shuffle();
};
