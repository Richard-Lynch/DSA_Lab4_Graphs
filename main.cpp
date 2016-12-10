#include <stdio.h>
#include <stdlib.h>
#include "Graph.hpp"

int main(){
    Graph test;

    for(int i = 'A' - 65; i< 'M' - 65; i++){
        test.add_vertex(i+65);
    }

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

    test.print_graph();
    
    test.dfs('A', 'C');
    test.dfs('A', 'E');

    test.dijkstra('A', 'X');
    test.dijkstra('A', 'F');

    test.print_graph();

    return 0;
}