#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>
#include <string>

class dictionary {
	public:
		dictionary(int sortType);
		void readWords();
		friend void operator<<(ostream &ostr, dictionary &wordlist);
		void selectionSort();
		int binarySearch(string key);
		void quickSort(int left, int right);
		int partition(int p, int r);
		void heapSort();

	private:
		vector<string> words;
};
