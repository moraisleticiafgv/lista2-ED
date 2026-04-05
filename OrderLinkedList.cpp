#include <iostream>
#include "OrderLinkedList.hpp"

using namespace std;

OrderLinkedList::OrderNode::OrderNode(Order order)
    : data(order) {
    this->next = nullptr;
}


OrderLinkedList::OrderLinkedList(char type) {
    this->head = nullptr;
    this->size = 0;
    this->type = type;
}

OrderLinkedList::~OrderLinkedList() {
    this->clear();
}


// Função de comparação
bool OrderLinkedList::comesBefore(Order a, Order b) {
    if (this->type == 'B') {
        if (a.getPrice() > b.getPrice()) {
            return true;
        }

        if (a.getPrice() < b.getPrice()) {
            return false;
        }

        return a.getTimestamp() < b.getTimestamp();
    }

    if (a.getPrice() < b.getPrice()) {
        return true;
    }

    if (a.getPrice() > b.getPrice()) {
        return false;
    }

    return a.getTimestamp() < b.getTimestamp();
}


// Operações básicas
bool OrderLinkedList::empty() {
    return this->head == nullptr;
}

int OrderLinkedList::getSize() {
    return this->size;
}

Order* OrderLinkedList::front() {
    if (this->head == nullptr) {
        return nullptr;
    }

    return &(this->head->data);
}

// Inserção ordenada
void OrderLinkedList::insertOrdered(Order order) {
    OrderNode* newNode = new OrderNode(order);

    if (this->head == nullptr || this->comesBefore(order, this->head->data)) {
        newNode->next = this->head;
        this->head = newNode;
        this->size++;
        return;
    }

    OrderNode* prev = this->head;
    OrderNode* current = this->head->next;

    while (current != nullptr && !this->comesBefore(order, current->data)) {
        prev = current;
        current = current->next;
    }

    prev->next = newNode;
    newNode->next = current;
    this->size++;
}


// Remoção por id
bool OrderLinkedList::removeById(int id) {
    if (this->head == nullptr) {
        return false;
    }

    if (this->head->data.getId() == id) {
        OrderNode* temp = this->head;
        this->head = this->head->next;
        delete temp;
        this->size--;
        return true;
    }

    OrderNode* prev = this->head;
    OrderNode* current = this->head->next;

    while (current != nullptr) {
        if (current->data.getId() == id) {
            prev->next = current->next;
            delete current;
            this->size--;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}


// Remove head
bool OrderLinkedList::popFront() {
    if (this->head == nullptr) {
        return false;
    }

    OrderNode* temp = this->head;
    this->head = this->head->next;
    delete temp;
    this->size--;

    return true;
}

// Copia para array dinâmico
Order* OrderLinkedList::toArray(int* n) {
    *n = this->size;

    if (this->size == 0) {
        return nullptr;
    }

    Order* array = new Order[this->size];
    OrderNode* current = this->head;
    int i = 0;

    while (current != nullptr) {
        array[i] = current->data;
        i++;
        current = current->next;
    }

    return array;
}

// Limpeza
void OrderLinkedList::clear() {
    OrderNode* current = this->head;

    while (current != nullptr) {
        OrderNode* next = current->next;
        delete current;
        current = next;
    }

    this->head = nullptr;
    this->size = 0;
}