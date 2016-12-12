#include "Graph.hpp"
#include "Graph_Edge.hpp"

//this can go
Graph_Node* Graph::find_vertices(char vertex_data){//returns a pointer to the vertex, or NULL if it doesnt exist
    for(int i = 0; i<26; i++){
        if(Vertices[i].data == vertex_data){
            return &Vertices[i];
        }
    }
    return NULL;
}   

//add a vertex with no edge, returns false if the vertex already exists or its an unallowed char
bool Graph::add_vertex(char vertex_data){
    if(vertex_data < 91 && vertex_data > 64){           //if the data is an allowed character
        if( Vertices[vertex_data-65].data == '\0'){         //and the vertex is already empty
            Vertices[vertex_data-65].data = vertex_data;    //then add the vertex
            return true;                                    //and return true for a sucsessful add
        }
        else{                                               //if the vertex already excists
            printf("Vertex already exists. \n");            
            return false;                                   //return false for not inserted
        }
    }                                  
    else{                                               //if the data isnt an allowed character
        printf("Character not allowed. \n");                
        return false;                                       //return false for not insertered
    }  
    
}

//add edge to vertex, returns false if the edge already exists, or if the vertex doesnt exist, or if the char is now allowed
bool Graph::add_edge_vertex(char vertex_data, char connected_vertex_data, int weight){ 
    return Vertices[vertex_data-65].add_edge(&Vertices[connected_vertex_data-65], weight);//calls the add_edge method of the Graph_Node   
} 

//print the graph, listing each vertex and its edges
void Graph::print_graph(){
    for(int i = 0; i<26; i++){                          //for each value in the array
        //char vertex = Vertices[i].data;     
        if(Vertices[i].data){                           //if the current vertex data isnt null
            printf("Vertex %c : ", Vertices[i].data);       //print the current vertex
            Graph_Edge* curr = Vertices[i].node_edges;      //go to its first edge
            while(curr){                                    //and while there is an edge
                printf("(%c, %i) ", curr->vertex->data
                                            , curr->weight);//print the current edge
                curr = curr->next_edge;                     //and go to the next edge
            }
            printf("\n");
        }
    }
    printf("\n");
}

bool Graph::dfs(char start_at, char end_at){
    printf("Depth first search from '%c' to '%c': ", start_at, end_at);
    clear_search();//clear all of the flags stored in the node, for DFS "was_checked" is the only important flag
    bool found = dfs1(start_at, end_at);//call the private dfs1 method which actually performs the DFS
    if(found){
        printf(" TARGET FOUND - HALT");
    }
    printf("\n\n");
    return found;
}

bool Graph::dfs1(char start_at, char end_at){
    Vertices[start_at-65].was_checked = true;
    printf("%c ", start_at);
    bool found = false;
    Graph_Edge* curr = Vertices[start_at-65].node_edges;

    while(curr){
        if(!curr->vertex->was_checked){
            
            if(curr->vertex->data == end_at){
                found = true;
                printf("%c ", curr->vertex->data);
            }
            else{
                found = dfs1(curr->vertex->data, end_at);
            }
            
        }
        curr = curr->next_edge;
    }
    return found;
}

bool Graph::dijkstra(char start_at, char end_at){
    printf("Dijkstra from '%c' to '%c' length 0:\n", start_at, end_at);
    
    clear_search();
    Graph_Node* curr_vert = &Vertices[start_at-65];
    curr_vert->shortest_path = 0;
    curr_vert->parent = start_at;
    Graph_Node* last_vert = NULL;
    

    while(curr_vert != last_vert){
        curr_vert->is_permanent = true;
        last_vert = curr_vert;

        if(curr_vert->data == end_at){
            printf("Target Found - HALT\n\n");
            printf("Length: %i Path: ", curr_vert->shortest_path);
            while(curr_vert->data != start_at){
                printf("%c ", curr_vert->data);
                curr_vert = &Vertices[curr_vert->parent-65];
            }
            printf("%c \n\n", curr_vert->data);
            
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

        printf("%c length %i, parent %c\n", curr_vert->data, curr_vert->shortest_path, curr_vert->parent);
        
        int new_curr;
        int new_shortest = 9999999;

        for(int i = 'A'-65; i<26; i++){
            if(!Vertices[i].is_permanent && (Vertices[i].shortest_path < new_shortest)){
                new_curr = i;
                new_shortest = Vertices[i].shortest_path;
                
            }
        }
        curr_vert = &Vertices[new_curr];
        // printf("%c length %i, parent %c\n", curr_vert->data, curr_vert->shortest_path, curr_vert->parent);
    }
    printf("Target Not Found\n\n");
    return false;

}

// bool Graph::dijkstra1(char start_at, char end_at){

// }

void Graph::clear_search(){
    for(int i = 0; i<26; i++){
        Vertices[i].was_checked = Vertices[i].is_permanent = false;
        Vertices[i].destination = Vertices[i].parent = '\0';
        Vertices[i].shortest_path = 99999999;

    }
}

Graph::Graph(){
    for(int i = 0; i<26; i++){
        Vertices[i].data = '\0';
    }
}