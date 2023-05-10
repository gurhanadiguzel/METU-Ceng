#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    passengers.insert(Passenger(firstname,lastname));
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    /* TODO */
    return &passengers.search(Passenger(firstname,lastname))->data;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    /* TODO */
    flights.insert(Flight(flightCode,departureTime,arrivalTime,departureCity,arrivalCity,economyCapacity,businessCapacity));
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    /* TODO */
    std::vector<Flight*> v_flights;
    searchFlight(v_flights,flights.getRoot(),departureCity, arrivalCity);    
    return v_flights; 
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    issueTicket(flights.getRoot(), firstname, lastname, flightCode, ticketType);
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    /* TODO */
    saveFreeTicketRequest(flights.getRoot(),firstname,lastname,flightCode,ticketType);
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    /* TODO */
    executeTheFlight(flights.getRoot(),flightCode);
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}

void AirlineReservationSystem::searchFlight(std::vector<Flight*> &v_flights, BSTNode<Flight> *node,const std::string &departureCity, const std::string &arrivalCity){
    if(node != NULL){
        if(node->data.getArrivalCity() == arrivalCity && node->data.getDepartureCity() == departureCity){
            v_flights.push_back(&node->data);
        }
        searchFlight(v_flights,node->left,departureCity, arrivalCity);
        searchFlight(v_flights,node->right,departureCity, arrivalCity);
    }
}

void AirlineReservationSystem::issueTicket(BSTNode<Flight> *node,const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType){
    if(node != NULL){
        if(node->data.getFlightCode()== flightCode){
            BSTNode<Passenger> *new_passenger = passengers.search(Passenger(firstname,lastname));
            if(new_passenger != NULL){
                Ticket new_ticket = Ticket(&new_passenger->data,&node->data,ticketType);
                node->data.addTicket(new_ticket);
            }
        }
        issueTicket(node->left,firstname,lastname,flightCode,ticketType);
        issueTicket(node->right,firstname,lastname,flightCode,ticketType);
    }    
}

void AirlineReservationSystem::saveFreeTicketRequest(BSTNode<Flight> *node,const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType){
    if(node != NULL){
        if(freeTicketRequests.isFull()){
            throw QueueException("Error: Queue is full");
        }
        if(node->data.getFlightCode() == flightCode){
            BSTNode<Passenger> *new_passenger = passengers.search(Passenger(firstname,lastname));
            if(new_passenger != NULL){
                Ticket free_ticket = Ticket(&new_passenger->data,&node->data,ticketType);
                freeTicketRequests.enqueue(free_ticket);
            }
        }
        saveFreeTicketRequest(node->left, firstname, lastname, flightCode, ticketType);
        saveFreeTicketRequest(node->right, firstname, lastname, flightCode, ticketType);
    }
}

void AirlineReservationSystem::executeTheFlight(BSTNode<Flight> *node,const std::string &flightCode){
    if(node != NULL){
        if(node->data.getFlightCode() == flightCode){
            for(int i= 0; i< freeTicketRequests.size(); i++){
                Ticket temp= freeTicketRequests.dequeue();
                if(temp.getFlight()->getFlightCode() == flightCode){
                    if(!node->data.addTicket(temp)){
                        freeTicketRequests.enqueue(temp);
                    }                   
                }
                else{
                    freeTicketRequests.enqueue(temp);
                }                
            }
            node->data.setCompleted(true);
        }
       executeTheFlight(node->left, flightCode);
       executeTheFlight(node->right, flightCode);
    }
}
