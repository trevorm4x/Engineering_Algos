#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>
#include <string>

class dictionary {
public:
  dictionary();
  void readWords();
  friend void operator<<(ostream &ostr, dictionary &wordlist);
  void wordSorter();
  int wordFinder(string key);

private:
  vector<string> words;
};
