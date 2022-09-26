#include <iostream>
#include "code.h"
using namespace std;

class response{

    public:
        response(code guess);
        void set(code guess);
        int getNumberCorrect();
        int getNumberIncorrect();
        friend bool operator ==(const response& lhs, const response& rhs);
        friend void operator <<(ostream& ostr, response rhs);

    private:
        static int numberCorrect;
        static int numberIncorrect;
};