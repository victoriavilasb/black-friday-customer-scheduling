#include "../include/store.hpp"
#include "../include/client.hpp"
#include <iostream>
#include <cmath>
#include <list>

Store::Store(int id, int capacity, int x, int y) {
    this->id = id;
    this->capacity = capacity;
    this->x = x;
    this->y = y;
}

int
Store::distance(int clientX, int clientY) {
    int dx = abs(this->x - clientX);
    int dy = abs(this->y - clientY);

    if (dx > dy) {
        return dx;
    } else {
        return dy;
    }
}

bool
clientComp(Client * a, Client * b)
{
    if (a->id == b->id) {
        return a->id < b->id;
    }

    return a->ticket>b->ticket;
}

void
Store::calculateClientPriorityList(std::list<Client *> clients) {
    std::list <Client *> ::iterator it = clients.begin();
    
    while(it != clients.end()) {
        this->clientsPriority.push_back((*it));
        it ++;
    }

    // ===> Sort by ticket: greater first and if the tickets are the same order by lower id
    clientsPriority.sort(clientComp);
}
