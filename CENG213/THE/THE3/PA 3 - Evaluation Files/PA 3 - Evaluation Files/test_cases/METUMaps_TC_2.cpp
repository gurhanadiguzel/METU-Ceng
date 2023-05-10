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

    // This should fail
    maps.StartJourney();
    // This also fail (we should not be in a journey)
    maps.EndJourney();
    // This also fail
    maps.Display();
    // This should also fail
    maps.UpdateLocation("Bad Location");
}

int main()
{
    PA3_MAPS_TEST_CASE tc;
    tc();
}