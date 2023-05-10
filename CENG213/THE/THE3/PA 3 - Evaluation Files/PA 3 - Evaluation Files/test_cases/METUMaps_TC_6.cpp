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

    // Set Proper Locations
    maps.SetStartingLocation("A1_Gate");
    maps.SetDestination("Ceng");
    maps.StartJourney();
    std::cout << "======TABLE======" << std::endl;
    maps.cachedPaths.Print();
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("FL_I");
    std::cout << "================" << std::endl;
    // Turned to a wrong way (should re-calculate)
    maps.UpdateLocation("FL");
    std::cout << "======TABLE======" << std::endl;
    maps.cachedPaths.Print();
    std::cout << "================" << std::endl;
    // System tried to warn user to turn back!
    maps.Display();
    std::cout << "================" << std::endl;
    // Again wrong way (should be in cache now)
    maps.UpdateLocation("Library");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("EE");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Ceng");
    maps.EndJourney();
}

int main()
{
    PA3_MAPS_TEST_CASE tc;
    tc();
}