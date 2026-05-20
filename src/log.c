// log.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

// -----------------------------
// 取引ID生成
// -----------------------------
long generateTransactionId(void) {
    static long id = 100000;  // 簡易的に連番
    return id++;
}

// -----------------------------
// 現在日時取得
// -----------------------------
void getCurrentDateTime(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
}

// -----------------------------
// 税額計算
// taxType: 0=非課税, 1=10%, 2=8%
// -----------------------------
int calculateTaxAmount(int price, int taxType) {
    switch (taxType) {
        case 1: return price * 10 / 100;
        case 2: return price * 8 / 100;
        default: return 0;
    }
}

// -----------------------------
// 取引ログCSVへ保存
// -----------------------------
int saveTransactionLog(long transactionId, const char *datetime, int totalAmount, int taxAmount, int paymentMethod) {
    FILE *fp = fopen("transaction_log.csv", "a");
    if (!fp) return -1;

    fprintf(fp, "%ld,%s,%d,%d,%d\n",
            transactionId, datetime, totalAmount, taxAmount, paymentMethod);

    fclose(fp);
    return 0;
}

// -----------------------------
// カート明細CSVへ保存
// ※ 本来はカートの中身をループして書く
// -----------------------------
int saveCartDetails(long transactionId) {
    FILE *fp = fopen("cart_details.csv", "a");
    if (!fp) return -1;

    // 本来はカートの内容を保存する
    // 今はサンプルとして固定値
    fprintf(fp, "%ld,%s,%d,%d\n",
            transactionId, "SampleItem", 2, 500);

    fclose(fp);
    return 0;
}

// -----------------------------
// ログ保存メイン処理
// -----------------------------
void saveTransactionData(void) {
    long transactionId = generateTransactionId();

    char datetime[32];
    getCurrentDateTime(datetime, sizeof(datetime));

    // 本来はカートから計算する
    int totalAmount = 2000;
    int taxAmount = calculateTaxAmount(totalAmount, 1);  // 10% 税
    int paymentMethod = 1; // 例：1=現金

    if (saveTransactionLog(transactionId, datetime, totalAmount, taxAmount, paymentMethod) != 0) {
        printf("取引ログ保存に失敗しました\n");
        return;
    }

    if (saveCartDetails(transactionId) != 0) {
        printf("明細保存に失敗しました\n");
        return;
    }

    printf("取引データを保存しました（ID: %ld）\n", transactionId);
}
