#include <stdio.h>
#include <stdlib.h>
#include "Graph.hpp"

int main(){
    Graph test;

    //add the vertices from A to L
    //note: this setup presumes that the node data is an upper case ascii char, 
    //and uses this to store and find nodes
    for(int i = 'A' - 65; i< 'M' - 65; i++){
        test.add_vertex(i+65);
    }

    //add all of the required edges
    //note:this could have been achieved by reading in from a file or other external source which would be much better for large graphs
    test.add_edge_vertex('A', 'B', 1);

    test.add_edge_vertex('B', 'C', 2);
    test.add_edge_vertex('B', 'D', 2);

    test.add_edge_vertex('C', 'E', 3);
    test.add_edge_vertex('C', 'F', 2);

    test.add_edge_vertex('D', 'G', 2);

    test.add_edge_vertex('F', 'H', 1);
    test.add_edge_vertex('F', 'I', 2);
    test.add_edge_vertex('F', 'J', 4);

    test.add_edge_vertex('G', 'J', 1);
    test.add_edge_vertex('G', 'K', 2);
    test.add_edge_vertex('G', 'L', 3);

    test.add_edge_vertex('I', 'K', 11);

    test.add_edge_vertex('J', 'L', 5);

    //Test Print - ensure values stored
    test.print_graph();
    
    //Depth First Search
    test.dfs('A', 'X');         //test to a value which isnt in the graph
    test.dfs('K', 'B');         //test between two known values

    //Dijkstra
    test.dijkstra('A', 'X');    //test to a value which isnt in the graph
    test.dijkstra('A', 'J');    //test between two known values

    return 0;
}