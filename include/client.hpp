#ifndef client_hpp
#define client_hpp

#include <string>
#include <cmath>
#include <list>
#include <algorithm> 
#include "./store.hpp"

class Store;

class Client {
    public:
        Client(int id, int age, std::string state, std::string paymentMethod, int x, int y);
        std::string state, paymentMethod; 
        int age, x, y, id;
        float ticket;
        bool free;
        Store * favoriteStore;

        float calculateTicket(int age, int scoreState, float scorePayMethod);
};

#endif
