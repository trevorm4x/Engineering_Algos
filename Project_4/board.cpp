#include "board.h"

board::board()
{
    string response;
    cout << "Please enter the name of the sudoku puzzle file" << endl;
    cin >> response;
    readValues(response);
    initializeConflicts();
    updateConflicts();
    printBoard();
    cout << "\n\n\n";
    printConflicts();

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
        for (int columns = 0; columns < 9; columns++) {
            cout << puzzleBoard[rows][columns] << " ";
        }
        cout << endl;
    }
}

void board::initializeConflicts() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            conflicts[i][j] = { false, false, false, false, false, false, false, false, false };
        }
    }
}

void board::updateConflicts() {
    conflicts.resize(3, 9);
    // resizes the matrix to have 3 rows and 9 columns of boolean vectors
    // the first row represents the row conflicts for the puzzle
    // the second row represents the column conflicts for the puzzle
    // the third row represents the square conflicts for the puzzle
    for (int i = 0; i < 3; i++)
        //goes through the rows in the conflicts matrix
    {
        for (int j = 0; j < 9; j++)
            //goes through the columns in the conflicts matrix
        {
            if (i == 0)
                //updates the row conflicts
            {
                for (int k = 0; k < 9; k++) {
                    if (puzzleBoard[j][k] != -1) {
                        conflicts[i][j][puzzleBoard[j][k]] = true;
                    }
                }
            }

            if (i == 1)
                //updates column conflicts
            {
                for (int k = 0; k < 9; k++) {
                    if (puzzleBoard[k][j] != -1) {
                        conflicts[i][j][puzzleBoard[j][k]] = true;
                    }
                }
            }
            if (i == 2)
                //updates the square conflicts
            {
                //not yet implemented
            }
        }
    }
}

void board::printConflicts() {
    for (int rows = 0; rows < 3; rows++) 
    {
        for (int columns = 0; columns < 9; columns++) 
        {
            if (rows == 0) 
            //prints out conflicts for the rows
            {
                cout << "conflicts for row " << columns + 1 << ": {";
                for (int i = 0; i < 9; i++) {
                    cout << conflicts[rows][columns][i] << ", ";
                }
                cout << "}" << endl;
            }
            if (rows == 1) 
            //prints out conflicts for the columns
            {
                cout << "conflicts for column " << columns + 1 << ": {";
                for (int i = 0; i < 9; i++) {
                    cout << conflicts[rows][columns][i] << ", ";
                }
                cout << "}" << endl;
            }
            if (rows == 2) 
            //prints out conflicts for the squares
            {
                cout << "conflicts for square " << columns + 1 << ": {";
                for (int i = 0; i < 9; i++) {
                    cout << conflicts[rows][columns][i] << ", ";
                }
                cout << "}" << endl;
            }
        }
    }
}