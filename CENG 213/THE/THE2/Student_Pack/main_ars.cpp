#include <iostream>

#include "AirlineReservationSystem.h"

int main() {
    AirlineReservationSystem ars;

    ars.print();

    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");
    ars.addPassenger("berat", "kara");
    ars.addFlight("1", "10:00", "20:00", "ANKARA", "LONDON", 50, 50);
    ars.addFlight("2", "10:00", "20:00", "ADANA", "LONDON", 0, 50);
    ars.addFlight("3", "10:00", "20:00", "NİĞDE", "LONDON", 50, 0);
    ars.addFlight("4", "10", "20", "NİĞDE", "LONDON", 0, 10);   
    ars.issueTicket("berat", "kara","4",business);

    ars.print();
    std::cout<<ars.searchPassenger("leo", "ivy")->getFirstname()<<std::endl;;

    return 0;
}
