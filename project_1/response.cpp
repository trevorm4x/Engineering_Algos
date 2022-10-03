// Project 1 Part B
// Trevor Smith
// Andrew Nguy
// Viraj Lawande
//
// response class header file that contains function prototypes for the class

#include "response.h"

response::response(code secretCode, code guess)
// constructor that uses the set function to set variables numberCorrect and
// numberIncorrect equal to their respective values from the user's guess
{
    set(secretCode, guess);
}

int response::getNumberCorrect()
// function to access the number of correct digits from outside the class
{
    return numberCorrect;
}

int response::getNumberIncorrect()
// function to access the number of incorrect digits from outside the class
{
    return numberIncorrect;
}

void response::set(code secretCode, code guess)
// function to set the numberCorrect and numberIncorrect variables equal to the
// number of correct and incorrect digits in the user's guess
{
    numberCorrect   = secretCode.checkCorrect(guess);
    numberIncorrect = secretCode.checkIncorrect(guess);
}

bool operator==(response& lhs, response& rhs)
// function to overload the == operator as a comparison operator for the
// response class
{
    if(lhs.getNumberCorrect() == rhs.getNumberCorrect()) {
        return true;
    }
    return false;
}

void operator<<(ostream& ostr, response rhs)
// function to overload the << operator so that it outputs the number of correct
// and incorrect digits in a guess
{
    ostr << "Number Correct: " << rhs.numberCorrect << endl;
    ostr << "Number Incorrect: " << rhs.numberIncorrect << endl;
}
