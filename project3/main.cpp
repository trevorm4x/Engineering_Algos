#include "dictionary.h"
#include "grid.h"

using namespace std;

void findMatches(dictionary d, grid g)
// findMatches function that takes in a sorted dictionary and a grid
//  and creates all possible words from the grid. it then searches for them in
//  the dictionary and prints the matches to the screen
{
  // searches for words across a grid object, looking in each direction and
  // referencing words in dictionary
  int num_row = g.mat.rows();
  int num_col = g.mat.cols();
  std::string keyword = "";

  // coordinate directions to iterate and check for words
  int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  // iterate on each coordinate of the grid and iterate on each of the eight
  // directions until reaching the edge of the grid on either side.
  for (int i = 0; i < num_row; i++) {
    for (int j = 0; j < num_col; j++) {
      for (int dir = 0; dir < 8; dir++) // handles searching in 8 directions
      {
        // placeholder for building up words from grid element
        keyword = "";
        // itererators for adding characters to our word
        int i_0 = i;
        int j_0 = j;
        // checks if we have searched outside the grid
        while ((i_0 >= 0) && (i_0 < num_row) && (j_0 >= 0) && (j_0 < num_col)) {
          keyword.push_back(g.mat[i_0][j_0]);
          // search only for words of length 5 or more
          if (keyword.length() >= 5) {
            // implement binary search
            if (d.binarySearch(keyword) >= 0) {
              cout << "Found: " << keyword << endl;
            }
          }
          // increment coordiates by given direction
          i_0 += x[dir];
          j_0 += y[dir];
        }
      }
    }
  }
}

void search(int sortType)
// search function that takes in an integer to determine which sorting algorithm
// the user would like to use, creates a dictionary sorted using the appropriate
// method, creates a character matrix from the filename that the user inputs
//  and then calls the findMatches() function to find the words from the grid
//  that match the ones in the dictionary
{
  dictionary dict = dictionary(sortType);
  string response;
  cout << "Please enter the filename of the grid you would like to use" << endl;
  cin >> response;
  grid inputGrid = grid(response);
  cout << "Here's all the words I could find:\n";
  findMatches(dict, inputGrid);
}

int main()
// main function that prompts user to select which sorting algorithm they'd like
// to use, and then calls the search function
{
  int sortType;
  cout << "Please input the appropriate number for sorting algorithm you would "
          "like to use"
       << endl;
  cout << "0: selectionSort" << endl;
  cout << "1: quickSort" << endl;
  cout << "2: heapSort" << endl;
  cin >> sortType;

  search(sortType);
}

// We tested the duration for each sort on Andrew's laptop and found
//  selectionSort: 4 minutes, 46 seconds
//  quickSort: 1 second
//  heapSort: 2 seconds