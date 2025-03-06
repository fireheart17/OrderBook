#include<bits/stdc++.h>
using namespace std;
class Order
{
    char Side;
    int Order_id, Quantity;
    double Price;
    string Type;

    friend struct CompareBid;
    friend ostream &operator<<(ostream &os, const Order &order);

public:
    Order(string type, char side, int oid, int quantity, double price)
        : Type(type), Side(side), Order_id(oid), Quantity(quantity), Price(price) {}

    Order(string type, char side, int oid, int quantity)
        : Type(type), Side(side), Order_id(oid), Quantity(quantity), Price(-1) {}

    char getSide() const { return Side; }
    int getId() const { return Order_id; }
    int getQuantity() const { return Quantity; }
    double getPrice() const { return Price; } // will be -1 for market orders
    string getType() const { return Type; }

    void modify(int quantity, double price)
    {
        Quantity = quantity;
        Price = price;
    }

    void modify(int quantity)
    { // overloaded for market orders
        Quantity = quantity;
    }
};