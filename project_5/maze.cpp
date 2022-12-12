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
      bool solveMazeRecursive(graph &g, node *v);
      bool solveMazeIterative(graph &g, node *v);

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
   // prints the path and clears the vector to be reused
   if (path.size() == 0) {
      cout << "No path exists.\n";
      return;
   }
   for (auto s : path) {
      cout << s << ",\n";
   }
   for (auto s : path) {
      popStep();
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
   // check for nodes adjacent to the given maze coordinate
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
   // search the maze for a node with node_id and return its coord location
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

bool maze::solveMazeIterative(graph &g, node* v) {
   // solve maze with depth-first stack-based search
   stack<node*> thestack;
   stack<string> thesteps;

   int i_goal = rows - 1, j_goal = cols - 1;

   thestack.push(v);
   thesteps.push("");
   v->visit();

   while (!thestack.empty()) {
      node* v = thestack.top();
      thestack.pop();
      string step = thesteps.top();
      thesteps.pop();

      struct coord c = findNode(v->getId());
      if (!v->isVisited()) {
         cout << step << endl;
         // printf("c=(%d, %d)\n", c.x, c.y);
         v->visit();
      }

      int xdirs[4] = {-1, 1, 0, 0};
      int ydirs[4] = {0, 0, -1, 1};
      string sdirs[4] = {"up", "down", "left", "right"};
      // print(c.x, c.y, i_goal, j_goal);

      if (c.x == i_goal && c.y == j_goal) {
         // reached goal
         while (!thestack.empty()) {
            // struct coord c = findNode(thestack.top()->getId());
            // printf("c=(%d, %d)\n", c.x, c.y);
            // string step = thesteps.top();
            // cout << step << endl;
            thestack.pop();
            thesteps.pop();
         }
         cout << "Maze finished!\n";
      }

      bool hasNeighbor = false;
      string laststep = "";

      for (int d = 0; d < 4; d++) {
         int isnode = getMap(c.x + xdirs[d], c.y + ydirs[d]);
         if (isnode >= 0) {
            node* next = g.getNode(isnode);
            if (!next->isVisited()) {
               // v has unvisited neighbor
               hasNeighbor = true;
               // pushStep(sdirs[d]);
               // next->visit();
               thestack.push(next);
               thesteps.push(sdirs[d]);
               // pushStep(sdirs[d]);
               laststep = sdirs[d];
            }
         }
      }
   }


   return true;
}

bool maze::solveMazeRecursive(graph &g, node* v) {
   // solve maze using recursive depth-first search

   struct coord c = findNode(v->getId());

   v->visit();

   int goal_i = rows - 1, goal_j = cols - 1;

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
            bool solved = solveMazeRecursive(g, next);
            if (solved) return true;
            popStep();
         }
      }
   }

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
      graph h;
      while (fin && fin.peek() != 'Z')
      {
         maze m(fin);
         m.mapMazeToGraph(m, g);
         cout << g;
         node* start = g.getNode(m.getMap(0, 0));
         m.solveMazeRecursive(g, start);
         m.printPath();

         cout << endl << "trying iterative!\n\n";
         cout << "The print outs for this puzzle are different; when you reach a dead end,\
immediately return to the last branch and continue from there.\n";
         m.mapMazeToGraph(m, h);
         node* start2 = h.getNode(m.getMap(0, 0));
         m.solveMazeIterative(h, start2);
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
