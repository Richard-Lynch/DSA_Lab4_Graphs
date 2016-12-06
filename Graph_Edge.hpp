#include <stdio.h>
#include <stdlib.h>
#include "Graph_Node.hpp"

class Graph_Edge{
public:
    //basic
    Graph_Node* vertex; //the vertex being connected to by the edge
    int weight;         //the weight of the edge          

    Graph_Edge* next_edge;  //the next edge in the linked list

private:

}