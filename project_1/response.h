#include <iostream>
using namespace std;

class response{

    public:
        response();
        void set(int correct, int incorrect);
        int getNumberCorrect();
        int getNumberIncorrect();
        friend response operator== (response lhs, response rhs);
        friend response operator<< (ostream& ostr, response rhs);

    private:
        int numberCorrect;
        int numberIncorrect;
};