#include "card.h"

// Source file for the card class

card::card(int suit, int value)
// Card class constructor that sets the card objects value and suit
{
	integerValue = value;
	setValue(value);
	setSuit(suit);
	isFlipped = false;
}

card::card(const card &other)
// Card class constructor that sets the card objects value and suit
{
	cardValue = other.cardValue;
	integerValue = other.integerValue;
	cardSuit = other.cardSuit;
	isFlipped = other.isFlipped;
}

void card::flip() 
{ 
	//function to set a card's value as flipped
	//Used for the bonus to make sure that a user cannot flip a card over more than once
	isFlipped = true; 
}

bool card::getFlipped() 
{ 
	//function to return a card's state (whether it is flipped or not)
	//Used for the bonus to make sure that a user cannot flip a card over more than once
	return isFlipped; 
}

void card::setValue(int value)
// setValue function that takes in value and sets the cardValue variable to the
// associated value
{
	switch (value) {
		case 1:
			cardValue = "Ace";
			break;
		case 2:
			cardValue = "2";
			break;
		case 3:
			cardValue = "3";
			break;
		case 4:
			cardValue = "4";
			break;
		case 5:
			cardValue = "5";
			break;
		case 6:
			cardValue = "6";
			break;
		case 7:
			cardValue = "7";
			break;
		case 8:
			cardValue = "8";
			break;
		case 9:
			cardValue = "9";
			break;
		case 10:
			cardValue = "10";
			break;
		case 11:
			cardValue = "Jack";
			break;
		case 12:
			cardValue = "Queen";
			break;
		case 13:
			cardValue = "King";
			break;
	}
}

void card::setSuit(int suit)
// setSuit function that takes in a suit integer and sets the cardSuit variable
// to the associated value
{
	if (suit == 1) 
	{
		cardSuit = "Club";
	} else if (suit == 2) 
	{
		cardSuit = "Diamond";
	} else if (suit == 3) 
	{
		cardSuit = "Heart";
	} else if (suit == 4) 
	{
		cardSuit = "Spade";
	}
}

string card::getValue()
// getValue function to get the stored card value of the card object
{
	return cardValue;
}

string card::getSuit()
// getSuit function to get the stored card suit of the card object
{
	return cardSuit;
}

int card::getIntegerValue() 
{ 
	return integerValue; 
}

void operator<<(ostream &ostr, card rhs)
// function to overload the << operator so it outputs the card object's
// suit and value
{
	ostr << "Card Suit: " << rhs.cardSuit << endl;
	ostr << "Card Value: " << rhs.cardValue << endl;
}