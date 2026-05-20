// cart_test.c
#include <stdio.h>
#include <assert.h>
#include "cart.h"

int main(void) {
    // テスト用商品マスタ
    Product products[] = {
        {1, "りんご", 100, 0},
        {2, "バナナ", 150, 0},
        {3, "オレンジ", 200, 0},
    };
    size_t productCount = sizeof(products) / sizeof(products[0]);

    Cart cart;
    initCart(&cart);

    // 1. 追加テスト
    assert(addToCart(&cart, 1, 2) == 0); // りんご2個
    assert(addToCart(&cart, 2, 1) == 0); // バナナ1個
    assert(cart.count == 2);
    assert(cart.items[0].productId == 1);
    assert(cart.items[0].quantity == 2);

    // 2. 同一商品追加で数量加算
    assert(addToCart(&cart, 1, 3) == 0); // りんご +3 → 合計5
    assert(cart.items[0].quantity == 5);

    // 3. 小計計算
    int subtotal = calculateCartSubtotal(&cart, products, productCount);
    // りんご 100 * 5 = 500, バナナ 150 * 1 = 150 → 650
    assert(subtotal == 650);

    // 4. 数量変更
    assert(updateCartQuantity(&cart, 2, 4) == 0); // バナナ4個に
    subtotal = calculateCartSubtotal(&cart, products, productCount);
    // りんご 100 * 5 = 500, バナナ 150 * 4 = 600 → 1100
    assert(subtotal == 1100);

    // 5. 数量0で削除扱い
    assert(updateCartQuantity(&cart, 1, 0) == 0); // りんご削除
    assert(cart.count == 1);
    assert(cart.items[0].productId == 2);

    // 6. 削除テスト
    assert(removeFromCart(&cart, 2) == 0); // バナナ削除
    assert(isCartEmpty(&cart));

    // 7. 存在しない商品操作
    assert(removeFromCart(&cart, 999) == -1);
    assert(updateCartQuantity(&cart, 999, 10) == -1);

    printf("すべてのカート単体テストが成功しました。\n");
    return 0;
}
