// Graph.cpp - implementation of Graph data stucture
//             adjacency Matrix is built based on the number of nodes
//             a true value in adjacency matrix represents and edge
//        By - Conor Jenkinson 
#include <iostream>
#include <queue>

#include "Graph.h"
using namespace std;


Graph::Graph()
{
        allocateArrays();
        node_count = 0;
        //
        // Initialize for empty graph
        //
        for (int i = 0; i < node_count; ++i) {
                for (int j = 0; j < node_count; ++j) {
                        adjacencyMatrix[i][j] = false;
                }
                markedVertices[i] = false;
        }
}
Graph::Graph(int nodes)
{

        node_count = nodes;
        allocateArrays();
        //
        // Initialize for empty graph
        //
        for (int i = 0; i < node_count; ++i) {
                for (int j = 0; j < node_count; ++j) {
                        adjacencyMatrix[i][j] = false;
                }
                markedVertices[i] = false;
        }
}
Graph::Graph(const Graph &source){
        node_count = source.node_count;\
        adjacencyMatrix = new bool * [node_count];
        markedVertices  = new bool   [node_count];
        for (int i = 0; i < node_count; ++i)
                adjacencyMatrix[i] = new bool [node_count];
        for (int i = 0 ; i < node_count; ++i){
                for (int j = 0 ; j < node_count ; ++j){
                        adjacencyMatrix[i][j] = 
                        source.adjacencyMatrix[i][j];
                }
                markedVertices[i] = source.markedVertices[i];
        }
}
void Graph::allocateArrays()
{
        adjacencyMatrix = new bool * [node_count];
        markedVertices  = new bool   [node_count];

        for (int i = 0; i < node_count; ++i)
                adjacencyMatrix[i] = new bool [node_count];
}
Graph::~Graph()
{       for (int i = 0 ; i < node_count; ++i){
                delete [] adjacencyMatrix[i];
                }
        delete [] adjacencyMatrix;
        delete [] markedVertices;
        node_count = 0;
}
bool Graph::createEdge(int v1, int v2)
{
        if (v1 >=0 and v1 <= node_count and v2 >= 0 and v2 <= node_count) {
                adjacencyMatrix[v1][v2] = true;
                return true;
        } 
        else {
                return false;
        }
}
bool Graph::isAdjacent(int v1, int v2)
{
        return adjacencyMatrix[v1][v2];
}
bool Graph::markVertex(int v)
{
        if (v >= 0 and v <= node_count) {
                markedVertices[v] = true;
                return true;
        }
        return false;
}
bool Graph::unmarkVertex(int v){
        if (v >= 0 and v <= node_count) {
                markedVertices[v] = false;
                return true;
        }
        return false;
}
bool Graph::isMarked(int v)
{
        return markedVertices[v];
}
void Graph::unmarkAll()
{
        for (int i = 0; i < node_count; ++i)
                markedVertices[i] = false;
}
void Graph::print_matrix(){
        for (int i = 0 ; i < node_count; i++){
                for (int j = 0 ; j < node_count; j++){
                        cout << adjacencyMatrix[i][j];
                }
                cout << endl;
        }
}










