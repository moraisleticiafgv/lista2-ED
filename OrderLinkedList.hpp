#ifndef ORDERLINKEDLIST_HPP
#define ORDERLINKEDLIST_HPP

#include "Order.hpp"

class OrderLinkedList {
private:
    struct OrderNode {
        Order data;
        OrderNode* next;

        OrderNode(Order order);
    };

    OrderNode* head;
    int size;
    char type; // 'B' para buy, 'S' para sell

    bool comesBefore(Order a, Order b);

public:
    OrderLinkedList(char type);
    ~OrderLinkedList();

    bool empty();
    int getSize();
    Order* front();

    void insertOrdered(Order order);
    bool removeById(int id);
    bool popFront();

    Order* toArray(int* n);
    void clear();
};

#endif