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
        if(Vertices[i].data){                               //if the current vertex data isnt null
            printf("Vertex %c : ", Vertices[i].data);           //print the current vertex
            Graph_Edge* curr = Vertices[i].node_edges;          //go to its first edge
            while(curr){                                        //and while there is an edge
                printf("(%c, %i) ", curr->vertex->data
                                            , curr->weight);        //print the current edge
                curr = curr->next_edge;                             //and go to the next edge
            }
            printf("\n");
        }
    }
    printf("\n");
}

//Public DFS; does some printing, clears the flags in each node and then calls the private dfs1 method - returns true if value found
bool Graph::dfs(char start_at, char end_at){
    printf("Depth first search from '%c' to '%c': ", start_at, end_at);
    clear_search();                         //clear all of the flags stored in the nodes ( "was_checked" )
    bool found = dfs1(start_at, end_at);    //call the private dfs1 method which actually performs the DFS
    if(found){                              
        printf(" TARGET FOUND - HALT");
    }
    printf("\n\n");
    return found;
}

//Private DFS; called by dfs and then recursivly calls itself - prints each inspected node - returns true if value found
bool Graph::dfs1(char start_at, char end_at){
    Vertices[start_at-65].was_checked = true;               //the current vertex is marked as checked
    printf("%c ", start_at);                                //print the char being inspected
    bool found = false;                                     //initialise found to false
    Graph_Edge* curr = Vertices[start_at-65].node_edges;    //start at the first edge of the current node

    while(curr && !found){                                  //while the current edge is not NULL and we havnt found the value
        if(!curr->vertex->was_checked){                         //if the vertex connected to by the edge hasnt already been checked
            
            if(curr->vertex->data == end_at){                       //if the connected vertex is the vertex we're looking for
                found = true;                                           //the value has been found
                printf("%c ", curr->vertex->data);                      //print the found value
            }
            else{                                                   //otherwise
                found = dfs1(curr->vertex->data, end_at);               //preform a DFS on the connected node
            }
        }
        curr = curr->next_edge;                                 //iterate to the next edge
    }
    return found;                                           //return found, which will be passed up the recusive chain
}

//Dijkstra; returns true if the value is found 
bool Graph::dijkstra(char start_at, char end_at){
    printf("Dijkstra from '%c' to '%c' length 0:\n", start_at, end_at);
    
    clear_search();                                 //clears the node flags ("is_permanent", "destination", "parent")
    Graph_Node* curr_vert = &Vertices[start_at-65]; //current node == starting node
    curr_vert->shortest_path = 0;                   //distance to starting node (self) is 0
    curr_vert->parent = start_at;                   //parent is starting node (self)
    Graph_Node* last_vert = NULL;                   //the last vertex visited
    

    while(curr_vert != last_vert){                  //while the current vertex has changed sinced the last loop
        curr_vert->is_permanent = true;                 //make the current vertex permenant
        last_vert = curr_vert;                          //make the last vertex the current vertex

        //if the path has been found
        if(curr_vert->data == end_at){                  //if the current vertex(which was just made permenant) is the vertex being searched for
            printf("Target Found - HALT\n");              //print halt
            printf("Length: %i\nPath: ", 
                            curr_vert->shortest_path);      //print the total path length and the actual path ( from end_at to start_at)
            while(curr_vert->data != start_at){             //while not at the starting node
                printf("%c ", curr_vert->data);                 //print the current node
                curr_vert = &Vertices[curr_vert->parent-65];    //go to that nodes parent
            }
            printf("%c \n\n", curr_vert->data);             //print the start_at vertex data
            
            return true;                                //return true as the path was found
        }
        
        //otherwise update all connected vertices
        Graph_Edge* curr_edge = curr_vert->node_edges;  //the current edge is the first edge attached to the current vertex

        while(curr_edge){                               //while there are more edges to check
            if(!curr_edge->vertex->is_permanent){           //if the connected vertex isnt permenant
                int shortest = curr_edge->weight +              //store a temp path length using the current vertex
                            curr_vert->shortest_path;           
                if(curr_edge->vertex->shortest_path > shortest){//if that length is shorter than the avtual shortest path
                    curr_edge->vertex->shortest_path = shortest;    //update the shortest path
                    curr_edge->vertex->parent = curr_vert->data;    //update the parent for that shortest path
                    curr_edge->vertex->destination = start_at;      //update the destination to which this shortest path leads(ie start at)
                }
            }
            curr_edge = curr_edge->next_edge;               //iterate to the next edge
        }

        printf("%c length %i, parent %c\n",             //print the current node (most recently made permenant)
            curr_vert->data, curr_vert->shortest_path, curr_vert->parent);
        
        //decide which node to check next by evaluating which tentative node currently has the shortest path
        int new_curr;                                   //a temp value for the index of the next node to be checked
        int new_shortest = 9999999;                     //a high initial value for new shortest - must ensure this new_shortest >>> any actual path length

        for(int i = 'A'-65; i<26; i++){                 //for each node in the graph(note that "empty" nodes have a very large shortest path which should ensure they are never selected)
            if( Vertices[i].data != '\0' &&                 //if the vertex being checked isnt empty 
                !Vertices[i].is_permanent &&                //and isnt permanent 
                Vertices[i].shortest_path < new_shortest){  //and has a shorter path than the current shortest path
                new_curr = i;                                   //then the vertex becomes the new current
                new_shortest = Vertices[i].shortest_path;       //and the that new_shortest path is now this vertex's shortest path
                
            }
        }
        curr_vert = &Vertices[new_curr];                //retreive the pointer for the new current vertex
    }

    //if we reach this point, the targer was never found and all nodes are permentant
    printf("Target Not Found\n\n");                 
    return false;   //return false if node isnt found

}

//private clear method - Clears all flags for DFS and dijkstra
void Graph::clear_search(){
    for(int i = 0; i<26; i++){  //for every node in the graph
        Vertices[i].was_checked = Vertices[i].is_permanent = false; //nothing has been checked && nothing is permenant
        Vertices[i].destination = Vertices[i].parent = '\0';        //there is no desitination and there is no parent
        Vertices[i].shortest_path = 99999999;                       //the shortest path is very long(should be much bigger than any actual path)

    }
}

//constructor
Graph::Graph(){
    for(int i = 0; i<26; i++){  //for every value in the graph
        Vertices[i].data = '\0';    //ensure the data is null
    }
}