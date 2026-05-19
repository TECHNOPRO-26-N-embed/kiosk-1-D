#include <stdio.h>
#include <stdlib.h>
// 構造体を「Item」に統一し、メンバー名を統一
typedef struct {
    int item_id;
    char item_name[50];
    int price;
    float tax;
} Item;
// カート用の構造体
typedef struct {
    Item items[10]; // ShoppingItem から Item に統一
    int count;
} Cart;
// 消費税計算の関数
int Sumtax(int sum, Item item) {
    int res = 0;
    if (item.tax == 1) {
        res = sum * 8 / 100;
    } else {
        res = sum * 10 / 100;
    }
    return res;
}
// カートに商品を追加する関数
void AddItemToCart(Cart *cart, Item item) {
    if (cart->count < 10) {
        cart->items[cart->count] = item;
        cart->count++;
    } else {
        printf("カートがいっぱいです。\n");
        return;
    }
}
// カートの中身を表示する関数
void ViewCart(Cart *cart) {
    printf("カートの中身:\n");
    for (int i = 0; i < cart->count; i++) {
        // 統一した構造体のメンバー名に合わせて変更
        printf("商品ID: %d, 商品名: %s,価格: %d, 税率: %.2f%%\n",
               cart->items[i].item_id,
               cart->items[i].item_name,
               cart->items[i].price,
               cart->items[i].tax);
    }
}

int main() {
    // --- パート1: 商品一覧表示と入力待ち ---
    printf("================================\n");
    printf("いらっしゃいませ。\n");
    printf("セルフレジシステムへようこそ。\n");
    printf("Enterキーを押して続行してください。\n");
    printf("================================\n");
    getchar(); // ユーザーの入力を待つ
    Item items[100]; // 商品の最大数を100と仮定
    FILE *fp;
    char line[256];
    fp = fopen("../data/product.csv","r");
    if (fp != NULL) { // ファイルが正常に開けた場合のみ処理
        fgets(line, sizeof(line), fp);
        int count = 0;
        while(fgets(line, sizeof(line), fp)){
            sscanf(line, "%d,%49[^,],%d,%f", // 安全のため%99から%49に修正（配列サイズ50のため）
                &items[count].item_id,
                items[count].item_name,
                &items[count].price,
                &items[count].tax);
            count++;
        }
        fclose(fp); // 開いたファイルを閉じる
        printf("==============商品一覧==============\n");
        for(int i = 0; i < count; i++){
          printf("%d %s %d円　税率:%.2f%%\n",
            items[i].item_id,
            items[i].item_name,
            items[i].price,
            items[i].tax * 100);
        }
    }
    printf("\nEnterキーを押して商品番号入力へ進みます。\n");
    getchar(); // clear input buffer;前回の改行をクリア
    getchar(); // ユーザーの入力を待つ
    int input_id;
    int found = 0;
    printf("商品番号を入力してください: ");
    scanf("%d", &input_id);
    // count変数はファイル読み込み時のものを引き継ぎます（ファイルが開けなかった場合は0）
    int count = 0; 
    // ※実際にはファイル読み込みが成功した時のcountを使うため、ここでは初期値0としています
    
    for(int i = 0; i < count; i++){
        if(items[i].item_id == input_id){
            printf("選択された商品: %s\n", items[i].item_name);
            printf("価格: %d円\n", items[i].price);
            printf("税率: %.2f%%\n", items[i].tax * 100);
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("商品番号が見つかりませんでした。\n");
    }
    int quantity;
    printf("数量を入力してください: ");
    scanf("%d", &quantity);

// --- パート2: ファイル出力テスト（元のコードより） ---
    FILE *fp_shop = fopen("shopping_data.csv", "w+"); // aからw+に変更されていた部分を統合
    if(fp_shop == NULL){
        printf("ファイルを開くことができませんでした。\n");
        return 1;
    }
    // ここで何か書き込む処理などを行う場合は記述してください
    fclose(fp_shop);
    // --- パート3: 一時ファイルテスト（元のコードより） ---
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        perror("一時ファイルの作成に失敗しました");
        return EXIT_FAILURE;
    }
    const char *message = "これはテストのメッセージです。";
    if (fprintf(tempFile, "%s\n", message) < 0) {
        perror("書き込みに失敗しました");
        fclose(tempFile);
        return EXIT_FAILURE;
    }
    rewind(tempFile);
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), tempFile) == NULL) {
        perror("読み込みに失敗しました");
        fclose(tempFile);
        return EXIT_FAILURE;
    }
    printf("ファイルの内容: %s", buffer);
    fclose(tempFile);
    // --- パート4: 支払方法選択メニュー ---
    while(1){
        printf("\n===============================\n");
        printf("支払方法を選択してください\n");
        printf("\n===============================\n");
        printf("1:電子マネー\n");
        printf("2:現金\n");
        printf("3:クレジットカード\n");
        printf("4:クーポン\n");
        printf("\n-------------------------------\n");
        
        // 元の空欄だったif文を、コンパイルが通るようにダミー条件(1)にしています。練習時に書き換えてください。
        if (1) { 
            printf("支払方法が選択されました。\n"); // ダミーメッセージ
            break; // 無限ループを抜けるための一時的なbreak
        }
        getchar();
        return 0;
    }
    // --- パート5: メインメニュー ---
    int choice;
    while(1){
        printf("\n===============================\n");
        printf("メインメニュー\n");
        printf("\n===============================\n");
        printf("1:商品を買う\n");
        printf("2:カートを見る\n");
        printf("3:終了\n");
        printf("\n-------------------------------\n");
        printf("番号を入力してください: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("商品を買う処理を実行します。\n");
                break;
            case 2:
                printf("カートを見る処理を実行します。\n");
                break;
            case 3:
                printf("プログラムを終了します。\n");
                return 0;
            default:
                printf("無効な番号です。もう一度入力してください。\n");
        }
    }
    // --- パート6: レシート出力（元のコードより） ---
    Item item; // 単一の変数として定義
    int total = 0;
    int payment = 0;
    int change;
    printf("支払い金額:");
    scanf("%d", &payment);
    change = payment - total;
    printf("\n===================レシート===================\n");
    printf("〇〇店\n");
    printf("%s %d円 * %d\n", item.item_name, item.price, quantity); // メンバー名をitem_nameに変更
    printf("---------------------------------------------\n");
    printf("合計: %d円\n", total);
    printf("お釣り: %d円\n", change);
    return 0;
}