#include "../include/store.hpp"
#include "../include/client.hpp"
#include <iostream>
#include <cmath>
#include <string>

Client::Client(int id, int age, std::string state, std::string paymentMethod, int x, int y) {
    this->id = id;
    this->age = age;
    this->state = state;
    this->x = x;
    this->y = y;
    this->free = true;
}

float
Client::calculateTicket(int age, int scoreState, float scorePayMethod) {    
    return float(abs(60-age) + scoreState) / scorePayMethod;
}
