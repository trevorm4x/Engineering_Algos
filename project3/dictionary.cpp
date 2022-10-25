#include "dictionary.h"

dictionary::dictionary() 
//constructor for the dictionary class. Inputs the words from the dictionary file
//into the words vector within the class, and sorts the vector using selection sort
{
	readWords();
	wordSorter();
}

void dictionary::readWords() 
//function to read the words in from the dictionary text file
{
	fstream myFile;
	myFile.open("dictonary.txt", ios::in);
	if (myFile.is_open()) 
	//ensures that the file is opened properly before reading in words
	{
		string line;
		while (getline(myFile, line)) 
		//continuously pushes each line from the txt file as a string to the words array
		//until the last line of the txt document is reached
		{
			words.push_back(line);
		}
	}
	else 
	//prints error message in case the file is not able to be opened
	{
		cout << "File was not opened" << endl;
	}
}//end readWords()

void operator<<(ostream& ostr, dictionary& dictionary) 
// function to overload the << operator to print out all words in the
//dictionary object being passed into the operator
{
	for (int i = 0; i < dictionary.words.size(); i++) {
		cout << dictionary.words[i] << endl;
	}
}

void dictionary::wordSorter() 
//function to sort the words vector using a selection sort algorithm
{
	int n = words.size() - 1;
	cout << "line 31" << endl;
	int min;
	cout << "line 33" << endl;
	for (int i = 0; i < n - 1; i++) 
	{
		cout << "line 36" << endl;
		min = i;

		for (int j = i + 1; j < n - 1; j++) 
		{
			cout << "line 40" << endl;
			if (words[j] < words[min]) 
			{
				cout << "line 42" << endl;
				min = j;
			}
		}
		string placeholder = words[i];
		words[i] = words[min];
		words[min] = placeholder;
	}
}//end wordSorter()

int dictionary::wordFinder(string key) 
//untested function to handle word lookups in the words vector
//using a binary search algorithm
{
	int first = 0;
	int last = words.size() - 1;
	int mid;
	string midValue;

	while (first <= last) {
		mid = (first + last) / 2;
		midValue = words[mid];

		if (key == midValue){
			return mid;
		}
		else if (key < midValue) {
			last = mid;
		}
		else {
			first = mid;
		}
		
	}
}//end wordFinder()