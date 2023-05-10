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

    if(g.ConnectVertices("D", "D", 123) == true)
    {
        std::cout << "Connected vertices" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Unable to connect vertices" << std::endl;
    }
    return 0;
}