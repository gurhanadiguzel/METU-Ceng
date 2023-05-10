#include "METUMaps.h"
#include <iostream>

class PA3_MAPS_TEST_CASE
{
    public:
        void operator()() const;
};

void PA3_MAPS_TEST_CASE::operator()() const
{
    METUMaps maps(2, "metu_campus.map");

    if(maps.currentLoc != "")
        std::cout << "\"currentLoc\" should be empty\n";
    if(maps.destination != "")
        std::cout << "\"destination\" should be empty\n";
    if(maps.startingLoc != "")
        std::cout << "\"startingLoc\" should be empty\n";
    if(maps.inJourney != false)
        std::cout << "\"inJourney\" should be false\n";
    if(maps.currentRoute.empty() != true)
        std::cout << "\"currentRoute\" should be empty\n";
    if(maps.potentialPathCount != 2)
        std::cout << "\"potentialPathCount\" did not initialized properly\n";

    if(maps.cachedPaths.tableSize != 47)
    {
        std::cout << "\"cachedPaths.tableSize\" is wrong: "
                << maps.cachedPaths.tableSize
                << " should be" << 47 << "\n";
    }

    std::cout <<"Otherwise OK";

}

int main()
{
    PA3_MAPS_TEST_CASE tc;
    tc();
}