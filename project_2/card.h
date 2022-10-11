#include <iostream>
#include <string>

//header file for card class
using namespace std;

class card
{
public:
	card(int suit, int value);
	void setValue(int value);
	void setSuit(int suit);
	string getValue();
	string getSuit();
	friend void operator<<(ostream& ostr, card rhs);

private:
	string cardSuit, cardValue;
};
