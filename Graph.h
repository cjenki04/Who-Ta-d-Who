//Graph.h - header file for Graph class
// 	   By - Conor Jenkinson

#include<queue>
using namespace std;
class Graph
{
public:
        

	Graph();   //default constructor
	Graph(int nodes); //constructor with specified nodes
	Graph(const Graph &source); //copy constructor
    ~Graph(); // destructor

	bool createEdge(int v1, int v2);// creates edge between vertex 1 and 2
	bool isAdjacent(int v1, int v2);// true if edge between 1 and 2
	void print_matrix(); //prints out adjacency matrix
	bool markVertex(int v); //marks vertex as visited
	bool isMarked(int v);   //returns true if vertex was visited
	void unmarkAll();       //unmarks all verticies
	void allocateArrays();  //used to initialize arrays
	bool unmarkVertex(int v); //unmarks a specified vertex
	

private:
	
    int node_count;
	bool  *markedVertices;
	bool **adjacencyMatrix;
};


