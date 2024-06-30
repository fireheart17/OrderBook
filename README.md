
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
