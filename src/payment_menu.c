// payment_menu.c
#include <stdio.h>
#include "payment_menu.h"

int selectPaymentMethod(void) {
    int choice;

    while (1) {
        printf("\n===============================\n");
        printf("支払方法を選択してください\n");
        printf("===============================\n");
        printf("1: 電子マネー\n");
        printf("2: 現金\n");
        printf("3: クレジットカード\n");
        printf("4: クーポン\n");
        printf("-------------------------------\n");
        printf("番号を入力: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // バッファクリア
            printf("数値を入力してください。\n");
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            printf("支払方法が選択されました。\n");
            return choice;
        }

        printf("1〜4の番号を入力してください。\n");
    }
}
