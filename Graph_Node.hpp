#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>

class Graph_Edge; 

class Graph_Node{
public:
    //basic
    char data;                      //the data stored in this node
    Graph_Edge* node_edges;

    //Dijkstra
    char destination;    //the destination vertex
    char parent;         //the vertex to go to next in the path
    bool is_permanent;          //is a permentant vertex, ie cant be updated
    bool was_checked;           //to ensure no loops
    int shortest_path;          //the shortest path from this vertex to the desired vertex
    
    //managing edges
    bool add_edge(Graph_Node* connected_vertex, int edge_weight);   //adds an edge between this node and another node with a given weight
    bool remove_edge(Graph_Node* connected_vertex, bool pair_deleted);                 //removes an edge, returns false if the edge doesnt exist
    bool change_weight_edge(Graph_Node* connected_vertex, int new_edge_weight, bool pair_edited);   //adjusts an edges weight

    Graph_Node();
    Graph_Node(char Data);
    ~Graph_Node();
private:

};

// struct Graph_Edge{
//     Graph_Node* vertex; //the vertex being connected to by the edge
//     int weight;         //the weight of the edge          
// };
