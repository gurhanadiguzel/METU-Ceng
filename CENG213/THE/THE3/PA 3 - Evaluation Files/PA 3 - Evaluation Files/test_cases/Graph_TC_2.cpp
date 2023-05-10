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

    try{
        g.InsertVertex("A");
    }
    catch(const DuplicateVertexNameException& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}