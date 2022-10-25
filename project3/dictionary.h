#include <iostream>
#include "d_matrix.h"
#include "d_except.h"
#include <string>
#include <fstream>

class dictionary
{
public:
	dictionary();
	void readWords();
	friend void operator <<(ostream& ostr, dictionary& wordlist);
	void wordSorter();
	int wordFinder(string key);

private:
	vector<string> words;

};

