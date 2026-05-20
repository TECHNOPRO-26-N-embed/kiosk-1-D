#ifndef CART_H
#define CART_H

#include "product.h"

typedef struct {
    Item items[100];
    int quantities[100];
    int count;
} Cart;

void initCart(Cart *cart);
int addToCart(Cart *cart, Item item, int quantity);
void displayCart(const Cart *cart);
void clearCart(Cart *cart);

#endif
