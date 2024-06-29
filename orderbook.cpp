#include<bits/stdc++.h>
using namespace std;

/*

Order: action,orderid,side,quantity,price,type (e.g., A,123,B,9,1000)
action = A (add), X (remove), M (modify) ---- what to do with modify???
orderid = unique positive integer to identify each order;
used to reference existing orders for remove/modify
side = B (bid), A (ask)
quantity = positive integer indicating maximum quantity to buy/sell
price = double indicating max price at which to buy/min price to sell
type = Normal and FillAndKill

Trade: quantity,bidoid,askoid,price (e.g., T,2,1025)
quantity = amount that traded
bidoid = orderid of the bid
askoid = orderid of ask
price = price at which the trade happened

*/

class Order {
    char Side;
    int Order_id, Quantity;
    double Price;
    string Type;

    friend struct CompareBid;

public:
    Order(char side, int oid, int quantity, double price, string type) :
        Side(side), Order_id(oid), Quantity(quantity), Price(price), Type(type) {}

    char getSide() { return Side; }
    int getId() { return Order_id; }
    int getQuantity() { return Quantity; }
    double getPrice() { return Price; }
    string getType() { return Type; }

    void modify(int quantity, double price) {
        Quantity = quantity;
        Price = price;
    }
};

struct CompareBid {
    bool operator()(Order* a, Order* b) const {
        return a->Price > b->Price;
    }
};

class OrderBook {
    unordered_map<int, Order*> orders;
    set<Order*, CompareBid> bids;
    set<Order*> asks;
    vector<string> types;
    int nextorderid;
    int messages;
    int corrupted_messages = 0;
    int duplicate_orders = 0;
    int empty_orders = 0;
    double last_trade_price = 0.0;
    int last_trade_quantity = 0;

    void process_orders() {
        while (bids.size() && asks.size()) {
            Order* a = *(bids.begin());
            Order* b = *(asks.begin());
            if (a->getPrice() >= b->getPrice()) {
                int trade = min(b->getQuantity(), a->getQuantity());
                cout << "Trade: Quantity = " << trade << " at $" << b->getPrice() << " (Bid ID: " << a->getId() << ", Ask ID: " << b->getId() << ")\n\n";
                last_trade_price = b->getPrice();
                last_trade_quantity = trade;

                if (a->getQuantity() == trade) {
                    cancel_order(a->getId());
                } else {
                    a->modify(a->getQuantity() - trade, a->getPrice());
                }

                if (b->getQuantity() == trade) {
                    cancel_order(b->getId());
                } else {
                    b->modify(b->getQuantity() - trade, b->getPrice());
                }
            } else {
                break;
            }
        }
    }

    void print_midquote() {
        if (bids.empty() || asks.empty()) {
            cout << "Midquote: NAN\n";
            return;
        }
        double x = ((*bids.begin())->getPrice() + (*asks.begin())->getPrice()) / 2;
        cout << "Midquote: " << x << endl;
    }

    void print_spread() {
        if (bids.empty() || asks.empty()) {
            cout << "Spread: NAN\n";
            return;
        }
        double x = (*asks.begin())->getPrice() - (*bids.begin())->getPrice();
        cout << "Spread: " << x << endl;
    }

    void print_depth() {
        cout << "Depth Information:\n";
        cout << "Bids:\n";
        int level = 1;
        for (auto it = bids.begin(); it != bids.end() && level <= 5; ++it, ++level) {
            cout << "Level " << level << ": Quantity = " << (*it)->getQuantity() << endl;
        }
        cout << "Asks:\n";
        level = 1;
        for (auto it = asks.begin(); it != asks.end() && level <= 5; ++it, ++level) {
            cout << "Level " << level << ": Quantity = " << (*it)->getQuantity() << endl;
        }
    }

    void print_levelinfo() {
        cout << "Level Information:\n";
        cout << "Bids:\n";
        int level = 1;
        for (auto it = bids.begin(); it != bids.end() && level <= 5; ++it, ++level) {
            cout << "Level " << level << ": Price = " << (*it)->getPrice() << endl;
        }
        cout << "Asks:\n";
        level = 1;
        for (auto it = asks.begin(); it != asks.end() && level <= 5; ++it, ++level) {
            cout << "Level " << level << ": Price = " << (*it)->getPrice() << endl;
        }
    }

