#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <iostream>

using namespace std;

 /*
 *n = length of code
 *m = range of digits
 */

class code
{
	int n, m;
	vector<int> codeSequence, guess;
	vector<int> correctedGuess, correctedSequence;
public:
	code(int, int);
	vector<int> randomCodeInitializer();
	int checkCorrect();
	int checkIncorrect();
	vector<int> getGuess();
	void printSecretSequence(vector<int>);
};

code::code(int x, int y) {
	n = x;
	m = y;
	srand(time(NULL));
	codeSequence = randomCodeInitializer();
	printSecretSequence(codeSequence);
	guess = getGuess();
}

vector<int> code::randomCodeInitializer() {
	vector<int> p;
	for (int i = 0; i < n; i++) {
		p.push_back(rand() % m);
	}
	return p;
}

int code::checkCorrect() {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (guess[i] == codeSequence[i]) {
			count++;
		}
		else {
			correctedSequence.push_back(codeSequence[i]);
			correctedGuess.push_back(guess[i]);
		}
	}
	return count;
}

int code::checkIncorrect() {
	int count = 0;
	int g;
	for (int i = 0; i < correctedGuess.size(); i++) {
		g = correctedGuess[i];
		for (int j = 0; j < correctedSequence.size(); j++) {
			if (g == correctedSequence[i]) {
				count++;
			}
		}
	}
	return count;
}

vector<int> code::getGuess() {
	cout << "Please enter your guess of " << n << " digits" << endl;
	vector<int> guess;
	int s;
	for (int i = 0; i < n; i++) {
		cout << "Enter digit #" << i << ":" << endl;
		cin >> s;
		guess.push_back(s);
	}
	return guess;
};

void code::printSecretSequence(vector<int> k) {
	cout << "Shhhh the secret Sequence is " << endl;
	for (int i = 0; i < k.size(); i++) {
		cout << k[i];
	}
	cout << endl;
}