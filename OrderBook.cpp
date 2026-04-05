#include <iostream>
#include "OrderBook.hpp"

using namespace std;

OrderBook::OrderBook()
    : buyOrders('B'), sellOrders('S') {
    this->transactions = nullptr;
    this->transactionCount = 0;
    this->transactionCapacity = 0;
}

OrderBook::~OrderBook() {
    delete[] this->transactions;
}


// Array dinâmico de transações
void OrderBook::growTransactions() {
    int newCapacity;

    if (this->transactionCapacity == 0) {
        newCapacity = 2;
    } else {
        newCapacity = this->transactionCapacity * 2;
    }

    Transaction* newArray = new Transaction[newCapacity];

    for (int i = 0; i < this->transactionCount; i++) {
        newArray[i] = this->transactions[i];
    }

    delete[] this->transactions;
    this->transactions = newArray;
    this->transactionCapacity = newCapacity;
}

void OrderBook::appendTransaction(int buyOrderId, int sellOrderId, float executionPrice) {
    if (this->transactionCount == this->transactionCapacity) {
        this->growTransactions();
    }

    this->transactions[this->transactionCount] =
        Transaction(buyOrderId, sellOrderId, executionPrice);

    this->transactionCount++;
}


bool OrderBook::submit(Order order) {
    // Ordem de compra
    if (order.getType() == 'B') {
        Order* bestSell = this->sellOrders.front();

        if (bestSell != nullptr && bestSell->getPrice() <= order.getPrice()) {
            int buyOrderId = order.getId();
            int sellOrderId = bestSell->getId();
            float executionPrice = bestSell->getPrice();

            this->sellOrders.popFront();
            this->appendTransaction(buyOrderId, sellOrderId, executionPrice);

            return true;
        }

        this->buyOrders.insertOrdered(order);
        return false;
    }

    // Ordem de venda
    if (order.getType() == 'S') {
        Order* bestBuy = this->buyOrders.front();

        if (bestBuy != nullptr && bestBuy->getPrice() >= order.getPrice()) {
            int buyOrderId = bestBuy->getId();
            int sellOrderId = order.getId();
            float executionPrice = bestBuy->getPrice();

            this->buyOrders.popFront();
            this->appendTransaction(buyOrderId, sellOrderId, executionPrice);

            return true;
        }

        this->sellOrders.insertOrdered(order);
        return false;
    }

    return false;
}

bool OrderBook::cancel(int id) {
    if (this->buyOrders.removeById(id)) {
        return true;
    }

    if (this->sellOrders.removeById(id)) {
        return true;
    }

    return false;
}

