#include "Graph_Edge.hpp"
#include "Graph_Node.hpp"

Graph_Edge::Graph_Edge(Graph_Node* Vertex, int Weight, Graph_Edge* Next_edge){
    vertex = Vertex;
    weight = Weight;
    next_edge = Next_edge;
}