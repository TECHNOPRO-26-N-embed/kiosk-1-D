// payment.c
#include <stdio.h>
#include "payment.h"

// 合計金額（本来はカート集計結果を返す）
// 今はテスト用に固定値
int calculateTotalAmount(void) {
    return 1500;  // 例：1500円
}

// 投入金額を入力
int inputCashAmount(void) {
    int cash;
    printf("投入金額を入力してください: ");
    scanf("%d", &cash);
    return cash;
}

// お釣り計算
int calculateChange(int total, int cash) {
    return cash - total;
}

// 現金決済処理メイン
void processCashPayment(void) {
    int total = calculateTotalAmount();
    int cash = 0;
    int change = 0;

    printf("=== 現金決済 ===\n");
    printf("合計金額: %d 円\n", total);

    while (1) {
        cash = inputCashAmount();

        if (cash < total) {
            printf("投入金額が不足しています。あと %d 円必要です。\n", total - cash);
        } else {
            break;
        }
    }

    change = calculateChange(total, cash);

    printf("支払い完了しました。\n");
    printf("お預かり: %d 円\n", cash);
    printf("お釣り: %d 円\n", change);
    printf("ありがとうございました！\n");
}
