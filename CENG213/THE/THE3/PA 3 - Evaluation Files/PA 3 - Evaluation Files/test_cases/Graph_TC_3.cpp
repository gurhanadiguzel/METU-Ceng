#include "Graph.h"
#include <iostream>

int main()
{
    Graph g;

    g.InsertVertex("A");
    g.InsertVertex("B");
    g.InsertVertex("C");
    g.InsertVertex("D");
    g.InsertVertex("E");

    g.ConnectVertices("E", "D", 33);

    g.PrintAll();
    return 0;
}