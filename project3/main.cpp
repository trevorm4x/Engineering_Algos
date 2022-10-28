#include "dictionary.h"
#include "grid.h"


int x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int y[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void findMatches(dictionary d, grid g) {
	int num_row = g.mat.rows();
	int num_col = g.mat.cols();
	std::string keyword = "";
	
	for (int i = 0; i < num_row; i++) {
		for (int j = 0; j < num_col; j++) {
			for (int dir = 0; dir < 8; dir++) { // handles searching in 8 directions
				keyword = "";
				int i_0 = i;
				int j_0 = j;
				while ((i_0 >= 0) && (i_0 < num_row) && (j_0 >= 0) && (j_0 < num_col)) {
					keyword.push_back(g.mat[i_0][j_0]);
					if (keyword.length() >= 5) {
						if (d.wordFinder(keyword)) {
							std::cout << keyword << endl;
						}
					}
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