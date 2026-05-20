#include <stdio.h>
#include "payment.h"
#include "globals.h"
#include "cart.h"
#include "product.h"

// カートの合計金額（税込）を返す
int calculateTotalAmount(void) {
    int total = 0;

    for (int i = 0; i < g_cart.count; i++) {
        Item item = g_cart.items[i];
        int qty = g_cart.quantities[i];

        // 税込価格 = 税抜価格 × (1 + 税率)
        int priceWithTax = (int)(item.price * (1.0f + item.tax));

        total += priceWithTax * qty;
    }

    return total;
}

int inputCashAmount(void) {
    int cash;
    printf("投入金額を入力してください: ");
    scanf("%d", &cash);
    return cash;
}

int calculateChange(int total, int cash) {
    return cash - total;
}

void processCashPayment(void) {
    int total = calculateTotalAmount();

    if (total <= 0) {
        printf("カートが空のため決済できません。\n");
        return;
    }

    printf("=== 現金決済 ===\n");
    printf("合計金額(税込): %d 円\n", total);

    int cash = 0;
    while (1) {
        cash = inputCashAmount();
        if (cash < total) {
            printf("投入金額が不足しています。あと %d 円必要です。\n", total - cash);
        } else {
            break;
        }
    }

    int change = calculateChange(total, cash);

    printf("支払い完了しました。\n");
    printf("お預かり: %d 円\n", cash);
    printf("お釣り: %d 円\n", change);
    printf("ありがとうございました！\n");
}
