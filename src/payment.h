// payment.h
#ifndef PAYMENT_H
#define PAYMENT_H

// 合計金額計算（本来はカートから計算する）
int calculateTotalAmount(void);

// 投入金額入力
int inputCashAmount(void);

// お釣り計算
int calculateChange(int total, int cash);

// 現金決済処理メイン
void processCashPayment(void);

#endif
