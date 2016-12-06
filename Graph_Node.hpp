#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>

struct Graph_Edge;  //defined below Graph_Node

typedef std::vector<Graph_Edge> edge_vector;

class Graph_Node{
public:
    //basic
    char data;                      //the data stored in this node
    Graph_Edge* node_edges;
    edge_vector edge_list;

    //Dijkstra
    Graph_Node* destination;    //the destination vertex
    bool is_permanent;          //is a permentant vertex, ie cant be updated
    Graph_Node* parent;         //the vertex to go to next in the path
    int shortest_path;          //the shortest path from this vertex to the desired vertex
    bool was_checked;           //to ensure no loops

    //managing edges
    bool add_edge(Graph_Node* connected_vertex, int edge_weight);   //adds an edge between this node and another node with a given weight
    bool remove_edge(Graph_Node* connected_vertex);                 //removes an edge, returns false if the edge doesnt exist
    bool change_weight_edge(Graph_Node* connected_vertex, int new_edge_weight);   //adjusts an edges weight

    Graph_Node();
    ~Graph_Node();
private:

};

struct Graph_Edge{
    Graph_Node* vertex; //the vertex being connected to by the edge
    int weight;         //the weight of the edge          
};
