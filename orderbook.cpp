#include <bits/stdc++.h>
#include <mutex>
#include<order.hpp>
#include<trade.hpp>
#include<orderbook.hpp>
using namespace std;

/*

Order: action,type,side,orderid,quantity,price (e.g., A,123,B,9,1000)
action = A (add), X (remove), M (modify) ---- what to do with modify???
type = limitorder, fillandkill ,marketorder,fillorkill
orderid = unique positive integer to identify each order;
used to reference existing orders for remove/modify
side = B (bid), A (ask)
quantity = positive integer indicating maximum quantity to buy/sell
price = double indicating max price at which to buy/min price to sell

Trade: quantity,bidoid,askoid,price (e.g., T,2,1025)
quantity = amount that traded
bidoid = orderid of the bid
askoid = orderid of ask
price = price at which the trade happened

RULES:

can't modify market orders;
if a market order can't be filled completely it will be filled partially and rest will be cancelled


REMAINING:

->add GOODTILLDAY(GTC) order
-> add semaphores

*/



// Overloading << operator to print Order objects with precision of 5
ostream &operator<<(ostream &os, const Order &order)
{
    os << fixed << setprecision(5); // set precision to 5 decimal places
    os << "ID: " << order.Order_id
       << ", Type: " << order.Type
       << ", Side: " << order.Side
       << ", Quantity: " << order.Quantity
       << ", Price: " << order.Price << endl;
    return os;
}



// Overloading << operator to print Trade objects with precision of 5
ostream &operator<<(ostream &os, const Trade &trade)
{
    os << fixed << setprecision(5); // set precision to 5 decimal places
    os << "Traded " << trade.Quantity << " units at Price: $"
       << trade.Price << " { Ask ID: " << trade.Ask_id << ", Bid ID: " << trade.Bid_id << " }" << endl;

    return os;
}

struct CompareBid
{
    bool operator()(Order *a, Order *b) const
    {
        return a->Price > b->Price;
    }
};



int main()
{
    OrderBook ob;
    int n, count = 0;
    cin >> n;
    while (n--)
    {
        string msg;
        cin >> msg;
        // cout << "Processing " << ++count << endl;
        ob.process_message(msg);
    }
    ob.print_summary();

    return 0;
}