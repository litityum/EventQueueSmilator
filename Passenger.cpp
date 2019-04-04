//
// Created by ASUS on 26.10.2018.
//

#include "Passenger.h"
#include "Event.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <queue>

using namespace std;

Passenger::Passenger(string line) {
    string token;
    stringstream stream(line);
    stream >> arrive;
    stream >> flight;
    stream >> luggage_time;
    stream >> security_time;
    stream >> VIP;
    stream >> luggage;
    //getline(stream, token, ' ');
    //arrive = stoi(token);
    //getline(stream, token, ' ');
    //flight = stoi(token);
    //getline(stream, token, ' ');
    //luggage_time = stoi(token);
    //getline(stream, token, ' ');
    //security_time = stoi(token);
    //getline(stream, token, ' ');
    //VIP = token[0];
    //getline(stream, token, ' ');
    //luggage = token[0];
}

