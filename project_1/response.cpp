#include "response.h"

// Viraj
response::response(code secretCode, code guess) {
    set(secretCode, guess);
}

int response::getNumberCorrect() {
    return numberCorrect;
}

int response::getNumberIncorrect() {
    return numberIncorrect;
}

void response::set(code secretCode, code guess) {
    numberCorrect   = secretCode.checkCorrect(guess);
    numberIncorrect = secretCode.checkIncorrect(guess);
}

bool operator==(response& lhs, response& rhs) {
    if((lhs.getNumberCorrect() == rhs.getNumberCorrect()) &
    (lhs.getNumberIncorrect() == rhs.getNumberIncorrect())) {
        return true;
    }
    return false;
}

void operator<<(ostream& ostr, response rhs) {
    ostr << "Number Correct: " << rhs.numberCorrect << endl;
    ostr << "Number Incorrect: " << rhs.numberIncorrect << endl;
}