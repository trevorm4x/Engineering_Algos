#include "code.h"
#include <iostream>
using namespace std;

class response {

    public:
    response(code secretCode, code guess);
    void set(code secretCode, code guess);
    int getNumberCorrect();
    int getNumberIncorrect();
    friend bool operator==(const response& lhs, const response& rhs);
    friend void operator<<(ostream& ostr, response rhs);

    private:
    int numberCorrect;
    int numberIncorrect;
};