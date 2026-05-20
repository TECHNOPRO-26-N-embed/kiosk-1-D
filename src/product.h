// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_ITEMS 100

typedef struct {
    int item_id;
    char item_name[50];
    int price;
    float tax;
} Item;

// 関数プロトタイプ（宣言）
void displayProductList(Item items[], int count);
int inputProductId(void);
int isValidProductId(Item items[], int count, int input_id);
int inputQuantity(void);
int processProductSelection(Item items[], int count, int *selectedIndex, int *selectedQuantity);

#endif
