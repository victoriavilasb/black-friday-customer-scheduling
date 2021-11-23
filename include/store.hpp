#ifndef store_hpp
#define store_hpp

#include <list>
#include <algorithm>

class Client;
class Store {
    public:
        Store(int id, int capacity, int x, int y);
        int id, capacity, x, y;
        std::list< Client *> clientsScheduled;
        std::list< Client *> clientsPriority;
        int distance(int clientX, int clientY);
        void calculateClientPriorityList(std::list<Client *> clients);
        void removeClientFromScheduledList(Client * client);
        std::list<Store *> available(std::list<Store *> stores);
};

#endif
