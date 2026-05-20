#include <stdio.h>
#include "cart.h"

void initCart(Cart *cart) {
    cart->count = 0;
}

int addToCart(Cart *cart, Item item, int quantity) {
    cart->items[cart->count] = item;
    cart->quantities[cart->count] = quantity;
    cart->count++;
    return 1;
}

void displayCart(const Cart *cart) {
    printf("=== カート内容 ===\n");
    for (int i = 0; i < cart->count; i++) {
        printf("%s × %d個 (%d円)\n",
               cart->items[i].item_name,
               cart->quantities[i],
               cart->items[i].price);
    }
}

void clearCart(Cart *cart) {
    cart->count = 0;
}
