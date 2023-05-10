#include "Graph.h"
#include "GraphExceptions.h"
#include <iostream>

int main()
{
    Graph g;

    g.InsertVertex("S");
    g.InsertVertex("T");
    g.InsertVertex("X");
    g.InsertVertex("Y");
    g.InsertVertex("Z");

    g.ConnectVertices("S", "T", 10);
    g.ConnectVertices("S", "Y", 4);
    g.ConnectVertices("S", "Z", 7);
    g.ConnectVertices("Y", "T", 3);
    g.ConnectVertices("Y", "X", 9);
    g.ConnectVertices("Y", "Z", 2);
    g.ConnectVertices("T", "X", 1);
    g.ConnectVertices("X", "Z", 5);

    std::vector<int> path;
    bool result = g.ShortestPath(path, "S", "Z");

    g.PrintPath(path, true);

    return 0;
}