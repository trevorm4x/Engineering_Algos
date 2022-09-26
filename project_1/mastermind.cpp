#include "mastermind.h"
#include <stdio.h>

using namespace std;

mastermind::mastermind(int n, int m) : secretCode(n, m) {
};


mastermind::mastermind() : secretCode(5, 10) {
    secretCode.initializeRandomCode();
};


void mastermind::printSecretCode(){
	cout << "Shhhh! the secret Sequence is " << endl;
    secretCode.printCode();
};


code mastermind::humanGuess(){
   	cout << "Please enter your guess of " << secretCode.get_length() << " digits" << endl;
	vector<int> guess_vector;
	int s;
	for (int i = 0; i < secretCode.get_length(); i++) {
		cout << "Enter digit #" << i << ":" << endl;
		cin >> s;
		guess_vector.push_back(s);
	}
	code guess = code(secretCode.get_length(), secretCode.get_digitRange());
    guess.setCode(guess_vector);
    return guess;
};


// commented for testing, uncomment when response class is finished

// response mastermind::getResponse(code guess){
    // response answer = response();
    // answer.set(
        // secretCode.checkCorrect(guess),
        // secretCode.checkIncorrect(guess)
    // );
    // return answer;
// };
// 
// 
// bool mastermind::isSolved(response answer) {
    // if (secretCode.get_length() == answer.getNumberCorrect()) {
        // return true;
    // }
    // return false;
// }


int main(){
    mastermind game = mastermind();
    game.printSecretCode();
    code guess = game.humanGuess();
    // response answer = game.getResponse(guess);
    // cout << game.isSolved(answer);
    return 1;
}