#include "grid.h"

//source file for the grid class

grid::grid(string response) 
{
	gridFiller(response); 
}

void grid::gridFiller(string response) 
{
	fstream myFile;
	myFile.open(response.c_str(), ios::in);
	int rows, cols;
	if (myFile.is_open())		// ensures that the file is opened properly before reading in words
	{
		myFile >> rows >> cols;
		mat.resize(rows, cols);

		for (int i = 0; i < cols; i++) 
		{
			for (int j = 0; j < rows; j++) 
			{
				char temp;
				myFile >> temp;
				mat[j][i] = temp;
			}
		}
	} else			// prints error message in case the file is not able to be opened
	{
		cout << "File was not opened" << endl;
	}
}
