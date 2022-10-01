// Project 1 Part B
// Trevor Smith
// Andrew Nguy
// Viraj Lawande
//
// Mastermind class implementation file that handles playing of the game, with
// functions to print the secret code for game testing, get the user's guess,
// get the number of correct and incorrect digits and check if the code has been
// cracked

#include "mastermind.h"
#include <stdio.h>

using namespace std;

mastermind::mastermind(int n, int m)
: secretCode(n, m)
// mastermind class constructor that takes in user inputs for the length and
// digit range for the code
{
    secretCode.initializeRandomCode();
    guessCounter = 0;
};

mastermind::mastermind()
: secretCode(5, 10)
// mastermind class constructor that takes in no inputs and initializes the 
// secret code with a 5 digit length and a digit range of 10
{
    secretCode.initializeRandomCode();
    guessCounter = 0;
};

void mastermind::printSecretCode()
// function that prints out the secret code for program testing
{
    cout << "Shhhh! the secret Sequence is " << endl;
    secretCode.printCode();
};

code mastermind::humanGuess()
// function to take in a user's guess and store it as a code object
{
    cout << "Please enter your guess of " << secretCode.get_length()
	    << " digits" << endl;
    vector<int> guess_vector;
    int s;

    for(int i = 0; i < secretCode.get_length(); i++) {
        cout << "Enter digit #" << i << ":" << endl;
        cin >> s;
        guess_vector.push_back(s);
    }

    code guess = code(secretCode.get_length(), secretCode.get_digitRange());
    guess.setCode(guess_vector);
    return guess;
}; // end humanGuess()

response mastermind::getResponse(code guess)
// function to get the response (number of correct and incorrect digits) of the
// code
{
    response answer = response(secretCode, guess);
    return answer;
};

bool mastermind::isSolved(response answer)
// checks if the user has guessed the code by comparing the length of the secret
// code to the number of correct digits in the user's guess
{
    if(secretCode.get_length() == answer.getNumberCorrect()) {
        return true;
    }
    return false;
}

void mastermind::playGame()
// initiates gameplay
{
    // print key for debug purposes
    printSecretCode();

    // continuously takes user input and checks until game ends
    bool flag = true;
    while(flag == true && guessCounter < 10) {
        code guess      = humanGuess();
        response answer = getResponse(guess);
        cout << answer;
        cout << endl;
        flag = !isSolved(answer);
        guessCounter++;
    }

    // win if game ended before 10 turns
    if(guessCounter < 10) {
        cout << "You won in " << guessCounter << " guesses!\n";
    } else {
        cout << "You lose! Reached a max of 10 guesses.\n";
    }
} // end playGame()
