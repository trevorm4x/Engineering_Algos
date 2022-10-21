#include "deck.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

// runs the main function that creates a deck and prints it,
// and then shuffles before reprinting to confirm changes

void playFlip(deck deck) {
	//global function playFlip to implement game functions
	for (int i = 0; i < 3; i++) {
		deck.shuffle();
	}

	//step 2, create new deck of 24 cards

	int response;
	int score;

	cout << "Would you like to turn the top card over or end the game? (Enter 1 for turn over, 0 to end the game)" << endl;
	cin >> response;

	switch (response) {
	case 1:
		node<card> dealtCard;
		//add score dynamics
		dealtCard = smalldeck.deal();
		smalldeck.replace(dealtCard);
	case 0:
		cout << "Your final score is: " << score << endl;
		//call constructors for the 2 decks
	}

	
}
int main() {
	deck deck = deck();
  
	return 0;
}