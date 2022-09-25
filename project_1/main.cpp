#include "mastermind.h"
#include <stdio.h>


int main() {
    int n;
    int m;
    cout << "Type n and m\n";
    cin >> n >> m;
    mastermind game = mastermind(n, m);
    game.playGame();
}