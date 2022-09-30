// Project 1 Part A
// Trevor Smith
// Andrew Nguy
// Viraj Lawande
//
// code class header file that contains function prototypes for the class

#include <iostream>
#include <vector>

using namespace std;

class code 
{
    public:

    //constructor
    code(int n, int m);

    // basic operations modeling "mastermind" game rules
    void initializeRandomCode();
    void setCode(vector<int> guess);
    int checkCorrect(code guess);
    int checkIncorrect(code guess);
    void printCode();

    // accessors
    int get_length() 
    {
        return length;
    }

    int get_digitRange() 
    {
        return digitRange;
    }

    vector<int> get_code() 
    {
        return thecode;
    }

    private:
    int length, digitRange;
    vector<int> thecode;
    pair<code, code> removeCorrect(code guess);
    int countDigit(int digit);
};