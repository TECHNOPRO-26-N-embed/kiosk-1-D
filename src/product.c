// product.c
#include <stdio.h>
#include <string.h>
#include "product.h"

// 商品一覧表示
void displayProductList(Item items[], int count){
    printf("===== 商品一覧 =====\n");
    for(int i = 0; i < count; i++){
        printf("%d %s %d円 税率%.0f%%\n",
               items[i].item_id,
               items[i].item_name,
               items[i].price,
               items[i].tax * 100);
    }
}

// 商品ID入力
int inputProductId(void){
    int input_id;
    printf("\n商品番号を入力してください: ");
    if(scanf("%d", &input_id) != 1){
        while(getchar() != '\n');
        return -1;
    }
    return input_id;
}

// 商品存在チェック
int isValidProductId(Item items[], int count, int input_id){
    for(int i = 0; i < count; i++){
        if(items[i].item_id == input_id){
            return i;
        }
    }
    return -1;
}

// 数量入力
int inputQuantity(void){
    int quantity;
    while (1) {
        printf("数量を入力してください: ");
        if(scanf("%d", &quantity) != 1){
            while(getchar() != '\n');
            printf("数値を入力してください。\n\n");
            continue;
        }
        if(quantity >= 1){
            return quantity;
        }
        printf("数値は1以上で入力してください。\n\n");
    }
}

// 商品選択処理
int processProductSelection(Item items[], int count, int *selectedIndex, int *selectedQuantity){
    int inputId;
    int index;

    while(1){
        displayProductList(items, count);
        inputId = inputProductId();
        index = isValidProductId(items, count, inputId);

        if(index != -1){
            printf("\n選択された商品: %s\n", items[index].item_name);
            printf("価格: %d円\n", items[index].price);
            printf("税率: %.0f%%\n", items[index].tax * 100);

            *selectedQuantity = inputQuantity();
            *selectedIndex = index;

            printf("\n%d個 選択しました。\n", *selectedQuantity);
            return 1;
        }

        printf("\n商品番号が存在しません。\n\n");
    }
}
