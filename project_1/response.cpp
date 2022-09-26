#include "response.h"

// Viraj
response::response(code guess) {
    set(guess);
}

int response::getNumberCorrect() {
    return numberCorrect;
}

int response::getNumberIncorrect() {
    return numberIncorrect;
}

void response::set(code guess) {
    numberCorrect = guess.checkCorrect(guess);
    numberIncorrect = guess.checkIncorrect(guess);
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