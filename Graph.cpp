#include "Graph.hpp"
#include "Graph_Edge.hpp"

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

void Graph::print_graph(){
    for(int i = 0; i<26; i++){
        char vertex = Vertices[i].data;
        if(vertex){
            printf("Vertex %c : ", vertex);
            Graph_Edge* curr = Vertices[i].node_edges;
            while(curr){
                printf("(%c, %i) ", curr->vertex->data, curr->weight);
                curr = curr->next_edge;
            }
            printf("\n");
        }
    }
}

bool Graph::dfs(char start_at, char end_at){
    printf("Depth first search from %c: ", start_at);
    clear_search();
    bool found = dfs1(start_at, end_at);
    if(found){
        printf(" TARGET FOUND - HALT");
    }
    printf("\n");

    return found;
}

bool Graph::dfs1(char start_at, char end_at){
    Vertices[start_at-65].was_checked = true;
    bool found = false;
    Graph_Edge* curr = Vertices[start_at-65].node_edges;

    while(curr){
        if(!curr->vertex->was_checked){
            if(curr->vertex->data == end_at){
                found = true;
            }
            else{
                printf("%c ", curr->vertex->data);
                found = dfs1(curr->vertex->data, end_at);
            }
            
        }
        curr = curr->next_edge;
    }
    return found;
}

bool Graph::dijkstra(char start_at, char end_at){
    printf("Dijkstra from %c to %c:\n", start_at, end_at);
    
    clear_search();
    Graph_Node* curr_vert = &Vertices[start_at-65];
    curr_vert->shortest_path = 0;
    Graph_Node* last_vert = NULL;
    

    while(curr_vert != last_vert){
        curr_vert->is_permanent = true;
        last_vert = curr_vert;

        if(curr_vert->data == end_at){
            printf("target found - HALT\n");
            return true;
        }
        
        Graph_Edge* curr_edge = curr_vert->node_edges;
        
        while(curr_edge){
            if(!curr_edge->vertex->is_permanent){
                int shortest = curr_edge->weight + curr_vert->shortest_path;
                if(curr_edge->vertex->shortest_path > shortest){
                    curr_edge->vertex->shortest_path = shortest;
                    curr_edge->vertex->parent = curr_vert->data;
                    curr_edge->vertex->destination = start_at;
                }
            }
            curr_edge = curr_edge->next_edge;
        }

        
        int new_curr;
        int new_shortest = 9999999;

        for(int i = 'A'-65; i<26; i++){
            if(!Vertices[i].is_permanent && (Vertices[i].shortest_path < new_shortest)){
                new_curr = i;
                new_shortest = Vertices[i].shortest_path;
                
            }
        }
        curr_vert = &Vertices[new_curr];
        printf("%c length %i, parent %c\n", curr_vert->data, curr_vert->shortest_path, curr_vert->parent);
    }
    printf("target not found\n");
    return false;

}

// bool Graph::dijkstra1(char start_at, char end_at){

// }

void Graph::clear_search(){
    for(int i = 0; i<26; i++){
        Vertices[i].was_checked = Vertices[i].is_permanent = false;
        Vertices[i].destination = Vertices[i].parent = NULL;
        Vertices[i].shortest_path = 99999999;

    }
}

Graph::Graph(){
    for(int i = 0; i<26; i++){
        Vertices[i].data = '\0';
    }
}