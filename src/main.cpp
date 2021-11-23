#include <iostream>
#include <list>
#include <map>
#include "../include/store.hpp"
#include "../include/client.hpp"

using namespace std;

bool
allClientsScheduled(list<Client *> clients) {
    list<Client *> ::iterator it = clients.begin();

    while(it != clients.end()) {
        if ((*it)->free) {
            return false;
        }

        it++;
    }

    return true;
}



void
scheduleClient(
    Client * client,
    Store * store
) {
    // insert client in scheduled list
    store->clientsScheduled.push_back(client);
    // lower capacity
    store->capacity--;
    // insert store into client
    client->favoriteStore = store;
    // set client to not free
    client->free = false;
}

void
changeClient(
    Client * client,
    Store * store
) {
    client->favoriteStore->clientsScheduled.remove(client);
    client->favoriteStore->capacity++;

    scheduleClient(client, store);
}

list<Store *>
availableStores(list<Store *> stores) {
    list <Store *> ::iterator it = stores.begin();
    list <Store *> availableStores;

    while(it != stores.end()) {
        if ((*it)->capacity > 0) {
            availableStores.push_back((*it));
        }

        it++;
    }

    return availableStores;
}

void 
stableMatching(
    std::list<Store *> stores,
    std::list<Client *> clients
) {
    list<Store *> s;
    list<Client *> c;
    int invitedClients, newDistance, currentDistance, x, y, count;
    list< Client *> clientsPriority;
    list< Client *> ::iterator clientsPriorityIt;
    list< Store *> ::iterator storePriorityIt;
    list<Store *> ::iterator storesIt;
    Store * store;
    Client * client;

    while (true) {
        s = availableStores(stores);
        if (s.size() == 0 || allClientsScheduled(clients)) {
            break;
        }

        for(storesIt = stores.begin(); storesIt != stores.end(); storesIt++) {
            invitedClients = 0;
            clientsPriorityIt = (*storesIt)->clientsPriority.begin();

            // if the store still has capacity and not all clients were invited
            while((*storesIt)->capacity > 0 && invitedClients != (*storesIt)->clientsPriority.size()) {
                if((*clientsPriorityIt)->free) {
                    scheduleClient((*clientsPriorityIt), (*storesIt));
                } else {
                    x = (*clientsPriorityIt)->x;
                    y = (*clientsPriorityIt)->y;

                    newDistance = (*storesIt)->distance(x, y);
                    currentDistance = (*clientsPriorityIt)->favoriteStore->distance(x, y);

                    if ((*storesIt)->capacity > 0) {
                        if (newDistance < currentDistance) {
                            changeClient((*clientsPriorityIt), (*storesIt));
                        } else if (newDistance == currentDistance) {
                            if ((*storesIt)->id < (*clientsPriorityIt)->favoriteStore->id) {
                                changeClient((*clientsPriorityIt), (*storesIt));
                            }
                        }
                    }
                }

                invitedClients++;
                clientsPriorityIt++;  
            }
        }
    }
}

int
main() {
    map<string, float> paymentMethodScoreTable;
    map<string, int> stateScoreTable;
    int id, m, n, storesNumber, storeCapacity, storeLocX, storeLocY, clientsNumber, age, clientLocX, clientLocY;
    string state, paymentMethod;
    list <Store *> stores;
    list <Client *> clients;
    list <Store *> ::iterator storesIt;
    list <Client *> ::iterator clientsIt;

      // ===> Fill paymentMethodScoreTable
    paymentMethodScoreTable["DINHEIRO"] = 1.0;
    paymentMethodScoreTable["DEBITO"] = 2.0;
    paymentMethodScoreTable["CREDITO"] = 3.0;

    // ===> Fill stateScoreTable
    stateScoreTable["MG"] = 0;
    stateScoreTable["PR"] = 10;
    stateScoreTable["SP"] = 20;
    stateScoreTable["SC"] = 30;
    stateScoreTable["RJ"] = 40;
    stateScoreTable["RN"] = 50;
    stateScoreTable["RS"] = 60;

    // ===> Read GridSize
    cin >> m >> n;

    // ===> Read stores
    cin >> storesNumber;
    id = 0;
    while (storesNumber > 0) {
        cin >> storeCapacity >> storeLocX >> storeLocY;
        stores.push_back(new Store(id, storeCapacity, storeLocX, storeLocY));

        storesNumber --;
        id ++;
    }

    // ===> Read clients
    cin >> clientsNumber;
    id = 0;
    while (clientsNumber > 0) {
        cin >> age >> state >> paymentMethod >> clientLocX >> clientLocY;
        Client * client = new Client(id, age, state, paymentMethod, clientLocX, clientLocY);

        client->ticket = client->calculateTicket(age, stateScoreTable[state], paymentMethodScoreTable[paymentMethod]);

        clients.push_back(client);

        clientsNumber --;
        id ++;
    }

    storesIt = stores.begin();
    while(storesIt != stores.end()) {
        (*storesIt)->calculateClientPriorityList(clients);
        storesIt++;
    }

    stableMatching(stores, clients);

    for(storesIt = stores.begin(); storesIt != stores.end(); storesIt++) {
        cout << (*storesIt)->id << endl;
        for(clientsIt = (*storesIt)->clientsScheduled.begin(); clientsIt != (*storesIt)->clientsScheduled.end(); clientsIt++) {
            cout << (*clientsIt)->id << " ";
        }
        cout << endl;
    }
}

