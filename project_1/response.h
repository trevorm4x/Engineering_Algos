#include <iostream>
#include "code.h"
using namespace std;

class response{

    public:
        response(code guess);
        void set(int correct, int incorrect);
        int getNumberCorrect(code guess);
        int getNumberIncorrect(code guess);
        friend bool operator ==(const response& lhs, const response& rhs);
        friend void operator <<(ostream& ostr, response rhs);

    private:
        static int numberCorrect;
        static int numberIncorrect;
};