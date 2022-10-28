#include "dictionary.h"
#include "grid.h"



void findMatches(dictionary d, grid g) {
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
			for (int dir = 0; dir < 8; dir++) { // handles searching in 8 directions
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
						if (d.wordFinder(keyword) >= 0) {
							std::cout << keyword << endl;
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

void search() {
	dictionary dict;
	grid grid;
	findMatches(dict, grid);
}

int main() {
	search();
}