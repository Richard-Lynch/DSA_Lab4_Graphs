#include "Graph_Node.hpp"
#include "Graph_Edge.hpp"

//---MANAGING EDGES---
//---add edges---
bool Graph_Node::add_edge(Graph_Node* connected_vertex, int edge_weight){
    assert(connected_vertex);
    //add edge from this to connected
    Graph_Edge* new_edge = new Graph_Edge(connected_vertex, edge_weight, node_edges);
    node_edges = new_edge;

    //add edge from connected to this
    Graph_Edge* new_con_edge = new Graph_Edge(this, edge_weight, connected_vertex->node_edges);
    connected_vertex->node_edges = new_con_edge;

    return true;
}

//---remove edges---    
bool Graph_Node::remove_edge(Graph_Node* connected_vertex, bool pair_deleted){
    assert(connected_vertex);
    if(!pair_deleted){
        printf("Attempting to erase edge\n");
    }

    Graph_Edge* prev = NULL;
    Graph_Edge* curr = node_edges;

    if(curr == NULL){//the node has no edges
        printf("There are no edges for this node\n");
        return false;
    }

    //make sure the edge exists
    while(connected_vertex != curr->vertex){//if we havnt found the vertex
        prev = curr;            //need prev to point an next when we find the node to be deleted
        curr = curr->next_edge; //iterate to the next node
    }

    //delete  edge from this node
    if(!prev){//the head of the list is the node we're looking for
        node_edges = curr->next_edge;
    }
    else{
        prev->next_edge = curr->next_edge;
    }

    delete curr;
    
    //delete edge from connected node
    if(!pair_deleted){
        connected_vertex->remove_edge(this, true);
        printf("Edge erased\n");
    }
    return true;
}

//---change edge---
bool Graph_Node::change_weight_edge(Graph_Node* connected_vertex, int new_edge_weight, bool pair_edited){
    assert(connected_vertex);
    if(!pair_edited){
        printf("Attempting to edit edge\n");
    }
    
    Graph_Edge* curr = node_edges;

    if(curr == NULL){//the node has no edges
        printf("There are no edges for this node\n");
        return false;
    }

    //make sure the edge exists
    while(connected_vertex != curr->vertex){//if we havnt found the vertex
        curr = curr->next_edge; //iterate to the next node
    }

    curr->weight = new_edge_weight;
    
    //delete edge from connected node
    if(!pair_edited){
        connected_vertex->change_weight_edge(this, new_edge_weight, true);
        printf("Edge edited\n");
    }
    return true;
}

//---GENERAL---
//---constructor---
Graph_Node::Graph_Node(){
    data = '\0';
    node_edges = NULL;
    //Dijkstra
    destination = '\0';    //the destination vertex
    is_permanent = false;         //is a permentant vertex, ie cant be updated
    parent = '\0';    //the vertex to go to next in the path
    shortest_path = 99999;         //set to a high number to ensure all other paths are shorter
    was_checked = false;
}

Graph_Node::Graph_Node(char Data){
    data = Data;
    node_edges = NULL;
    //Dijkstra
    destination = '\0';    //the destination vertex
    is_permanent = false;         //is a permentant vertex, ie cant be updated
    parent = '\0';    //the vertex to go to next in the path
    shortest_path = 99999;         //set to a high number to ensure all other paths are shorter
    was_checked = false;
}

//---destrcutor---
Graph_Node::~Graph_Node(){
    //delete list of edges
    if(node_edges){
        Graph_Edge* curr = node_edges;
        Graph_Edge* next = curr->next_edge;

        while(next){
            delete curr;
            curr = next;
            next = curr->next_edge;
        }
        delete curr;
    }
}
