#include "d_except.h"
#include "d_matrix.h"
#include <fstream>
#include <iostream>

class grid {
private:
  void gridFiller();

public:
  matrix<char> mat;
  grid();
};
