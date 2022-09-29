#include "mastermind.h"
#include <stdio.h>

using namespace std;

mastermind::mastermind(int n, int m) : secretCode(n, m){
    secretCode.initializeRandomCode();
    guessCounter = 0;
};

mastermind::mastermind() : secretCode(5, 10) {
    secretCode.initializeRandomCode();
    guessCounter = 0;
};

void mastermind::printSecretCode() {
    cout << "Shhhh! the secret Sequence is " << endl;
    secretCode.printCode();
};

code mastermind::humanGuess() {
    cout << "Please enter your guess of " << secretCode.get_length() << " digits" << endl;
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
};

response mastermind::getResponse(code guess) {
    response answer = response(secretCode, guess);
    return answer;
};

bool mastermind::isSolved(response answer) {
    if(secretCode.get_length() == answer.getNumberCorrect()) {
        return true;
    }
    return false;
}

void mastermind::playGame() {
    //print key for debug purposes
    printSecretCode();

    //continuously takes user input and checks until game ends
    bool flag = true;
    while(flag == true && guessCounter < 10) {
        code guess = humanGuess();
        response answer = getResponse(guess);
        cout << answer;
        cout << endl;
        flag = !isSolved(answer);
        guessCounter++;
    }
    
    //win if game ended before 10 turns
    if(guessCounter < 10) {
        cout << "You won in " << guessCounter << " guesses!\n";
    } else {
        cout << "You lose! Reached a max of 10 guesses.\n";
    }
}

/*
int main(){
    // code used for testing mastermind object.
    // proves that secret code is stored correctly, humanGuess is
    // stored correctly, and endgame is evaluated correctly.

    mastermind game = mastermind();
    game.printSecretCode();
    code guess = game.humanGuess();
    response answer = game.getResponse(guess);
    cout << "Game is solved? " << game.isSolved(answer) << "\n";
    return 1;
}
*/