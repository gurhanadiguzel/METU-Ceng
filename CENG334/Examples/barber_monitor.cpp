monitor BarberShop {
    condition waitingForCustomers;
    condition waitingForBarbers;
    int waiting = 0;  // number of waiting customers in chairs
    void barber() {
        if (waiting == 0)
            wait(waitingForCustomers);

        cutHair();
        waiting--;
        notify(waitingForBarbers);
    }
    void customer() {
        if (waiting < N) {
            waiting++;
            notify(waitingForCustomer);
            wait(waitingForBarbers);
            getHairCut();  // may not be executed if all chairs are
        }
    }
    void barberThread() {
        while (1)
            BarberShop.barber;
    }
    void customerThread() {
        BarberShop.customer;
    }
}