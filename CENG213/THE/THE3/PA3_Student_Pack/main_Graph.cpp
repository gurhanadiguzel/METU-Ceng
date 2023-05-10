#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    Graph g;
    std::vector<int> a = std::vector<int>();
    std::vector<std::vector<int> > b = std::vector<std::vector<int> >();
    g.InsertVertex("S");
    g.InsertVertex("T");
    g.InsertVertex("X");
    g.InsertVertex("Y");
    g.InsertVertex("Z");

    g.ConnectVertices("S", "T", 10);
    g.ConnectVertices("S", "Y", 4);
    g.ConnectVertices("S", "Z", 7);
    g.ConnectVertices("T", "Y", 3);
    g.ConnectVertices("T", "X", 1);
    g.ConnectVertices("Y", "S", 4);
    g.ConnectVertices("Y", "Z", 2);
    g.ConnectVertices("X", "Y", 9);
    g.ConnectVertices("X", "Z", 5);
    g.ShortestPath(a,"S","Z");
    std::cout<<g.TotalWeightInBetween(a)<<std::endl;
    std::cout<< "A"<<g.MultipleShortPaths(b,"S","Z",3)<<std::endl;
    //g.ConnectVertices("A", "I", 8);
    // try
    // {
    //     g.ConnectVertices("A", "J", 9);
    // }
    // catch(const TooManyEdgeOnVertexExecption& e)
    // {
    //     std::cout << e.what() << '\n';
    // }
    
    g.PrintAll();
    return 0;
}