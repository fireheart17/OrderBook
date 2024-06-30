#include <bits/stdc++.h>
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

*/

class Order
{
    char Side;
    int Order_id, Quantity;
    double Price;
    string Type;

    friend struct CompareBid;
    // friend class OrderBook;
    

public:
    Order(string type, char side, int oid, int quantity, double price) : Type(type), Side(side), Order_id(oid), Quantity(quantity), Price(price) {}

    Order(string type, char side, int oid, int quantity) : // overloaded for market orders
         Type(type), Side(side), Order_id(oid), Quantity(quantity), Price(-1) {}

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
    { // overloaded for market orders;
        Quantity = quantity;
    }

    void print(){
    	cout<<"ID: "<<Order_id<<" Type: "<<Type<<" Side: "<<Side<<" Quantity: "<<Quantity<<" Price: "<<Price<<endl;
    }
};

struct CompareBid
{
    bool operator()(Order *a, Order *b) const
    {
        return a->Price > b->Price;
    }
};

class OrderBook
{

    unordered_map<int, Order *> orders;
    set<Order *, CompareBid> bids;
    set<Order *> asks;
    vector<string> types;
    int nextorderid;
    int messages;
    int corrupted_messages = 0;
    int duplicate_orders = 0;
    double last_trade_price = 0.0;
    int last_trade_quantity = 0;

    void process_fillorkill(Order *order)
    {
        int tot = 0;

        if (order->getSide() == 'B' && asks.size())
        {
            auto it = asks.begin();
            while (it != asks.end() && (*it)->getPrice() <= order->getPrice() && tot < order->getQuantity())
            {
                tot += (*it)->getQuantity();
                it++;
            }
            if (tot >= order->getQuantity())
            {
                while (order->getQuantity())
                {
                    it = asks.begin();

                    int trade = min((*it)->getQuantity(), order->getQuantity());

                    cout << "Trade: Quantity = " << trade << " at $" << (*it)->getPrice() << " (Bid ID: " << (order)->getId() << ", Ask ID: " << (*it)->getId() << ")\n\n";
                    last_trade_price = (*it)->getPrice();
                    last_trade_quantity = trade;

                    modify_order((*it)->getId(), (*it)->getQuantity() - trade, (*it)->getPrice());
                    modifyorderFAKorMarket(order->getId(), order->getQuantity() - trade, order->getPrice());

                    if ((*it)->getQuantity() == 0)
                    {
                        cancel_order((*it)->getId());
                    }
                }
            }
        }
        else if(bids.size())
        {

            auto it = bids.begin();
            while (it != bids.end() && (*it)->getPrice() >= order->getPrice() && tot < order->getQuantity())
            {
                tot += (*it)->getQuantity();
                it++;
            }

            if (tot >= order->getQuantity())
            {	

                while (order->getQuantity())
                {
                    it = bids.begin();
                    int trade = min((*it)->getQuantity(), order->getQuantity());

                    cout << "Trade: Quantity = " << trade << " at $" << order->getPrice() << " (Bid ID: " << (*it)->getId() << ", Ask ID: " << order->getId() << ")\n\n";
                    last_trade_price = order->getPrice();
                    last_trade_quantity = trade;

                    modify_order((*it)->getId(), (*it)->getQuantity() - trade, (*it)->getPrice());
                    modifyorderFAKorMarket(order->getId(), order->getQuantity() - trade, order->getPrice());
                    if ((*it)->getQuantity() == 0)
                    {
                        cancel_order((*it)->getId());
                    }
                }
            }

        }
        cancel_order(order->getId());
    }

    void process_market_order(Order *order)
    {
        if (order->getSide() == 'B')
        {
            while (order->getQuantity() && asks.size())
            {
                auto it = asks.begin();

                int trade = min((*it)->getQuantity(), order->getQuantity());

                cout << "Trade: Quantity = " << trade << " at $" << (*it)->getPrice() << " (Bid ID: " << (order)->getId() << ", Ask ID: " << (*it)->getId() << ")\n\n";
                last_trade_price = (*it)->getPrice();
                last_trade_quantity = trade;

                modify_order((*it)->getId(), (*it)->getQuantity() - trade, (*it)->getPrice());
                modifyorderFAKorMarket(order->getId(), order->getQuantity() - trade);

                if ((*it)->getQuantity() == 0)
                {
                    cancel_order((*it)->getId());
                }
            }
        }
        else
        {

            while (order->getQuantity() && bids.size())
            {

                auto it = bids.begin();

                int trade = min((*it)->getQuantity(), order->getQuantity());

                cout << "Trade: Quantity = " << trade << " at $" << (*it)->getPrice() << " (Bid ID: " << (*it)->getId() << ", Ask ID: " << order->getId() << ")\n\n";
                last_trade_price = (*it)->getPrice();
                last_trade_quantity = trade;

                modify_order((*it)->getId(), (*it)->getQuantity() - trade, (*it)->getPrice());
                modifyorderFAKorMarket(order->getId(), order->getQuantity() - trade);

                if ((*it)->getQuantity() == 0)
                {
                    cancel_order((*it)->getId());
                }
            }
        }

        cancel_order(order->getId());
    }

