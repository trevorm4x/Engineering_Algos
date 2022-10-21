#include "deck.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int updateScore(int score, card chosenCard) {
    //global function to update a user's score based on the card they selected
    int cardValue = chosenCard.getIntegerValue();

    if (cardValue == 1) 
    {
        score += 10;
    } else if (cardValue >= 11 && cardValue <= 13) 
    {
        score += 5;
    } else if (cardValue >= 8 && cardValue <= 10) 
    {
        score += 0;
    } else if (cardValue == 7) 
    {
        score /= 2;
    } else if (cardValue >= 2 && cardValue <= 6) 
    {
        score = 0;
    }

    if (chosenCard.getSuit() == "Heart") 
    {
        score++;
    }
    return score;
}

void playFlip() {
    // runs the main function that creates a deck and prints it,
    // and then shuffles before reprinting to confirm changes

    deck my_deck = deck();

    int response = -1;
    int score = 0;

    for (int i = 0; i < 3; i++) 
    {
        my_deck.shuffle();
    }

    deck gameDeck = deck(my_deck.deal());

    for (int i = 0; i < 23; i++) 
    {
        gameDeck.replace(my_deck.deal());
    }
    cout << "Here are the remaining cards\n";
    cout << my_deck;
    cout << "Here are the cards in your hand\n";
    cout << gameDeck;

    while (1)
    {
        cout << "Choose a card from 1 to 24, or 0 to end the game." << endl;
        cin >> response;
        while (response < 0 || response > 24)
        {
            cout << "The card you selected does not exist. Please choose a card from 1 to 24, or 0 to end the game" << endl;
            cin >> response;
        }

        if (response == 0) 
        {
            cout << "Your final score is: " << score << endl;
            break;
        }
        else 
        {
            node<card>* chosenCard = gameDeck.goToCard(response);
            cout << "Here are the cards in your hand\n";
            cout << gameDeck;
            if (chosenCard->nodeValue.getFlipped()) 
            {
                cout << "You already chose that card before, cheater!!!!\n";
            }
            else 
            {
                chosenCard->nodeValue.flip();
                cout << chosenCard->nodeValue;
                score = updateScore(score, chosenCard->nodeValue);
                cout << "Your new score is " << score << endl;
            }
        }
    }
}

int main() 
{
    playFlip();
    return 0;
}
