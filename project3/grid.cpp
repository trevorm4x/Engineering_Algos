#include "grid.h"

grid::grid() {
	gridFiller();
}

void grid::gridFiller() {
	string response;
	cout << "Please enter the name of the file that you would like to use as your input with its filename (ex: dictionary.txt): " << endl;
	cin >> response;
	
	fstream myFile;
	myFile.open(response.c_str(), ios::in);
	int rows, cols;
	if (myFile.is_open())
		//ensures that the file is opened properly before reading in words
	{
		myFile >> rows >> cols;
		mat.resize(rows, cols);

		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				char temp;
				myFile >> temp;
				mat[j][i] = temp;
			}
		}
	}
	else
		//prints error message in case the file is not able to be opened
	{
		cout << "File was not opened" << endl;
	}
}