    void process_orders()
    {
        while (bids.size() && asks.size())
        {
            Order *a = *(bids.begin());
            Order *b = *(asks.begin());
            if (a->getPrice() >= b->getPrice())
            {
                int trade = min(b->getQuantity(), a->getQuantity());
                cout << "Trade: Quantity = " << trade << " at $" << b->getPrice() << " (Bid ID: " << a->getId() << ", Ask ID: " << b->getId() << ")\n\n";
                last_trade_price = b->getPrice();
                last_trade_quantity = trade;

                if (a->getQuantity() == trade)
                {
                    cancel_order(a->getId());
                }
                else
                {
                    a->modify(a->getQuantity() - trade, a->getPrice());
                }

                if (b->getQuantity() == trade)
                {
                    cancel_order(b->getId());
                }
                else
                {
                    b->modify(b->getQuantity() - trade, b->getPrice());
                }
            }
            else
            {
                break;
            }
        }
        print_midquote();
        print_spread();

        cout << endl
             << endl; // for limitorders and fillandkill orders
    }

    void print_midquote()
    {
        if (bids.empty() || asks.empty())
        {
            cout << "Midquote: NAN\n";
            return;
        }
        double x = ((*bids.begin())->getPrice() + (*asks.begin())->getPrice()) / 2;
        cout << "Midquote: " << x << endl
             << endl;
    }

    void print_spread()
    {
        if (bids.empty() || asks.empty())
        {
            cout << "Spread: NAN\n";
            return;
        }
        double x = (*asks.begin())->getPrice() - (*bids.begin())->getPrice();
        cout << "Spread: " << x << endl
             << endl;
    }

    void print_depth()
    {
        cout << "Depth Information:\n";
        cout << "Bids:\n";
        int level = 1;
        for (auto it = bids.begin(); it != bids.end() && level <= 5; ++it, ++level)
        {
            cout << "Level " << level << ": Quantity = " << (*it)->getQuantity() << endl;
        }
        cout << "Asks:\n";
        level = 1;
        for (auto it = asks.begin(); it != asks.end() && level <= 5; ++it, ++level)
        {
            cout << "Level " << level << ": Quantity = " << (*it)->getQuantity() << endl;
        }
        cout << endl;
    }

    void print_levelinfo()
    {
        cout << "Level Information:\n";
        cout << "Bids:\n";
        int level = 1;
        for (auto it = bids.begin(); it != bids.end() && level <= 5; ++it, ++level)
        {
            cout << "Level " << level << ": Price = " << (*it)->getPrice() << endl;
        }
        cout << "Asks:\n";
        level = 1;
        for (auto it = asks.begin(); it != asks.end() && level <= 5; ++it, ++level)
        {
            cout << "Level " << level << ": Price = " << (*it)->getPrice() << endl;
        }
        cout << endl;
    }

    

    void print_order_book()
    {
        cout << "Order Book:\n";
        cout << "Bids:\n";
        for (auto order : bids)
        {
            cout << "ID: " << order->getId() << " Price: " << order->getPrice() << " Quantity: " << order->getQuantity() << "\n";
        }
        cout << "Asks:\n";
        for (auto order : asks)
        {
            cout << "ID: " << order->getId() << " Price: " << order->getPrice() << " Quantity: " << order->getQuantity() << "\n";
        }
    }

public:

	void print_summary()
    {
        cout << "Summary:\n";
        if (last_trade_quantity)
        {
            cout << "Last Trade Price: " << last_trade_price << " Last Trade Quantity: " << last_trade_quantity << endl;
        }
        cout << "Corrupted messages: " << corrupted_messages << "\n";
        cout << "Duplicate order IDs: " << duplicate_orders << "\n";

        cout << endl;
        print_order_book();
        print_levelinfo();
        print_depth();
        cout << endl;
    }

    OrderBook() : nextorderid(0), messages(0)
    {
        types = {"limitorder", "fillandkill", "marketorder", "fillorkill"};
    }

