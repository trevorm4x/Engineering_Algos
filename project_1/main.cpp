// Project 1 Part B
// Trevor Smith
// Andrew Nguy
// Viraj Lawande
//
// main file that executes playing of the game

#include "mastermind.h"
#include <stdio.h>

int main() {
    int response;
    cout
    << "Would you like to play with default parameters? (1 for Yes, 0 for No)" << endl;
    cin >> response;

    if(response == 1) {
        mastermind game = mastermind();
        game.playGame();
    } else {
        // declare integers to hold user inputs for length and range;
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
        mastermind game = mastermind(n, m);
        game.playGame();
    }

    return 0;
}