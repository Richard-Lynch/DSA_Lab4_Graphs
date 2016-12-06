#include "Graph_Node.hpp"

//---MANAGING EDGES---
//---add edges---
bool Graph_Node::add_edge(Graph_Node* connected_vertex, int edge_weight){
    assert(connected_vertex);
    //add edge from this to connected
    Graph_Edge temp = {.vertex = connected_vertex, 
                            .weight = edge_weight};  //create a new edge for this vertex
    edge_list.push_back(temp);                  //copy in to vector
    
    //add edge from connected to this
    Graph_Edge con_temp = {.vertex = this, 
                            .weight = edge_weight};  //create a new edge
    connected_vertex->edge_list.push_back(con_temp);    //copy in to the vector 

    return true;
}

//---remove edges---    
bool Graph_Node::remove_edge(Graph_Node* connected_vertex){
    assert(connected_vertex);
    printf("Attempting to erase edge\n");
    edge_vector::iterator i = edge_list.begin();
    while((edge_list[i].vertex != connected_vertex)&&(edge_list.size() > i)){
        i++;
    }
    if(edge_list.size() <= i){
        printf("Edge does not exist from this to connected\n");
        return false;
    }
    edge_list.erase(i);
    printf("Edge from this to connected erased\n");

    //similarly for the connected vertex
    con_edge_list = connected_vertex->edge_list;
    int j = 0;
    while((con_edge_list[i].vertex != this)&&(edge_list.size() > j)){
        j++;
    }
    if(con_edge_list.size() =< j){
        printf("Edge does not exist from connected to this\n");
        return false;
    }
    con_edge_list.erase(i);
    printf("Edge from connected to this erased\n");
    
}

//---change edge---
bool Graph_Node::change_weight_edge(Graph_Node* connected_vertex, int new_edge_weight){
    assert(connected_vertex);
    printf("Attempting to edit edge\n");
    int i = 0;
    while((edge_list.at(edge_list.begin()+i))->vertex != connected_vertex){
        i++;
    }
    if(edge_list.size() =< i){
        printf("Edge does not exist from this to connected\n");
        return false;
    }
    (edge_list.at(edge_list.begin()+i))->weight = new_edge_weight;
    printf("Edge from this to connected edited\n");

    //similarly for the connected vertex
    con_edge_list = connected_vertex->edge_list;
    int j = 0;
    while((con_edge_list.at(con_edge_list.begin()+j))->vertex != this){
        j++;
    }
    if(con_edge_list.size() =< j){
        printf("Edge does not exist from connected to this\n");
        return false;
    }
    (con_edge_list.at(con_edge_list.begin()+i))->weight = new_edge_weight;
    printf("Edge from connected to this edited\n");
    
    }

//---GENERAL---
//---constructor---
Graph_Node::Graph_Node(){
    char data = NULL;
    //Dijkstra
    destination = NULL;    //the destination vertex
    is_permanent = false;         //is a permentant vertex, ie cant be updated
    parent = NULL;    //the vertex to go to next in the path
    shortest_path = 99999;         //set to a high number to ensure all other paths are shorter
    was_check = false;
}

//---destrcutor---
Graph_Node::~Graph_Node(){

}
