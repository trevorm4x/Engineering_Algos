#include "mastermind.h"
#include <stdio.h>

// executes the game
int main() {

    // declare user inputs
    int n, m;

    // continuously checks until user inputs valid params to play game
    bool flag = true;
    while(flag) {
        cout << "Please enter a valid number of digits in the sequence\n";
        cout << "and a valid max number of the digit range :\n";
        cin >> n >> m;
        // won't allow 0 or negative numbers as inputs, but will allow no input
        if(n <= 0 || m <= 0) {
            flag = true;
        } else {
            flag = false;
        }
    }

    // chooses which constructor to use depending on user input
    if(n != 0 && m != 0) {
        mastermind game = mastermind(n, m);
        game.playGame();
    } else {
        mastermind game = mastermind();
        game.playGame();
    }

    return 0;
}