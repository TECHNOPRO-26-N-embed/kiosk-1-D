# 🛠️ セルフレジ精算機システム — 詳細設計書

---

## 1. メインループ（改善版）

1. メインメニューを表示
2. ユーザー入力を受け付ける
3. 入力内容に応じて処理を分岐
   - "1" → 購入処理へ進む
   - "0" → プログラム終了
   - その他 → エラーメッセージを表示し再入力
4. 処理完了後、メインメニューへ戻る


void runMainLoop(void);
int showMainMenu(void);


---

## 2. 個別機能アルゴリズム（更新済）

### ● 機能1：商品選択処理（バーコード削除）


1. 商品一覧を表示
2. 商品IDを入力
3. 商品の存在チェック
   - 存在しない → エラー表示 → 再入力
4. 数量を入力
5. カートに追加
6. 商品一覧画面へ戻る


// 商品一覧を表示
void displayProductList(void);

// 商品IDの入力
int inputProductId(void);

// 商品IDが存在するかチェック
// 戻り値: 1 = 存在する, 0 = 存在しない
int isValidProductId(int productId);

// 数量入力
int inputQuantity(void);

// カートに商品を追加
// 戻り値: 0 = 成功, -1 = 失敗
int addToCart(int productId, int quantity);

// 商品選択処理のメイン関数
void processProductSelection(void);

---

### ● 機能2：カート確認


1. カート内容を表示
2. 操作選択（削除 / 数量変更 / 戻る）
3. 入力に応じて処理
   - 削除 → 指定商品を削除
   - 数量変更 → 新しい数量を入力
   - 戻る → 前の画面へ


// カート内容を表示
void displayCart(void);

// カート操作メニュー表示
int showCartMenu(void);

// カートから商品削除
// 戻り値: 0 = 成功, -1 = 失敗
int removeFromCart(int productId);

// カート数量変更
// 戻り値: 0 = 成功, -1 = 失敗
int updateCartQuantity(int productId, int newQuantity);

// カート確認処理メイン
void processCartMenu(void);

---

### ● 機能3：決済方法選択


1. 決済方法を選択（現金 / QR / 戻る）
2. 現金 → 現金決済処理へ
3. QR → 将来拡張（未実装）
4. 戻る → カート画面へ


// 決済方法メニュー表示
int selectPaymentMethod(void);

// 決済処理メイン
void processPayment(void);

---

### ● 機能4：現金決済


1. 合計金額を表示
2. 投入金額を入力
3. 不足している場合 → 不足金額を表示 → 再入力
4. お釣りを計算
5. 完了画面へ遷移


// 合計金額計算
int calculateTotalAmount(void);

// 投入金額入力
int inputCashAmount(void);

// お釣り計算
int calculateChange(int total, int cash);

// 現金決済処理メイン
void processCashPayment(void);


---

### ● 機能5：ログ保存


1. 取引IDを生成
2. 日時を取得
3. カート内容を集計
4. 税額を計算
5. CSV形式に整形
6. 取引ログCSVへ追記
7. 明細CSVへ追記

// 取引ID生成
long generateTransactionId(void);

// 現在日時取得（文字列）
void getCurrentDateTime(char *buffer, int size);

// 税額計算
int calculateTaxAmount(int price, int taxType);

// 取引ログCSVへ保存
int saveTransactionLog(long transactionId, const char *datetime, int totalAmount, int taxAmount, int paymentMethod);

// カート明細CSVへ保存
int saveCartDetails(long transactionId);

// ログ保存メイン処理
void saveTransactionData(void);

---

## 3. エラーハンドリング（更新済）

| 異常系 | 対処 |
|-------|------|
| 存在しない商品ID | 「商品が見つかりません」表示 |
| 数量が0以下 | 「数量は1以上を入力してください」 |
| カート空で確定 | 「カートが空です」 |
| 決済方法の誤入力 | 再入力を促す |
| 現金不足 | 不足金額を表示 |
| CSV保存失敗 | エラーログに記録 |

---

## 4. 構造体
typedef struct {
    int id;
    char name[64];
    int price;
    int taxType;
} Product;

typedef struct {
    int productId;
    int quantity;
} CartItem;


