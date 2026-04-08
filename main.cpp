#include <iostream>
#include "OrderBook.hpp"

using namespace std;

int main() {

    OrderBook book;

    // Exemplo 1: ordem sem execução
    cout << "Exemplo 1: ordem sem execução\n";
    bool result = book.submit(Order(1, 'B', 10.0f, 1));
    cout << "submit retornou: " << (result ? "true" : "false") << "\n";
    book.printBuyOrders();
    book.printSellOrders();
    book.printTransactions();
    cout << "\n";

    // Exemplo 2: execução imediata
    cout << "Exemplo 2: execução imediata\n";
    OrderBook book2;
    book2.submit(Order(2, 'S', 9.0f, 1));
    result = book2.submit(Order(3, 'B', 10.0f, 2));
    cout << "submit retornou: " << (result ? "true" : "false") << "\n";
    book2.printBuyOrders();
    book2.printSellOrders();
    book2.printTransactions();
    cout << "\n";

    // Exemplo 3: escolha da melhor contraparte
    cout << "Exemplo 3: melhor contraparte\n";
    OrderBook book3;
    book3.submit(Order(10, 'S', 9.5f, 1));
    book3.submit(Order(11, 'S', 8.0f, 2));
    book3.submit(Order(12, 'S', 8.0f, 3));
    result = book3.submit(Order(13, 'B', 10.0f, 4));
    cout << "submit retornou: " << (result ? "true" : "false") << "\n";
    book3.printBuyOrders();
    book3.printSellOrders();
    book3.printTransactions();
    cout << "\n";

    //Exemplo 4: ordem não compatível
    cout << "Exemplo 4: ordem não compatível\n";
    OrderBook book4;
    book4.submit(Order(20, 'S', 12.0f, 1));
    result = book4.submit(Order(21, 'B', 10.0f, 2));
    cout << "submit retornou: " << (result ? "true" : "false") << "\n";
    book4.printBuyOrders();
    book4.printSellOrders();
    book4.printTransactions();
    cout << "\n";

    // Exemplo 5: cancelamento
    cout << "Exemplo 5: cancelamento\n";
    OrderBook book5;
    book5.submit(Order(30, 'B', 11.0f, 1));
    result = book5.cancel(30);
    cout << "cancel retornou: " << (result ? "true" : "false") << "\n";
    book5.printBuyOrders();
    cout << "\n";

    // Exemplo 6: métodos get
    cout << "Exemplo 6: métodos get\n";
    OrderBook book6;
    book6.submit(Order(1, 'B', 10.0f, 1));
    book6.submit(Order(2, 'B', 9.0f, 2));
    book6.submit(Order(4, 'S', 15.0f, 3)); // não executa
    book6.submit(Order(3, 'B', 7.0f, 4));  // gera transação com id 4? não — preço incompatível
    // força uma transação
    book6.submit(Order(5, 'S', 8.0f, 5));  // executa com compra de 10.0

    int n;

    Order* buys = book6.getBuyOrders(&n);
    cout << "getBuyOrders: n = " << n << "\n";
    delete[] buys;

    Order* sells = book6.getSellOrders(&n);
    cout << "getSellOrders: n = " << n << "\n";
    delete[] sells;

    Transaction* trans = book6.getTransactions(&n);
    cout << "getTransactions: n = " << n << "\n";
    delete[] trans;

    // cancel inexistente
    result = book6.cancel(999);
    cout << "cancel(999) retornou: " << (result ? "true" : "false") << "\n";

    return 0;
}