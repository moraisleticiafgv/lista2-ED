# Order Book

## Descrição do projeto

Este projeto implementa, em C++, um sistema simples de ordens de compra e venda para uma única ação.

O sistema permite:

- submeter ordens de compra e venda;
- executar transações quando houver compatibilidade;
- cancelar ordens em aberto;
- consultar ordens de compra, ordens de venda e transações;
- imprimir o estado atual do sistema.

---

## Compilação

Com todos os arquivos no mesmo diretório, compile com:

```bash
g++ main.cpp OrderBook.cpp OrderLinkedList.cpp Order.cpp Transaction.cpp -o order_book
```

---

## Execução

Após compilar, execute com:

```bash
./order_book
```

---

## Organização interna dos dados

O sistema usa:

- **duas listas encadeadas simples** para armazenar ordens em aberto:
  - uma para compras;
  - uma para vendas;

- **um array dinâmico** para armazenar as transações executadas.

As listas de ordens são mantidas ordenadas:

- **compras**: maior preço primeiro; em empate, menor timestamp;
- **vendas**: menor preço primeiro; em empate, menor timestamp.

Assim, a melhor ordem de cada lado fica sempre no início da lista.

As transações são armazenadas em um array dinâmico porque são apenas adicionadas ao final, sem necessidade de remoção.
