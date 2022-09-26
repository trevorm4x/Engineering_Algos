#include "code.h"

void checkCorrect(code secret, code guess)
// Simple helper function to print out the results of the user's guess.
// May be included in the main game loop in part b.
{
    guess.printCode();
    cout << "Number of digits correct: ";
    cout << secret.checkCorrect(guess) << "\n";
    cout << "Number of digits incorrect: ";
    cout << secret.checkIncorrect(guess) << "\n";
}


int main()
// Play a sample game with predefined guesses. `secretCode` will be randomized,
// but is deterministic and will be the same each time the program is run.
{
    unsigned int n = 5;
    unsigned int m = 7;
    code secretCode = code(n, m);
    secretCode.initializeRandomCode();
    code guess_1 = code(n, m);
    guess_1.setCode({5, 0, 3, 2, 6});
    code guess_2 = code(n, m);
    guess_2.setCode({2, 1, 2, 2, 2});
    code guess_3 = code(n, m);
    guess_3.setCode({1, 3, 3, 4, 5});

    // Tell the user what happened
    secretCode.printCode();
    checkCorrect(secretCode, guess_1);
    checkCorrect(secretCode, guess_2);
    checkCorrect(secretCode, guess_3);
    return 0;
}