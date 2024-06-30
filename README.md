### Order Book Management System

This project implements an Order Book Management System using C++ that handles different types of orders (limit orders, fill-and-kill orders, market orders, and fill-or-kill orders). The system supports adding, modifying, and canceling orders, and processes trades accordingly.

### Files in the Project

1. **orderbook.cpp**: This file contains the implementation of the Order Book system.
2. **randomised_testgenerator.cpp**: This file contains a test generator to create randomized test cases for the Order Book system.

### Prerequisites

- A C++ compiler (e.g., g++)

### Compilation and Execution

1. **Compile the Order Book system**

   ```sh
   g++ -o orderbook orderbook.cpp
   ```

2. **Compile the Randomized Test Generator**

   ```sh
   g++ -o testgen randomised_testgenerator.cpp
   ```

3. **Run the Order Book system**

   ```sh
   ./orderbook
   ```

4. **Run the Randomized Test Generator**

   ```sh
   ./testgen
   ```

### Order Book (orderbook.cpp)

The Order Book system is designed to handle and process various types of orders in a financial market. It includes the following key components:

- **Order Class**: Represents an order with attributes such as type, side (bid/ask), order ID, quantity, and price.
- **OrderBook Class**: Manages the collection of orders, processes trades, and maintains the order book.
- **Trade Class**: Represents a trade with attributes such as bid ID, ask ID, quantity, and price.

### Key Features

1. **Order Types Supported**:
   - **Limit Order**: An order to buy or sell a stock at a specified price or better. It ensures that the order will only be executed at the limit price or a more favorable price.
   - **Fill and Kill Order (FAK)**: Also known as Immediate or Cancel (IOC), this order attempts to fill as much of the order as possible immediately. Any portion of the order that cannot be filled immediately is canceled.
   - **Market Order**: An order to buy or sell a stock immediately at the best available current price. This type of order prioritizes speed of execution over price, meaning the price is not specified. In the implementation, if a market order can only be partially filled, the system will fill it to the extent possible and cancel the remaining portion.
   - **Fill or Kill Order (FOK)**: An order that must be executed immediately and completely at the specified price. If the entire order cannot be filled at once, it is canceled.

2. **Order Operations**:
   - **Add Order**: Adds a new order to the order book.
   - **Modify Order**: Modifies an existing order in the order book.
   - **Cancel Order**: Cancels an existing order in the order book.
   - **Process Orders**: Processes trades by matching buy and sell orders.
3. **Trade Processing**:
   - **Process Trades**: Manages the trade execution based on order matching.
   - **Trade Reporting**: Outputs trade details with precision up to 5 decimal places.

4. **Order Book Summary**:
   - **Print Summary**: Prints a summary of the current state of the order book including best bid, best ask, and trade history.
   - **Midquote**: Calculates and returns the midquote, which is the average of the best bid and best ask prices.
   - **Spread**: Calculates and returns the spread, which is the difference between the best bid and best ask prices.
   - **Level Info**: Provides information about the order book at a specific level, such as price and quantity of orders.
   - **Depth**: Calculates and returns the total quantity of orders at a given price level or better.
   
### How to Use

1. **Adding an Order**:
   - Use the `add_order` method to add a new order.
   - Parameters: `type` (string), `side` (char), `id` (int), `quantity` (int), `price` (double).

   ```cpp
   ob.add_order("limitorder", 'B', 1, 10, 1000.0);
   ```

2. **Modifying an Order**:
   - Use the `modify_order` method to modify an existing order.
   - Parameters: `order_id` (int), `quantity` (int), `price` (double).

   ```cpp
   ob.modify_order(1, 5, 995.0);
   ```

3. **Canceling an Order**:
   - Use the `cancel_order` method to cancel an existing order.
   - Parameter: `order_id` (int).

   ```cpp
   ob.cancel_order(1);
   ```

4. **Processing a Message**:
   - Use the `process_message` method to process a message.
   - Parameter: `msg` (string).

   ```cpp
   ob.process_message("A,limitorder,B,1,10,1000");
   ```
5. **Printing Order Book Summary**:
   - Use the `print_summary` method to print the current state of the order book.

   ```cpp
   ob.print_summary();
   ```

### Randomized Test Generator (randomised_testgenerator.cpp)

The Randomized Test Generator creates randomized test cases to test the Order Book system.

### How to Use

1. **Generating Test Cases**:
   - Run the compiled test generator executable to generate test cases.

   ```sh
   ./testgen
   ```

2. **Testing**:
   - Use the generated test cases to test the Order Book system.

### Example Usage

Here is a simple example of how to use the Order Book system with test messages:

```cpp
int main() {
    OrderBook ob;
    vector<string> messages = {
        "A,limitorder,B,1,10,1000",        // Add buy limit order: id=1, quantity=10, price=1000
        "X,5",                             // Attempt to cancel non-existing order: id=5
        "M,2,5,1005",                      // Attempt to modify non-existing order: id=2
        "A,limitorder,B,1,10,1000",        // Add buy limit order: id=1, quantity=10, price=1000
        "A,limitorder,A,2,5,1005",         // Add sell limit order: id=2, quantity=5, price=1005
        "A,limitorder,B,3,7,995"           // Add buy limit order: id=3, quantity=7, price=995
    };

    for (const auto& msg : messages) {
        ob.process_message(msg);
    }

    return 0;
}
```

This project provides a robust framework for managing an order book in a financial market. The randomized test generator helps in validating the system with a variety of test cases.
