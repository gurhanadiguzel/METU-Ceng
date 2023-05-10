#include <iostream>
#include <string>
#include "highSpeedTrain.h"

void test1(){
    HighSpeedTrain *h = new HighSpeedTrain();
    std::cout << h->getFrom() << std::endl;
    std::cout << h->getTo() << std::endl;
    std::cout << h->getETA();
}

void test2(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    std::cout << h->getFrom() << std::endl;
    std::cout << h->getTo() << std::endl;
    std::cout << h->getETA();
}

void test3(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    HighSpeedTrain h2 = *h;
    std::cout << h2.getFrom() << std::endl;
    std::cout << h2.getTo() << std::endl;
    std::cout << h2.getETA();
}

void test4(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Florence", 175);
    HighSpeedTrain h2 = *h;
    std::cout << h2.getFrom() << std::endl;
    std::cout << h2.getTo() << std::endl;
    std::cout << h2.getETA();
}

void test5(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    std::cout << *h;
}

void test6(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    HighSpeedTrain *h2 = new HighSpeedTrain("Milano", "Venice", 137);
    std::cout << (*h) + (*h2);
}

void test7(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    HighSpeedTrain *h2 = new HighSpeedTrain("Florence", "Rome", 115);
    std::cout << (*h) + (*h2);
}

void test8(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    HighSpeedTrain *h2 = new HighSpeedTrain("Florence", "Rome", 115);
    std::cout << std::boolalpha << (*h < *h2);
}

void test9(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    HighSpeedTrain *h2 = new HighSpeedTrain("Turin", "Rome", 115);
    std::cout << std::boolalpha;
    std::cout << std::boolalpha << (*h > *h2);
}

void test10(){
    HighSpeedTrain *h = new HighSpeedTrain("Turin", "Milano", 60);
    HighSpeedTrain *h2 = new HighSpeedTrain("Turin", "Milano", 115);
    std::cout << std::boolalpha;
    std::cout << std::boolalpha << (*h < *h2);
}

int main(int argc, char *argv[]){
    int caseIndex = std::stoi(argv[1]);
    switch(caseIndex){
        case 1:
            test1();
            break;
        case 2:
            test2();
            break;
        case 3:
            test3();
            break;
        case 4:
            test4();
            break;
        case 5:
            test5();
            break;
        case 6:
            test6();
            break;
        case 7:
            test7();
            break;
        case 8:
            test8();
            break;
        case 9:
            test9();
            break;
        case 10:
            test10();
            break;
        default:
            break;
    }
    return 0;
}