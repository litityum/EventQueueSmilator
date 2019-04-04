//
// Created by ASUS on 30.10.2018.
//

#ifndef EVENT_H
#define EVENT_H

#include "Passenger.h"

class Event {
public:
    int time;
    int type; //Arrive, Luggage, Security
    Passenger* passenger;
    Event(int _time, int _type, Passenger& _passenger);
    bool operator<(const Event& event) const;
    bool operator>(const Event& event) const;
    void print() const;

};


#endif //EVENT_H
