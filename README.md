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

## Other Order Types

- **Fill and Kill (FAK) Order**: FAK orders are immediately executed against resting orders. Any quantity that remains unfilled is cancelled.

- **Fill or Kill (FOK) Order**: FOK orders are cancelled if not immediately filled for the total quantity at the specified price or better.

- **Give Up**: An order to be given to another member firm in the clearing system, an allocation. An order executed by clearing firm A and given to clearing firm B where it will be cleared and processed. Give up order indicator is "GU" populated in the F-Ex field.

- **Good Till Cancel (GTC) Order**: GTC orders remain open until they are completely executed or cancelled.

- **Good Till Date (GTD) Order**: GTD orders expire either at a specified date or when the security expires.

- **In Flight Mitigation (IFM)**: Customers who use the IFM Cancel/Replace functionality are able to mitigate in flight fills and prevent overfilling.

- **Limit Order**: Limit orders allow customers to define the maximum price for buying a security or the minimum price for selling a security.
  - **Buy Orders**: Executed at or below the limit price.
  - **Sell Orders**: Executed at or above the limit price.

- **Market Limit Order**: Market Limit orders are executed at the best available price on the opposite side of the market. If the order cannot be completely filled, the order becomes a Limit order and the remaining quantity rests on the order book at the fill price. If no market is available, the order is rejected.

- **Market Order**: A Market order (with protection) has a protection range limiting the price at which an order can trade. Market orders (with protection) are assigned Protection Price Limits based upon pre-defined protection points and the best available price on the opposite side of the market.

- **Minimum Quantity**: Minimum quantity of an order to be executed. This tag can be used in conjunction with FAK.

- **Maximum Quantity Display**: Maximum quantity of an order to be shown in the order book to other customers at any given time.

- **Route-Through**: Route-Through allows firms to submit orders for clients, as well as other clearing members for whom the firm is authorized to do business. This occurs by changing the firm within the SenderCompID to the one assigned to another firm.

- **Stop Order**: A Stop order (with protection) has a protection range limiting the price at which an order can trade. When a Stop order (with protection) is triggered, it becomes a Limit order at the Protection Price Limit.

- **Stop Limit Order**: Stop Limit orders are activated when an order's trigger price is traded in the market. The order is executed at all price levels between the trigger price and the limit price. For buy orders, the trigger price is lower than the best available price on the opposite side of the market.

### Financial Market Terms

**Market makers** are firms or individuals that actively buy and sell securities, providing liquidity to the market. They play a crucial role in ensuring that there is always a counterparty for investors looking to buy or sell securities. Market makers profit from the bid-ask spread, which is the difference between the buying (bid) and selling (ask) prices of a security.

### Liquidity
**Liquidity** refers to the ease with which an asset can be bought or sold in the market without affecting its price. High liquidity means that an asset can be quickly sold or bought with minimal price fluctuation. For example, major stocks like Apple or Microsoft are considered highly liquid because they are traded frequently and in large volumes.

### Bid-Ask Spread
The **bid-ask spread** is the difference between the highest price a buyer is willing to pay for a security (the bid) and the lowest price a seller is willing to accept (the ask). A narrower spread often indicates a more liquid market, while a wider spread can indicate less liquidity and higher trading costs.

### Volatility
**Volatility** measures the degree of variation of a trading price series over time. It is often quantified as the standard deviation of returns. High volatility indicates large price swings, while low volatility suggests relatively stable prices.

### Arbitrage
**Arbitrage** involves the simultaneous purchase and sale of an asset in different markets to exploit price differences. Traders who practice arbitrage aim to profit from the discrepancies without any risk, although in practice, risks can still be present.

### Derivatives
**Derivatives** are financial instruments whose value is derived from the value of an underlying asset. Common types of derivatives include options, futures, and swaps. These instruments are often used for hedging risks or for speculative purposes.

### Hedge Funds
**Hedge funds** are investment funds that employ various strategies to earn active returns for their investors. They can invest in a wide range of assets and use techniques like leverage, short-selling, and derivatives to enhance returns.

### Index Funds
**Index funds** are mutual funds or exchange-traded funds (ETFs) designed to replicate the performance of a specific index, such as the S&P 500. They offer broad market exposure, low operating expenses, and low portfolio turnover.

### Bonds
**Bonds** are debt securities issued by corporations, municipalities, or governments to raise capital. Investors in bonds are essentially lending money to the issuer in exchange for periodic interest payments and the return of the bond's face value at maturity.

### Equity
**Equity** represents ownership in a company, typically in the form of stocks. Shareholders are entitled to a portion of the company’s profits, usually distributed as dividends, and have voting rights on corporate matters.

### Mutual Funds
**Mutual funds** are investment vehicles that pool money from many investors to purchase a diversified portfolio of stocks, bonds, or other securities. They are managed by professional portfolio managers and offer investors an easy way to diversify their holdings.

### Exchange-Traded Funds (ETFs)
**ETFs** are investment funds traded on stock exchanges, similar to stocks. They hold assets such as stocks, commodities, or bonds and generally aim to track an index. ETFs offer the diversification of mutual funds with the flexibility of stock trading.

These terms are foundational to understanding the dynamics of financial markets and the various strategies and instruments involved in trading and investment.

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
