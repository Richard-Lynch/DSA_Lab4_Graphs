#include <stdio.h>
#include <stdlib.h>

class Graph_Node;

class Graph_Edge{
public:
    //basic
    Graph_Node* vertex; //the vertex being connected to by the edge
    int weight;         //the weight of the edge          

    Graph_Edge* next_edge;  //the next edge in the linked list

    Graph_Edge(Graph_Node* Vertex, int Weight, Graph_Edge* Next_edge);

private:
};