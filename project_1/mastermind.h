// Project 1 Part B
// Trevor Smith
// Andrew Nguy
// Viraj Lawande
//
// mastermind class header file that contains function prototypes for the class

#include "response.h"
#include <cstddef>

class mastermind {

    public:
        mastermind();
        mastermind(int n, int m);
        void playGame();

    private:
        void printSecretCode();
        code humanGuess();
        response getResponse(code guess);
        bool isSolved(response response);
        code secretCode;
        int guessCounter;
};