    void add_order(string type, char side, int id, int quantity, double price)
    {
        Order *order = new Order(type, side, id, quantity, price);
        orders[id] = order;
        if (type == types[3])
        {
            process_fillorkill(order);
            return;
        }
        if (side == 'B')
        {
            bids.insert(order);
        }
        else
        {
            asks.insert(order);
        }

        process_orders();

        if (type == types[1])
        {
            cancel_order(order->getId());
        }
    }

    void cancel_order(int order_id)
    {
        if (orders.find(order_id) == orders.end())
        {
            return;
        }

        Order *order = orders[order_id];
        if (order->getSide() == 'B')
        {
            bids.erase(order);
        }
        else
        {
            asks.erase(order);
        }
        delete order;
        orders.erase(order_id);
    }

    void modify_order(int order_id, int quantity, double price)
    {
        if (orders.find(order_id) == orders.end())
        {
            cout << "Order does not exist.\n";
            return;
        }
        Order *order = orders[order_id];
        if (order->getSide() == 'B')
        {
            bids.erase(order);
        }
        else
        {
            asks.erase(order);
        }
        order->modify(quantity, price);
        if (order->getSide() == 'B')
        {
            bids.insert(order);
        }
        else
        {
            asks.insert(order);
        }
        cout << "Successfully modified the order having ID " << order_id << endl;

        process_orders();
    }

    void modifyorderFAKorMarket(int order_id, int quantity,double price)
    {
        Order *order = orders[order_id];
        order->modify(quantity,price);
    }

    void modifyorderFAKorMarket(int order_id, int quantity)
    { // overloaded for market orders
        Order *order = orders[order_id];
        order->modify(quantity);
    }

    void process_message(string msg)
    {
        messages++;
        istringstream ss(msg);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ','))
        {
            tokens.push_back(token);
        }
        if (tokens.empty())
        {
            corrupted_messages++;
            return;
        }

        if (tokens[0] == "A")
        { // A,side,oid,quantity,price,type
            if (tokens.size() == 5 && tokens[1] == types[2])
            { // market order
                string type = tokens[1];
                char side = tokens[2][0];
                int order_id = stoi(tokens[3]);
                int quantity = stoi(tokens[4]);
                if (orders.find(order_id) != orders.end())
                {
                    duplicate_orders++;
                }
                else if (quantity <= 0 || order_id<=0)
                {
                    corrupted_messages++;
                    return;
                }
                else
                { // not using add order here as we have separate process_market_order function
                    Order *order = new Order(type, side, order_id, quantity);
                    orders[order_id] = order;
                    process_market_order(order);
                }
            }
            else if (tokens.size() == 6)
            {
                string type = tokens[1];
                char side = tokens[2][0];
                int order_id = stoi(tokens[3]);
                int quantity = stoi(tokens[4]);
                double price = stod(tokens[5]);
                if (orders.find(order_id) != orders.end())
                {
                    duplicate_orders++;
                }
                else if (order_id<=0 || quantity <= 0 || price <= 0 || (type != types[0] && type != types[1] && type != types[3]))
                {
                    corrupted_messages++;
                }
                else
                {
                    add_order(type, side, order_id, quantity, price);
                }
            }
            else
            {
                corrupted_messages++;
            }
        }

        else if (tokens[0] == "X" && tokens.size() == 2)
        { // X,oid
            int order_id = stoi(tokens[1]);
            if (orders.find(order_id) == orders.end())
            {
                corrupted_messages++;
            }
            else
            {
                cancel_order(order_id);
            }
        }
        else if (tokens[0] == "M" && tokens.size() == 4)
        { // M,oid,quantity,price can't modify market orders
            int order_id = stoi(tokens[1]);
            int quantity = stoi(tokens[2]);
            double price = stod(tokens[3]);
            if (orders.find(order_id) == orders.end() || price <= 0 || quantity <= 0)
            {
                corrupted_messages++;
            }
            else
            {
                modify_order(order_id, quantity, price);
            }
        }
        else
        {
            corrupted_messages++;
        }

        if (messages % 10 == 0)
        {
            print_summary();
        }
    }

    ~OrderBook()
    {
    	if(orders.size()){
    		cout<<"Partially Executed Orders:-\n\n";
    	}
        while (orders.size())
        {
        	(*orders.begin()).second->print();
            cancel_order(orders.begin()->first);
        }
        bids.clear();
        asks.clear();
    }
};

int main()
{
    OrderBook ob;
    int n;
    cin>>n;
    while(n--){
    	string msg;
    	cin>>msg;
    	ob.process_message(msg);
    }
    ob.print_summary();

    return 0;
}
