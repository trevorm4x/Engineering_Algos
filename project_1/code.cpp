// Project 1 Part A
// Trevor Smith
// Andrew Nguy
// Viraj Lawande
//
// Main program file for homework 1 part a. Contains implementation of all
// `code` class member functions, and a basic mockup of the game loop for testing.
//

#include "code.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <stdlib.h>

using namespace std;


code::code(int n, int m)
// `code` class constructor. Takes in n, the length of the code, and 
//  m, the range of digits [0, digitRange - 1].
{
    length = n;
    digitRange = m;
}


void code::initializeRandomCode()
// Fills the code vector with a random values on interval
// [0, code.digitRange - 1].
{
    for (int i = 0; i < length; ++i)
    {
        // Extend empty vector by one random number at a time.
        thecode.push_back(rand() % digitRange);
    }
}


void code::setCode(vector<int> guess)
// Manually set code's stored vector with, let's say an input guess.
{
    thecode = guess;
}


pair<code, code> code::removeCorrect(code guess)
// Takes in a guess and removes any values that are the correct digit in the
// correct location. `thecode` and guess.thecode must be the same length, for
// example as though they were both created while playing the same game. 
// Returns both "cleaned" vectors in a std::pair object.
{
    // create two empty vectors for "clean" guess and secret
    vector<int> clean_guess;
    vector<int> clean_secret;
    vector<int> code_guess = guess.get_code();

    // iterate on index through both vectors, collecting objects that are not
    // in the same place and digit into the two "cleaned" vectors.
    for (int i = 0; i < guess.get_length(); ++i)
    {
        // if different numbers in the same place,
        if (thecode[i] != code_guess[i])
        {
            // push them to their respective "cleaned" vectors.
            clean_secret.push_back(thecode[i]);
            clean_guess.push_back(code_guess[i]);
        }
    }

    // initialize two new `code` objects to store the "cleaned" vectors.
    code clean_code_guess = code(guess.get_length(), guess.get_digitRange());
    clean_code_guess.setCode(clean_guess);
    code clean_code_secret = code(guess.get_length(), guess.get_digitRange());
    clean_code_secret.setCode(clean_secret);
    return pair<code, code> (clean_code_secret, clean_code_guess);
} //end removeCorrect


int code::checkCorrect(code guess)
// Count the number of correct guesses by removing the correct guesses via
// `removeCorrect` then counting the number of guesses removed. `guess` must be
// the same length as `thecode`.
// Seeing as the argument is called "guess", this member function should be
// called by a secret code with the guess passed as a parameter.
{
    pair<code, code> cleaned_codes = removeCorrect(guess);
    return guess.get_length() - cleaned_codes.first.get_code().size();
}


int code::countDigit(int digit)
// Helper method to count the occurance of some `digit` in a `code` object's
// contained vector, returning the count as an `int`.
{
    int found_digits = 0;

    // iterate through vector values
    for(int v : thecode)
    {
        // if we found an occurance of the digit,
        if (v == digit)
        {
            // we count it.
            ++found_digits;
        }
    }
    return found_digits;
}


int code::checkIncorrect(code guess)
// Count the number of correct digits in incorrect locations by removing the
// correct guesses via `removeCorrect`, then counting the occurance of each
// digit in both "cleaned" guesses. 
{
    pair<code, code> cleaned_codes = removeCorrect(guess);
    int guess_digits;
    int secret_digits;
    int incorrectDigits = 0;

    // Count the occurances of each possible digit in both "cleaned" codes.
    for (int i = 0; i < digitRange; ++i)
    {
        guess_digits = cleaned_codes.second.countDigit(i);
        secret_digits = cleaned_codes.first.countDigit(i);

        // The maximum number of correct digits we are allowed to find in the
        // guess is the number of that digit in the secret code, so we need to
        // limit that count to the number in the secret code. However, we can't
        // count more correct digits in the guess than there are occurances in
        // the guess, so we get to use a nice and simple `min` call to model
        // these rules of the game.

        incorrectDigits += min(guess_digits, secret_digits);
    }
    return incorrectDigits;
} //end checkIncorrect


void code::printCode()
// Simple helper function to print the vector stored in a `code` object.
{
    cout << "{";
    for(int i : thecode)
    {
        cout << i << ",";
    }
    cout << "}\n";
}


code inputGuess(unsigned int n, unsigned int m)
// Simple helper function to create a `code` object from user input. This
// may be leveraged into a member function of the game class in part b.
{
    vector<int> code_guess;
    string char_guess;
    cout << "enter your guess:\n";
    cin >> char_guess;
    code codeGuess = code(n, m);

    if (char_guess.length() < n)
    {
        // Incorrect input is undefined behavior so I had fun with it.
        cout << "Guess too short, you lost your shot!\n";
        codeGuess.initializeRandomCode();
        return codeGuess;
    }

    if (char_guess.length() > n)
    {
        cout << "Guess too long, extra digits removed\n";
    }

    for (unsigned int i = 0; i < n; ++i)
    {
        // Cast to int by subtracting 48
        code_guess.push_back((int)char_guess[i] - 48);
    }

    cout << "\n";
    codeGuess.setCode(code_guess);
    return codeGuess;
} //end inputGuess


void my_test()
// Helper function to initialize a game and play one round with user input.
// May be used in the main game loop in part b.
{
    unsigned int n, m;
    cout << "Please enter the code length:\n";
    cin >> n;
    cout << "Please enter the code range 1-9:\n";
    cin >> m;

    code secretCode(n, m);
    secretCode.initializeRandomCode();
    code my_guess = inputGuess(n, m);
    secretCode.printCode();
    my_guess.printCode();
    cout << "Number of digits correct: ";
    cout << secretCode.checkCorrect(my_guess) << "\n";
    cout << "Number of digits incorrect: ";
    cout << secretCode.checkIncorrect(my_guess) << "\n";
} //end my_test

