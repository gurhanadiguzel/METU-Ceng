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


    std::vector<std::vector<int> > paths;
    int pathCount = g.MultipleShortPaths(paths, "S", "Z", 2);
    if(pathCount != static_cast<int>(paths.size()))
    {
        std::cout << "Returned path count is not same with the vector size!" << std::endl;
        std::cout << "Returned: " << pathCount << " Vector Size: " << paths.size() << std::endl;
    }

    for(size_t i = 0; i < paths.size(); i++)
    {
        g.PrintPath(paths[i], true);
        int totalWeight = g.TotalWeightInBetween(paths[i]);
        std::cout << "Length: " << totalWeight << "\n";
    }
    return 0;
}