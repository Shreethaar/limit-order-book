#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDERS 100 

typedef struct {
	int price;
	int quantity;
} Order;

typedef struct {
	Order orders[MAX_ORDERS];
	int count;
} OrderBook;

void init_order_book(OrderBook *book) {
	book->count=0;
}
void add_order(OrderBook *book, int price, int quantity) {
	if(book->count < MAX_ORDERS) {
		Order *new_order=&(book->orders[book->count]);
		new_order->price=price;
		new_order->quantity=quantity;
		book->count++;
	}
	else {
		printf("Fulled order book\n");
	}
}
void match_order(OrderBook *book, int buy_price, int sell_price) {
	for(int i=0;i<book->count;i++) {
		if(book->orders[i].price<=buy_price) {
			printf("Buy order matched: Price: %d, Quantity: %d\n",book->orders[i].price, book->orders[i].quantity);
			for(int j=i;j<book->count-1;j++) {
				 book->orders[j] = book->orders[j + 1];
			}
            		book->count--;
            		i--;
		}
	}
	for(int i = 0; i < book->count; i++) {
		if (book->orders[i].price >= sell_price) {
			printf("Sell order matched: Price: %d, Quantity: %d\n", book->orders[i].price, book->orders[i].quantity);
			for(int j = i; j < book->count - 1; j++) {
				book->orders[j] = book->orders[j + 1];
			}
			book->count--;
		}
	}
}
int main() {
	OrderBook book;
	init_order_book(&book);
	add_order(&book,100,10);
	add_order(&book,95,20);
	add_order(&book,120,40);
	
	match_order(&book,100,120);
	return 0;
}


