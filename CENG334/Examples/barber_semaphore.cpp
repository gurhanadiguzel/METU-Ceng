#include <semaphore.h>

semaphore customer;
init(customer, 0);  // number of customers waiting for service
semaphore barber;
init(barber, 0);  // number of barbers waiting for customers
semaphore mutex;
init(mutex, 1);   // for mutual exclusion
int waiting = 0;  // customers who are sitting in chairs

void barberThread() {
    while (1) {
        wait(customer);  // if barber is not asleep, then there is customer waiting

        wait(mutex);
        waiting--;
        signal(mutex);

        cutHair();
        signal(barber);
    }
}
void customerThread() {
    if (waiting < N) {
        wait(mutex);
        waiting++;
        signal(customer);
        signal(mutex);

        wait(barber);
        getHairCut();
    }
}

Semaphore Customers = 0;
Semaphore Barber = 0;
Mutex Seats = 1;
int FreeSeats = N;

Barber {
    while (true) {
        /* waits for a customer (sleeps). */
        wait(Customers);

        /* mutex to protect the number of available seats.*/
        wait(Seats);

        /* a chair gets free.*/
        FreeSeats++;

        /* bring customer for haircut.*/
        signal(Barber);

        /* release the mutex on the chair.*/
        signal(Seats);
        /* barber is cutting hair.*/
    }
}

Customer {
    while (true) {
        /* protects seats so only 1 customer tries to sit
        in a chair if that's the case.*/
        if (FreeSeats > 0) {
            wait(Seats);
            /* sitting down.*/
            FreeSeats--;

            /* notify the barber. */
            signal(Customers);

            /* release the lock */
            signal(Seats);

            /* wait in the waiting room if barber is busy. */
            wait(Barber);
            getHairCut();

            // customer is having hair cut
        }
    }
}
