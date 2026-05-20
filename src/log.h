// log.h
#ifndef LOG_H
#define LOG_H

// 取引ID生成
long generateTransactionId(void);

// 現在日時取得
void getCurrentDateTime(char *buffer, int size);

// 税額計算
int calculateTaxAmount(int price, int taxType);

// 取引ログ保存
int saveTransactionLog(long transactionId, const char *datetime, int totalAmount, int taxAmount, int paymentMethod);

// カート明細保存
int saveCartDetails(long transactionId);

// ログ保存メイン処理
void saveTransactionData(void);

#endif
