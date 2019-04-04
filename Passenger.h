//
// Created by ASUS on 26.10.2018.
//

#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>

using namespace std;
class Passenger {
public:
    int arrive;
    int luggage_time;
    int security_time;
    int flight;
    int queue_enter_time;
    char luggage;
    char VIP;

    Passenger(string line);
};


#endif //PASSENGER_H
