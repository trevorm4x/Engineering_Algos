#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>

// header file for the grid class

class grid {
private:
  void gridFiller(string response);

public:
  matrix<char> mat;
  grid(string response);
};
