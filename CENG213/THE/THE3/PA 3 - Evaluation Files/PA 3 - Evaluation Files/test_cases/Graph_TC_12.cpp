#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    Graph g;

    g.InsertVertex("A");
    g.InsertVertex("B");
    g.InsertVertex("C");
    g.InsertVertex("D");
    g.InsertVertex("E");

    g.ConnectVertices("A", "B", 2);
    g.ConnectVertices("A", "C", 3);
    g.ConnectVertices("D", "E", 32);
    g.ConnectVertices("C", "E", 22);
    g.ConnectVertices("E", "B", 12);

    g.PrintAll();
    std::cout << "===============" << std::endl;

    g.MaskVertexEdges("E");

    g.PrintAll();
    return 0;
}