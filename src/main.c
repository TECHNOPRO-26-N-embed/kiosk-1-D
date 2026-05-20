#include <stdio.h>
#include "product.h"
#include "cart.h"
#include "payment_menu.h"
#include "payment.h"
#include "log.h"
#include "globals.h"   // ← 追加

int main(void) {

    // ================================
    // 商品マスタ読み込み
    // ================================
    Item items[MAX_ITEMS];
    int count = 0;

    FILE *fp = fopen("data/product.csv", "r");
    if (!fp) {
        printf("商品データを開けませんでした。\n");
        return 1;
    }

    char line[256];
    fgets(line, sizeof(line), fp);  // ヘッダー読み飛ばし

    while (count < MAX_ITEMS && fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d,%49[^,],%d,%f",
               &items[count].item_id,
               items[count].item_name,
               &items[count].price,
               &items[count].tax);
        count++;
    }
    fclose(fp);

    // globals に商品マスタをコピー
    for (int i = 0; i < count; i++) {
        g_items[i] = items[i];
    }
    g_itemCount = count;

    // ================================
    // カート初期化
    // ================================
    Cart cart;
    initCart(&cart);
    g_cart = cart;  // globals に反映

    // ================================
    // メインループ
    // ================================
    while (1) {
        printf("\n===== メインメニュー =====\n");
        printf("1. 商品を選ぶ\n");
        printf("2. カートを見る\n");
        printf("3. 決済する\n");
        printf("0. 終了\n");
        printf("番号を入力: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            // 商品選択
            int selectedIndex = -1;
            int selectedQuantity = 0;

            if (processProductSelection(items, count, &selectedIndex, &selectedQuantity)) {
                addToCart(&cart, items[selectedIndex], selectedQuantity);
                g_cart = cart;  // globals に反映
                printf("\nカートに追加しました。\n");
            }
        }

        else if (choice == 2) {
            // カート表示
            displayCart(&cart);
        }

        else if (choice == 3) {
            // 支払方法選択
            int method = selectPaymentMethod();

            if (method == 2) {  // 現金
                processCashPayment();
                saveTransactionData();
                clearCart(&cart);
                g_cart = cart;  // globals に反映
            } else {
                printf("この支払方法はまだ実装されていません。\n");
            }
        }

        else if (choice == 0) {
            printf("終了します。\n");
            break;
        }

        else {
            printf("1〜3の番号を入力してください。\n");
        }
    }

    return 0;
}
