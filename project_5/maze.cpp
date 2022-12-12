// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

struct coord {
   int x;
   int y;
};

class maze
{
   public:
      maze(ifstream &fin);
      void print(int,int,int,int);
      bool isLegal(int i, int j);

      void setMap(int i, int j, int n);
      int getMap(int i, int j) const;
      void mapMazeToGraph(maze &m, graph &g);

      void checkNeighborsCreateEdges(int i, int j, graph &g);
      bool solveMaze(graph &g, node *v);

      coord findNode(int node_id);

      void pushStep(string step);
      void popStep();
      void printPath();

   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
      vector<string> path;
};

void maze::printPath() {
   if (path.size() == 0) {
      cout << "No path exists.\n";
      return;
   }
   for (auto s : path) {
      cout << s << ",\n";
   }
   cout << "finish!\n";
}

void maze::pushStep(string step) {
   path.push_back(step);
}

void maze::popStep() {
   path.pop_back();
}

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n. 
{
   map[i][j] = n;
}

int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph and node number
{
   // if legal
   if (i >=0 && i < rows && j >= 0 && j < cols)
      return map[i][j];
   // otherwise -1
   return -1;
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
	 fin >> x;
	 if (x == 'O')
            value[i][j] = true;
	 else
	    value[i][j] = false;
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows-1 || goalJ < 0 || goalJ > cols-1)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows-1 || currJ < 0 || currJ > cols-1)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";	  
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows-1 || j < 0 || j > cols-1)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(maze &m, graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
   int count = 0;
   for (int p = 0; p < rows; p++) {
      for (int q = 0; q < cols; q++) {
         if (value[p][q] == true) {
            node n;
            n.setNode(count, 1, false, false);
            // printf("making node(%d, %d, %d).\n", p, q, count);
            g.addNode(n);
            setMap(p, q, count);
            count++;
            // check above/below/left/right and find edges
         }
         else {
            setMap(p, q, -1);
         }
      }
   }
   for (int p = 0; p < rows; p++) {
      for (int q = 0; q < cols; q++) {
         if (getMap(p, q) >= 0)
            checkNeighborsCreateEdges(p, q, g);
      }
   }
}

void maze::checkNeighborsCreateEdges(int i, int j, graph &g) {
   int xdirs[4] = {-1, 1, 0, 0};
   int ydirs[4] = {0, 0, -1, 1};

   int me_id = getMap(i, j);

   for (int dir = 0; dir < 4; dir++) {
      int node_id = getMap(i + xdirs[dir], j + ydirs[dir]);
      if (node_id >= 0) {
         // found a node
         g.getNode(node_id);
         // printf("found node connecting (%d, %d): node %d and (%d, %d): node %d.\n",
            // i, j, me_id, i + xdirs[dir], j + ydirs[dir], node_id);
         g.addEdge(me_id, node_id, 1);
      }
   }
}

coord maze::findNode(int node_id) {
   struct coord c;
   for (int p = 0; p < rows; p++) {
      for (int q = 0; q < cols; q++) {
         if (getMap(p, q) == node_id) {
            c.x = p;
            c.y = q;
            return c;
         }
      }
   }
   c.x = -1;
   c.y = -1;
   return c;
}

bool maze::solveMaze(graph &g, node* v) {

   struct coord c = findNode(v->getId());

   v->visit();

   int goal_i = rows - 1, goal_j = cols - 1;
   // print(c.x, c.y, goal_i, goal_j);

   if (v->getId() == getMap(goal_i, goal_j))
      return true;

   int xdirs[4] = {-1, 1, 0, 0};
   int ydirs[4] = {0, 0, -1, 1};
   string sdirs[4] = {"up", "down", "left", "right"};

   for (int d = 0; d < 4; d++) {
      int isnode = getMap(c.x + xdirs[d], c.y + ydirs[d]);
      if (isnode >= 0) {
         node* next = g.getNode(isnode);
         if (!next->isVisited()) {
            pushStep(sdirs[d]);
            bool solved = solveMaze(g, next);
            if (solved) return true;
            popStep();
         }
      }
   }

   /*
   for (int node_id = 0; node_id < g.numNodes(); node_id++) {
      if (g.isEdge(v->getId(), node_id)) {
         node* othernode = g.getNode(node_id);
         if (!othernode->isVisited()) {
            bool solved = solveMaze(g, othernode);
            if (solved) return true;
         }
      }
   }
   */

   //  v->unMark();

   return 0;
}


int main()
{
   char x;
   ifstream fin;

   // Read the maze from the file.
   string fileName = "Maze 3";

   fin.open(fileName.c_str());
   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {

      graph g;
      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.mapMazeToGraph(m, g);
         cout << g;
         node* start = g.getNode(m.getMap(0, 0));
         m.solveMaze(g, start);
         m.printPath();
      }

   } 
   catch (indexRangeError &ex) 
   { 
      cout << ex.what() << endl; exit(1);
   }
   catch (rangeError &ex)
   {
      cout << ex.what() << endl; exit(1);
   }
}
