#include <stdio.h>
#include <stdlib.h>
#include "Graph_Node.hpp"

class Graph{
public:
    Graph_Node* find_vertices(char vertex_data);   //returns a pointer to the vertex, or NULL if it doesnt exist
    bool add_vertex(char vertex_data);    //add a vertex with no edge, returns false if the vertex already exists or its an unallowed char
    bool add_edge_vertex(char vertex_data, char connected_vertex_data, int weight); //add edge to vertex, returns false if the edge already exists, or if the vertex doesnt exist, or if the char is now allowed

private:
    Graph_Node Vertices[26];    //array that stores all vertices
};