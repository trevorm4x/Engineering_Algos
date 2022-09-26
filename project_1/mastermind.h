#include "code.h"
#include "response.h"
#include <cstddef>

class mastermind{

    public:
        mastermind();
        mastermind(int n, int m);
        void playGame();

        // Put in private when class is done with testing
        void printSecretCode();
        code humanGuess();
        response getResponse(code guess);
        bool isSolved(response response);

    private:
        // trevor: changed this name from 'thecode' to 'secretCode'
        code secretCode;
        int guessCounter;

};