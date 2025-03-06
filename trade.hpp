#include<bits/stdc++.h>
using namespace std;
class Trade
{
    int Bid_id, Ask_id, Quantity;
    double Price;

public:
    Trade(int bid_id, int ask_id, int quantity, double price)
        : Bid_id(bid_id), Ask_id(ask_id), Quantity(quantity), Price(price) {}

    // Friend function to overload << operator for Trade
    friend ostream &operator<<(ostream &os, const Trade &trade);
};