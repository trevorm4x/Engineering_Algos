#include "board.h"

board::board() 
{
    string response;
    cout << "Please enter the name of the sudoku puzzle file" << endl;
    cin >> response;
    readValues(response);
    printBoard();
}

void board::readValues(string fileName) 
//readValues function that takes in a user inputted string and reads in the values from that string to the puzzle board
{
    fstream myFile;
    myFile.open(fileName.c_str(), ios::in);
    int rows, cols;
    if (myFile.is_open()) // ensures that the file is opened properly before
        // reading in words
    {
        rows = 9;
        cols = 9;
        puzzleBoard.resize(rows, cols);
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < cols; j++) 
            {
                char temp;
                myFile >> temp;
                if (temp != '.') {
                    puzzleBoard[i][j] = temp - '0';
                }
                else {
                    puzzleBoard[i][j] = -1;
                }
            }
        }
    }
    else // prints error message in case the file is not able to be opened
    {
        cout << "File was not opened" << endl;
    }
}

void board::printBoard() 
//printBoard function to print out the sudoku puzzle board and later on the conflicts
{
    //sudoku board
    for (int rows = 0; rows < 9; rows++) {
        for (int columns = 0; columns < 9; columns++){
            cout << puzzleBoard[rows][columns] << " ";
        }
        cout << endl;
    }
}