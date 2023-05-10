#include "METUMaps.h"
#include "GraphExceptions.h"

#include <iostream>

void METUMaps::PrintNotInJourney() const
{
    std::cout << "Device is not in a journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeDestination() const
{
    std::cout << "Cannot change Destination during journey!" << std::endl;
}

void METUMaps::PrintUnableToChangeStartingLoc() const
{
    std::cout << "Cannot change Starting Location during journey!" << std::endl;
}

void METUMaps::PrintAlreadyInJourney() const
{
    std::cout << "Device is already in a journey!" << std::endl;
}

void METUMaps::PrintJourneyIsAlreadFinished() const
{
    std::cout << "Journey is already finished!" << std::endl;
}

void METUMaps::PrintLocationNotFound() const
{
    std::cout << "One (or both) of the locations are not found in the maps!" << std::endl;
}

void METUMaps::PrintJourneyCompleted() const
{
    std::cout << "Journey Completed!" << std::endl;
}

void METUMaps::PrintCachedLocationFound(const std::string& location0,
                                        const std::string& location1) const
{
    std::cout << "Route between \""
              << location0 << "\" and \""
              << location1 << "\" is in cache, using that..."
              << std::endl;
}

void METUMaps::PrintCalculatingRoutes(const std::string& location0,
                                      const std::string& location1) const
{
    std::cout << "Calculating Route(s) between \""
              << location0 << "\" and \""
              << location1 << "\"..."
              << std::endl;
}

std::string METUMaps::GenerateKey(const std::string& location0,const std::string& location1){
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    return location0 + "/" + location1;
}

METUMaps::METUMaps(int potentialPathCount,const std::string& mapFilePath){
    // TODO
    this->map = Graph(mapFilePath);
    this->cachedPaths = KeyedHashTable(potentialPathCount*map.TotalVertexCount());
    this->potentialPathCount = potentialPathCount;
    this->inJourney = false;
}

void METUMaps::SetDestination(const std::string& name){
    // TODO
    if(inJourney){
        PrintUnableToChangeDestination();
    }
    else{
        destination = name; 
    }    
}

void METUMaps::SetStartingLocation(const std::string& name){
    // TODO
    if(inJourney){
        PrintUnableToChangeStartingLoc();
    }
    else{
        startingLoc = name;
    }    
}

void METUMaps::StartJourney(){
    // TODO
    PrintCalculatingRoutes(startingLoc,destination);
    if(inJourney){
        PrintAlreadyInJourney();
        return;
    }
    int index1 = -1;
    int index2 = -1;
    for(int i=0; i<map.TotalVertexCount(); i++){
        if( startingLoc  == map.VertexName(i)){
            index1 = i;
        }
        if(destination == map.VertexName(i)){
            index2 = i;
        }
    }
    if(index1 == -1 || index2 == -1){
        PrintLocationNotFound();
        return;
    }
    else{
        std::vector< std::vector<int> > shortest;
        if(map.MultipleShortPaths(shortest,startingLoc,destination,potentialPathCount)){
            currentRoute = shortest.front();
            for(int j=0; j<shortest.size(); j++){
                int size = shortest[j].size();
                for(int z=0; z<size-1;z++){
                    std::string Gkey = GenerateKey(map.VertexName(shortest[j].front()),map.VertexName(shortest[j].back()));
                    cachedPaths.Insert(Gkey, shortest[j]);
                    shortest[j].erase(shortest[j].begin());
                }
            }
        }
        currentLoc = startingLoc;
        inJourney = true;
    }        
}

void METUMaps::EndJourney(){
    // TODO
    if(!inJourney){
        PrintJourneyIsAlreadFinished();
        return;
    }
    else{
        cachedPaths.ClearTable();
        startingLoc.clear();
        destination.clear();
        currentLoc.clear();
    }
}

void METUMaps::UpdateLocation(const std::string& name){
    // TODO
    if(!inJourney){
        PrintNotInJourney();
        return;
    }
    int index = -1;
    for(int i=0; i<map.TotalVertexCount(); i++){
        if( name  == map.VertexName(i)){
            index = i;
        }
    }
    if(index == -1){
        PrintLocationNotFound();
        return;
    }
    if(name == destination){
        PrintJourneyCompleted();
    }
    else{
        std::string Gkey = GenerateKey(name,destination);
        std::vector<int> way;
        if(cachedPaths.Find(way, Gkey)){
            PrintCachedLocationFound(name,destination);
            currentRoute = way;
        }
        else{
            PrintCalculatingRoutes(name,destination);
            std::vector<int> shortest;
            if(map.ShortestPath(shortest,name,destination)){
                currentRoute = shortest;
                int size = shortest.size();
                for(int z=0; z<size -1;z++){
                    std::string Gkey = GenerateKey(map.VertexName(shortest.front()),map.VertexName(shortest.back()));
                    cachedPaths.Insert(Gkey, shortest);
                    shortest.erase(shortest.begin());
                }
            }
        }
        currentLoc = name;
    }

}

void METUMaps::Display()
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    if(!inJourney)
    {
        // We are not in journey, this function
        // shouldn't be called
        PrintNotInJourney();
        return;
    }

    int timeLeft = map.TotalWeightInBetween(currentRoute);

    // Print last known location
    std::cout << "Journey         : " << startingLoc << "->"
              << destination << "\n";
    std::cout << "Current Location: " << currentLoc << "\n";
    std::cout << "Time Left       : " << timeLeft << " minutes\n";
    std::cout << "Current Route   : ";
    map.PrintPath(currentRoute, true);

    std::cout.flush();
}