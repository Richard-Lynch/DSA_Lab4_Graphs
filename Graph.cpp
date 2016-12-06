#include "Graph.hpp"

Graph_Node* Graph::find_vertices(char vertex_data){//returns a pointer to the vertex, or NULL if it doesnt exist
    for(int i = 0; i<26; i++){
        if(Vertices[i].data == vertex_data){
            return &Vertices[i];
        }
    }
    return NULL;

}   
bool Graph::add_vertex(char vertex_data){    //add a vertex with no edge, returns false if the vertex already exists or its an unallowed char
    Vertices[vertex_data-65].data = vertex_data;
    return true;
}

bool Graph::add_edge_vertex(char vertex_data, char connected_vertex_data, int weight){ //add edge to vertex, returns false if the edge already exists, or if the vertex doesnt exist, or if the char is now allowed
    return Vertices[vertex_data-65].add_edge(&Vertices[connected_vertex_data-65], weight);   
} 