//
// Created by ASUS on 30.10.2018.
//

#include "Event.h"

Event::Event(int _time, int _type, Passenger& _passenger) {
    time = _time;
    type = _type;
    passenger = &_passenger;
}
bool Event::operator<(const Event &event) const{
    if(this->time == event.time){
        if(this->type == event.type)
            return (this->passenger->arrive < event.passenger->arrive);

        return (this->type < event.type);
    }
    return (this->time < event.time);
}
bool Event::operator>(const Event &event) const{
    if(this->time == event.time){
        if(this->type == event.type)
            return this->passenger->arrive > event.passenger->arrive;

        return this->type < event.type;
    }
    return (this->time > event.time);
}
void Event::print() const{
    cout << time << " " << type << " Arrived at " << passenger->arrive <<   endl;
}