#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName){
    // TODO
    for(int i=0; i < vertexList.size(); i++){
        if(vertexList[i].name == vertexName){
            throw DuplicateVertexNameException();
        }
    }
    GraphVertex new_vertex;
    new_vertex.name = vertexName;
    new_vertex.edgeCount = 0;
    vertexList.push_back(new_vertex);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,const std::string& toVertexName,int weight){
    // TODO
    int index1 =-1;
    int index2 = -1;
    for(int i=0; i < vertexList.size(); i++){
        if(vertexList[i].name == fromVertexName){
            index1 = i;
        }
        if(vertexList[i].name == toVertexName){
            index2 = i;
        }
    }
    if(index1 ==-1 || index2 == -1){
        throw VertexNotFoundException();
    }
    if(vertexList[index1].edgeCount >= MAX_EDGE_PER_VERTEX || vertexList[index2].edgeCount >= MAX_EDGE_PER_VERTEX){
        throw TooManyEdgeOnVertexExecption();
    }
    if( index1 == index2){
        return false;
    } 
    for(int j=0; j< edgeList.size(); j++){
        if(edgeList[j].vertexId0 == index1 && edgeList[j].vertexId1 == index2){
            return false;
        }
        if(edgeList[j].vertexId0 == index2 && edgeList[j].vertexId1 == index1){
            return false;
        }
    }
    GraphEdge new_edge;
    new_edge.weight = weight;
    new_edge.masked = false;
    new_edge.vertexId0 = index1;
    new_edge.vertexId1 = index2;
    edgeList.push_back(new_edge);    
    vertexList[index1].edgeIds[vertexList[index1].edgeCount] = edgeList.size()-1;
    vertexList[index2].edgeIds[vertexList[index2].edgeCount] = edgeList.size()-1;
    vertexList[index1].edgeCount++;
    vertexList[index2].edgeCount++;
    return true;
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,const std::string& from,const std::string& to) const{
    // TODO
    int index1= -1;
    int index2= -1;
    for(int i=0; i<vertexList.size(); i++){
        if(vertexList[i].name==from){
            index1 = i;
        }
        if(vertexList[i].name==to){
            index2 = i;
        }
    }
    if(index1 ==-1 || index2 == -1){
        throw VertexNotFoundException();
    }
    std::priority_queue<DistanceVertexIdPair> shortest;
    std::vector<int> distance;
    std::vector<int> previous;    
    for(int j=0; j<vertexList.size(); j++){
        distance.push_back(LARGE_NUMBER);
        previous.push_back(-1);
        if(j == index1){
            DistanceVertexIdPair start = DistanceVertexIdPair(index1,0);
            shortest.push(start);
        }       
    }  
    distance[index1] = 0;    
    while(!shortest.empty()){        
        DistanceVertexIdPair vertex = shortest.top();
        shortest.pop();
        if(vertex.currentWeight <= distance[vertex.vId]){
            for(int z=0; z<vertexList[vertex.vId].edgeCount; z++){
                int edgeId = vertexList[vertex.vId].edgeIds[z];
                int toId;
                if(vertex.vId == edgeList[edgeId].vertexId0){
                    toId = edgeList[edgeId].vertexId1;
                }
                else{
                    toId = edgeList[edgeId].vertexId0;
                }
                if(edgeList[edgeId].masked == 0){
                    if(vertex.currentWeight + edgeList[edgeId].weight < distance[toId]){
                        DistanceVertexIdPair new_vertex = DistanceVertexIdPair(toId,vertex.currentWeight + edgeList[edgeId].weight);
                        shortest.push(new_vertex);
                        previous[toId]= vertex.vId;
                        distance[toId] = vertex.currentWeight + edgeList[edgeId].weight ;
                    }
                } 
            }
        }        
    }
    std::vector<int> RevList;
    while(index2 != -1){
        RevList.push_back(index2);
        index2 = previous[index2];
    }
    if(RevList.back() == index1){
         while(!RevList.empty()){
            orderedVertexIdList.push_back(RevList.back());
            RevList.pop_back();
        }
        return true;
    }
    return false;    
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,const std::string& from,const std::string& to,int numberOfShortestPaths){
    // TODO
    int index1= -1;
    int index2= -1;
    for(int i=0; i<vertexList.size(); i++){
        if(vertexList[i].name==from){
            index1 = i;
        }
        if(vertexList[i].name==to){
            index2 = i;
        }
    }
    if(index1 ==-1 || index2 == -1){
        throw VertexNotFoundException();
    }
    UnMaskAllEdges();
    int number =0;
    for(int j=0; j<numberOfShortestPaths; j++){
        std::vector<int> shortest;
        if(ShortestPath(shortest,from,to)){
            orderedVertexIdList.push_back(shortest);
            number ++;
            int temp1,temp2;
            int weight = 0;
            for(int z=0;z<shortest.size()-1;z++){
                for(int x=0;x<edgeList.size();x++){
                    if(shortest[z] == edgeList[x].vertexId0 && shortest[z+1] == edgeList[x].vertexId1 
                    || shortest[z] == edgeList[x].vertexId1 && shortest[z+1] == edgeList[x].vertexId0){
                        if(edgeList[x].weight>weight){
                            temp1 = shortest[z];
                            temp2 = shortest[z+1];
                            weight = edgeList[x].weight;
                        }
                    }
                }
            }
            std::vector<StringPair> masking;
            masking.push_back(StringPair(vertexList[temp1].name,vertexList[temp2].name));
            MaskEdges(masking);
        }
        else{break;}
    }
    UnMaskAllEdges(); 
    return number;   
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames){
    // TODO      
    for(int i=0; i<vertexNames.size(); i++){
        int index1 = -1;
        int index2 = -1;
        for(int k=0; k<vertexList.size(); k++){
            if(vertexNames[i].s0 == vertexList[k].name){
                index1 = k;
            }
            if(vertexNames[i].s1 == vertexList[k].name){
                index2 = k;
            }
        }
        if(index1 == -1 || index2 == -1){
            throw VertexNotFoundException();
        }
        for(int j=0; j<edgeList.size(); j++){
            if(edgeList[j].vertexId0 == index1 && edgeList[j].vertexId1 == index2){
                edgeList[j].masked = true;
            }
            if(edgeList[j].vertexId1 == index1 && edgeList[j].vertexId0 == index2){
                edgeList[j].masked = true;
            }
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames){
    // TODO
    for(int i=0; i<vertexNames.size(); i++){
        int index1 = -1;
        int index2 = -1;
        for(int k=0; k<vertexList.size(); k++){
            if(vertexNames[i].s0 == vertexList[k].name){
                index1 = k;
            }
            if(vertexNames[i].s1 == vertexList[k].name){
                index2 = k;
            }
        }
        if(index1 == -1 || index2 == -1){
            throw VertexNotFoundException();
        }
        for(int j=0; j<edgeList.size(); j++){
            if(edgeList[j].vertexId0 == index1 && edgeList[j].vertexId1 == index2){
                edgeList[j].masked = false;
            }
            if(edgeList[j].vertexId1 == index1 && edgeList[j].vertexId0 == index2){
                edgeList[j].masked = false;
            }
        }
    }
}

void Graph::UnMaskAllEdges(){
    // TODO
    for(int i=0; i<edgeList.size(); i++){
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name){
    // TODO
    int index1 = -1;
    for(int i=0; i< vertexList.size() ; i++){
        if(vertexList[i].name == name){
            index1 = i;
        }
    }
    if(index1 == -1){
        throw VertexNotFoundException();
    }
    for(int j=0; j<vertexList[index1].edgeCount; j++){
        edgeList[vertexList[index1].edgeIds[j]].masked = true;
    }
}

void Graph::UnMaskVertexEdges(const std::string& name){
    // TODO
    int index1 = -1;
    for(int i=0; i< vertexList.size() ; i++){
        if(vertexList[i].name == name){
            index1 = i;
        }
    }
    if(index1 == -1){
        throw VertexNotFoundException();
    }
    for(int j=0; j<vertexList[index1].edgeCount; j++){
        edgeList[vertexList[index1].edgeIds[j]].masked = false;
    }
}

void Graph::ModifyEdge(const std::string& vName0, const std::string& vName1, float newWeight){
    // TODO
    int index1 =-1;
    int index2 = -1;
    for(int i=0; i < vertexList.size(); i++){
        if(vertexList[i].name == vName0){
            index1 = i;
        }
        if(vertexList[i].name == vName1){
            index2 = i;
        }
    }
    if(index1 == -1 || index2 == -1){
        throw VertexNotFoundException();
    }
    for(int j=0; j<edgeList.size(); j++){
        if(edgeList[j].vertexId0 == index1 && edgeList[j].vertexId1 == index2){
            edgeList[j].weight = newWeight;
        }
        if(edgeList[j].vertexId1 == index1 && edgeList[j].vertexId0 == index2){
            edgeList[j].weight = newWeight;
        }
    }
}

void Graph::ModifyEdge(int vId0, int vId1, float newWeight){
    // TODO
    for (int i = 0; i<edgeList.size(); i++){
        if(edgeList[i].vertexId0 == vId0 && edgeList[i].vertexId1 == vId1){
            edgeList[i].weight = newWeight;
        }
        if(edgeList[i].vertexId1 == vId0 && edgeList[i].vertexId0 == vId1){
            edgeList[i].weight = newWeight;
        }
    }
    
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < vertexList.size(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(vertexList.size()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(vertexList.size()) &&
           nextVertexId < static_cast<int>(vertexList.size()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const{
    // TODO
    return vertexList.size();
}

int Graph::TotalEdgeCount() const{
    // TODO
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const{
    // TODO
    if(vertexId >=0 &&  vertexId < vertexList.size()){
        return vertexList[vertexId].name;
    }
    else{
        return "";
    }    
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList){
    // TODO
    int weight = 0;
    bool flag = false;
    for(int i=0; i<orderedVertexIdList.size()-1; i++){
        int index1 = orderedVertexIdList[i];
        int index2 = orderedVertexIdList[i+1];
        if(index1 <0 || index1>=vertexList.size() || index2 <0 || index2>=vertexList.size()){
            throw VertexNotFoundException();
        }
        for(int j=0; j<edgeList.size(); j++){
            if(edgeList[j].vertexId0 == index1 && edgeList[j].vertexId1 == index2 
            || edgeList[j].vertexId1 == index1 && edgeList[j].vertexId0 == index2){
                weight += edgeList[j].weight;
                flag = true;
                break;
            }            
            flag = false;
        }
        if(!flag){
            return -1;
        }        
    }
    return weight;
}