#include "dictionary.h"

dictionary::dictionary()
// constructor for the dictionary class. Inputs the words from the dictionary
// file into the words vector within the class, and sorts the vector using
// selection sort
{
  words = {};
  readWords();
  wordSorter();
}

void dictionary::readWords()
// function to read the words in from the dictionary text file
{
  fstream myFile;
  myFile.open("Dictionary", ios::in);
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
  // prints error message in case the file is not able to be opened
  {
    cout << "File was not opened" << endl;
  }
} // end readWords()

void operator<<(ostream &ostr, dictionary &dictionary)
// function to overload the << operator to print out all words in the
// dictionary object being passed into the operator
{
  for (int i = 0; i < dictionary.words.size(); i++) {
    cout << dictionary.words[i] << endl;
  }
}

void dictionary::wordSorter()
// function to sort the words vector using a selection sort algorithm
{
  int n = words.size() - 1;
  int min;
  for (int i = 0; i < n - 1; i++) {
    min = i;

    for (int j = i + 1; j < n - 1; j++) {
      if (words[j] < words[min]) {
        min = j;
      }
    }
    string placeholder = words[i];
    words[i] = words[min];
    words[min] = placeholder;
  }
} // end wordSorter()

int dictionary::wordFinder(string key)
// untested function to handle word lookups in the words vector
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
    } else if (key < midValue) {
      last = mid - 1;
    } else {
      first = mid + 1;
    }
  }
  return -1;
} // end wordFinder()