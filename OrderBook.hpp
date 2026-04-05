#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Transaction.hpp"
#include "OrderLinkedList.hpp"

class OrderBook {
private:
    OrderLinkedList buyOrders;
    OrderLinkedList sellOrders;

    Transaction* transactions;
    int transactionCount;
    int transactionCapacity;

    void growTransactions();
    void appendTransaction(int buyOrderId, int sellOrderId, float executionPrice);

public:
    OrderBook();
    ~OrderBook();

    bool submit(Order order);
    bool cancel(int id);

    Order* getBuyOrders(int* n);
    Order* getSellOrders(int* n);
    Transaction* getTransactions(int* n);

    void printBuyOrders();
    void printSellOrders();
    void printTransactions();
};

#endif