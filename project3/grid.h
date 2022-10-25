#include <iostream>
#include "d_except.h"
#include "d_matrix.h"
#include <fstream>

class grid
{
private:
	void gridFiller();
	
public:
	matrix<char> mat;
	grid();
};

