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

int removeFromCart(Cart *cart, int itemId) {
    for (int i = 0; i < cart->count; i++) {
        if (cart->items[i].item_id == itemId) {
            for (int j = i; j < cart->count - 1; j++) {
                cart->items[j] = cart->items[j + 1];
                cart->quantities[j] = cart->quantities[j + 1];
            }
            cart->count--;
            return 1;
        }
    }
    return 0;
}



int updateQuantity(Cart *cart, int itemId, int newQty) {
    for (int i = 0; i < cart->count; i++) {
        if (cart->items[i].item_id == itemId) {

            if (newQty <= 0) {
                return removeFromCart(cart, itemId);
            }

            cart->quantities[i] = newQty;
            return 1;
        }
    }
    return 0;
}


int isCartEmpty(const Cart *cart) {
    return cart->count == 0;
}


void clearCart(Cart *cart) {
    cart->count = 0;
}
