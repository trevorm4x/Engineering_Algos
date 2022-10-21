#include <iostream>
#include <string>

// header file for card class
using namespace std;

class card {
public:
	card(int suit, int value);
	card(const card& other);
	void setValue(int value);
	void setSuit(int suit);
	string getValue();
	string getSuit();
	bool getFlipped();
	friend void operator<<(ostream &ostr, card rhs);
	card operator= (const card &other);
	void flip();
  

private:
	string cardSuit, cardValue;
	bool isFlipped;
};
