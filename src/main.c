#include <stdio.h>
#include "product.h"
#include "cart.h"
#include "payment_menu.h"
#include "payment.h"
#include "log.h"

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

    // ================================
    // カート初期化
    // ================================
    Cart cart;
    initCart(&cart);

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
                printf("\nカートに追加しました。\n");
            }
        }

        else if (choice == 2) {
            displayCart(&cart);

            if (isCartEmpty(&cart)) {
                printf("カートは空です。\n");
                continue;
            }

            printf("\n1. 商品削除\n");
            printf("2. 数量変更\n");
            printf("0. 戻る\n");
            printf("番号を入力: ");

            int sub;
            scanf("%d", &sub);

            if (sub == 1) {
                int id;
                printf("削除する商品ID: ");
                scanf("%d", &id);
                if (removeFromCart(&cart, id))
                    printf("削除しました。\n");
                else
                    printf("該当商品がありません。\n");
            }
            else if (sub == 2) {
                int id, qty;
                printf("数量変更する商品ID: ");
                scanf("%d", &id);
                printf("新しい数量: ");
                scanf("%d", &qty);
                if (updateQuantity(&cart, id, qty))
                    printf("数量を変更しました。\n");
                else
                    printf("該当商品がありません。\n");
            }
        }


        else if (choice == 3) {

            if (isCartEmpty(&cart)) {
                printf("カートが空です。決済できません。\n");
                continue;
            }
            // 支払方法選択
            int method = selectPaymentMethod();

            if (method == 2) {  // 現金
                processCashPayment();
                saveTransactionData();
                clearCart(&cart);
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
