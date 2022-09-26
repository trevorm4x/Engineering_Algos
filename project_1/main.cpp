#include "mastermind.h"
#include <stdio.h>


int main() {
    int n;
    int m;
    std::cout << "Type n and m\n";
    std::cin >> n >> m;
    mastermind game = mastermind(n, m);
    // game.playGame();
    return 1;
};