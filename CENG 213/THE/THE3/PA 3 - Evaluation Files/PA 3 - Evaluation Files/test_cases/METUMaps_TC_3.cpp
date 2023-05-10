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
    maps.SetStartingLocation("A7_Gate");
    maps.SetDestination("A4_Gate");
    maps.StartJourney();
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Teknokent");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("Tekno_A8");
    maps.UpdateLocation("FL");
    maps.UpdateLocation("FL_I");
    maps.UpdateLocation("Lib_I");
    std::cout << "================" << std::endl;
    maps.Display();
    std::cout << "================" << std::endl;
    maps.UpdateLocation("C_Statue");
    maps.UpdateLocation("A4_Gate");
    maps.EndJourney();
}

int main()
{
    PA3_MAPS_TEST_CASE tc;
    tc();
}