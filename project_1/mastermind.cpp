#include "mastermind.h"


bool mastermind::isSolved(response response) {
    if (thecode.get_length() == response.getNumberCorrect()) {
        return true;
    }
    return false;
}