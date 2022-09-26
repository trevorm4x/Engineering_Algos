#include "mastermind.h"

void mastermind::printSecretCode(){

};


code mastermind::humanGuess(){

};


response mastermind::getResponse(code guess){
    response answer = response();
    answer.set(
        secretCode.checkCorrect(guess),
        secretCode.checkIncorrect(guess)
    );
    return answer;
};


bool mastermind::isSolved(response answer) {
    if (thecode.get_length() == answer.getNumberCorrect()) {
        return true;
    }
    return false;
}