    void print_summary() {
        cout << "Summary:\n";
        if (last_trade_quantity) {
            cout << "Last Trade Price: " << last_trade_price << " Last Trade Quantity: " << last_trade_quantity << endl;
        }
        cout << "Corrupted messages: " << corrupted_messages << "\n";
        cout << "Duplicate order IDs: " << duplicate_orders << "\n";
        cout << "Empty order IDs: " << empty_orders << "\n";

        cout<<endl;
        print_order_book();
        print_levelinfo();
        print_depth();
    }

    void print_order_book() {
        cout << "Order Book:\n";
        cout << "Bids:\n";
        for (auto order : bids) {
            cout << "ID: " << order->getId() << " Price: " << order->getPrice() << " Quantity: " << order->getQuantity() << "\n";
        }
        cout << "Asks:\n";
        for (auto order : asks) {
            cout << "ID: " << order->getId() << " Price: " << order->getPrice() << " Quantity: " << order->getQuantity() << "\n";
        }
    }

public:
    OrderBook() : nextorderid(0), messages(0) {
        types = { "normal", "fillandkill" };
    }

    void add_order(char side, int id, int quantity, double price, string type) {
        Order* order = new Order(side, id, quantity, price, type);
        orders[id] = order;
        if (side == 'B') {
            bids.insert(order);
        } else {
            asks.insert(order);
        }

        process_orders();

        if (type == types[1]) {
            cancel_order(order->getId());
        }

        print_midquote();
        print_spread();
        cout<<endl;
        cout<<endl;
    }

    void cancel_order(int order_id) {
        if (orders.find(order_id) == orders.end()) {
            cout << "Order ID " << order_id << " not found.\n";
            return;
        }
        Order* order = orders[order_id];
        if (order->getSide() == 'B') {
            bids.erase(order);
        } else {
            asks.erase(order);
        }
        delete order;
        orders.erase(order_id);
    }

    void modify_order(int order_id, int quantity, double price) {
        if (orders.find(order_id) == orders.end()) {
            cout << "Order does not exist.\n";
            return;
        }
        Order* order = orders[order_id];
        if (order->getSide() == 'B') {
            bids.erase(order);
        } else {
            asks.erase(order);
        }
        order->modify(quantity, price);
        if (order->getSide() == 'B') {
            bids.insert(order);
        } else {
            asks.insert(order);
        }
        cout << "Successfully modified the order having ID " << order_id << endl;
        process_orders();
        print_midquote();
        print_spread();
    }

    void process_message(string msg) {
        messages++;
        istringstream ss(msg);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.empty()) {
            corrupted_messages++;
            return;
        }

        if (tokens[0] == "A" && tokens.size() == 6) { // A,side,oid,quantity,price,type
            char side = tokens[1][0];
            int order_id = stoi(tokens[2]);
            int quantity = stoi(tokens[3]);
            double price = stod(tokens[4]);
            string type = tokens[5];
            if (orders.find(order_id) != orders.end()) {
                duplicate_orders++;
                return;
            }
            if (quantity <= 0 || price <= 0 || (type != types[0] && type != types[1])) {
                corrupted_messages++;
                return;
            }
            add_order(side, order_id, quantity, price, type);
        } else if (tokens[0] == "X" && tokens.size() == 2) { // X,oid
            int order_id = stoi(tokens[1]);
            if (orders.find(order_id) == orders.end()) {
                corrupted_messages++;
                return;
            }
            cancel_order(order_id);
        } else if (tokens[0] == "M" && tokens.size() == 4) { // M,oid,quantity,price
            int order_id = stoi(tokens[1]);
            int quantity = stoi(tokens[2]);
            double price = stod(tokens[3]);
            if (orders.find(order_id) == orders.end()) {
                corrupted_messages++;
                return;
            }
            modify_order(order_id, quantity, price);
        } else {
            corrupted_messages++;
        }

        if (messages % 10 == 0) {
            print_summary();
            // print_order_book();
            // print_levelinfo();
            // print_depth();
        }
    }
};

int main() {
    OrderBook ob;
    vector<string> messages = {
        "A,B,1,1000,10,normal",
        "A,S,2,1075,10,normal",
        "A,B,3,975,5,normal",
        "A,S,4,1050,15,normal",
        "A,B,5,950,5,normal",
        "A,S,6,1025,10,fillandkill",
        "A,B,7,1000,10,normal",
        "X,5",
        "A,S,8,1025,5,normal",
        "A,B,9,950,5,normal",
        "M,7,15,1050" // Modify message
    };

    for (const auto& msg : messages) {
        ob.process_message(msg);
    }

    // ob.print_summary();

    return 0;
}
