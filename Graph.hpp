#include <stdio.h>
#include <stdlib.h>
#include "Graph_Node.hpp"

class Graph{
public:
    Graph_Node* find_vertices(char vertex_data);   //returns a pointer to the vertex, or NULL if it doesnt exist - protects the vertices array
    bool add_vertex(char vertex_data);    //add a vertex with no edge, returns false if the vertex already exists or the char is not allowed 
    bool add_edge_vertex(char vertex_data, char connected_vertex_data, int weight); //add edge to vertex, returns false if the edge already exists, 
                                                                                    //or if the vertex doesnt exist, or if the char is not allowed

    void print_graph();                         //prints each node in the graph with its edges and their weights

    //dfs
    bool dfs(char start_at, char end_at);       //preforms a depth first search;

    //dijkstra
    bool dijkstra(char start_at, char end_at);  //preforms a dijkstra search;

    Graph();
private:
    //private functions, called by DFS and Dijkstra
    void clear_search();
    bool dfs1(char start_at, char end_at);
    //general
    Graph_Node Vertices[26];    //array that stores all vertices
};