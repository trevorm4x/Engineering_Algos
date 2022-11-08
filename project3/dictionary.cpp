#include "dictionary.h"
#include "heap.h"

dictionary::dictionary(int sortType)
// constructor for the dictionary class. Inputs the words from the dictionary
// file into the words vector within the class, and sorts the vector using
// selection sort
{
	readWords();
	if (sortType == 0) {
		selectionSort();
	}

	if (sortType == 1) {
		quickSort(0, words.size() - 1);
	}

	if (sortType == 2){
		heapSort();
	}
}

void dictionary::readWords()
// function to read the words in from the dictionary text file
{
	fstream myFile;
	myFile.open("dictionary.txt", ios::in);
	if (myFile.is_open())
		// ensures that the file is opened properly before reading in words
	{
		string line;
		int i = 0;
		while (getline(myFile, line))
			// continuously pushes each line from the txt file as a string to the words
			// array until the last line of the txt document is reached
		{
			// there's like a CRLF or whatever at the end of each line we have to
			// remove.
      line.pop_back();
			words.push_back(line);
			++i;
		}
	} else 
	{
	// prints error message in case the file is not able to be opened
		cout << "File was not opened" << endl;
	}
} // end readWords()

void operator<<(ostream& ostr, dictionary& dictionary)
// function to overload the << operator to print out all words in the
// dictionary object being passed into the operator
{
	for (int i = 0; i < dictionary.words.size(); i++) {
		cout << dictionary.words[i] << endl;
	}
}

void dictionary::selectionSort()
// function to sort the words vector using a selection sort algorithm
{
	int n = words.size() - 1;
	int min;
	for (int i = 0; i < n - 1; i++) 
	{
		min = i;
		for (int j = i + 1; j < n - 1; j++) 
		{
			if (words[j] < words[min]) 
			{
				min = j;
			}
		}
		string placeholder = words[i];
		words[i] = words[min];
		words[min] = placeholder;
	}
} // end selectionSort()

int dictionary::binarySearch(string key)
// function to handle word lookups in the words vector
// using a binary search algorithm
{
	int first = 0;
	int last = words.size() - 1;
	int mid;
	string midValue;

	while (first <= last) {
		mid = (first + last) / 2;
		midValue = words[mid];

		if (key == midValue) {
			return mid;
		}
		else if (key < midValue) {
			last = mid - 1;
		}
		else {
			first = mid + 1;
		}
	}
	return -1;
} // end wordFinder()


void dictionary::quickSort(int left, int right)
{
	if (left < right)
	{
		int s = partition(left, right);
		quickSort(left, s - 1);
		quickSort(s + 1, right);
	}
}


int dictionary::partition(int p, int r) 
// partition function that selects the last element of the vector as a pivot,
//puts the pivot at the correct position in a sorted array
{
	string x = words[r];
	int i = p - 1;

	for (int j = p; j < r; j++) 
	{
		if (words[j] <= x) 
		{
			i++;
			swap(words[i], words[j]);
		}
	}

	swap(words[i + 1], words[r]);
	return (i + 1);
}

void dictionary::heapSort() {
	heap<string> maxHeap = heap<string>(words);
  words = maxHeap.heapsort();
}