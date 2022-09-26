#include "response.h"

// Viraj

response::response(code guess) {
    set(getNumberCorrect(guess), getNumberIncorrect(guess));
}

int response::getNumberCorrect(code guess) {
    int correct;
    correct = guess.checkCorrect(guess);
    return correct;
}

int response::getNumberIncorrect(code guess) {
    int incorrect;
    incorrect = guess.checkIncorrect(guess);
    return incorrect;
}

void response::set(int correct, int incorrect) {
    numberCorrect = correct;
    numberIncorrect = incorrect;
}

bool operator ==(const response& lhs, const response& rhs) {
    if (lhs == rhs) {
        return true;
    }
    return false;
}

void operator <<(ostream& ostr, response rhs) {
    ostr << "Number Correct: " << response::numberCorrect << endl;
    ostr << "Number Incorrect: " << response::numberIncorrect << endl;
}