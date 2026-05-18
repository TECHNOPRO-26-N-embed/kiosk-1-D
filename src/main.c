#include <stdio.h>

int main(){
    printf("================================\n");
    printf("いらっしゃいませ。\n");
    printf("セルフレジシステムへようこそ。\n");
    printf("Enterキーを押して続行してください。\n");
    printf("================================\n");

    getchar(); // ユーザーの入力を待つ

    typedef struct {
        int item_id;
        char item_name[50];
        int price;
        float tax;
    } Item;

    Item items[100]; // 商品の最大数を100と仮定

    FILE *fp;
    char line[256];
    fp = fopen("../data/product.csv","r");
    fgets(line,sizeof(line),fp);

    int count = 0;
    while(fgets(line,sizeof(line),fp)){
        sscanf(line,"%d,%99[^,],%d,%f",
            &items[count].item_id,
            items[count].item_name,
            &items[count].price,
            &items[count].tax);
        count++;
    }

    printf("==============商品一覧==============\n");
    for(int i = 0; i < count; i++){
      printf(  "%d %s %d円　税率:%.2f%%\n",
        items[i].item_id,
        items[i].item_name,
        items[i].price,
        items[i].tax * 100);
    }
    printf("\nEnterキーを押して商品番号入力へ進みます。\n");
    getchar(); // clear input buffer;前回の改行をクリア
    getchar(); // ユーザーの入力を待つ

    int input_id;
    int found = 0;
    printf("商品番号を入力してください: ");
    scanf("%d", &input_id);

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

    return 0;



}
#include <stdio.h>
typedef struct {
int item_id;
char item_name[50];
int price;
float tax;
} ShoppingItem;
int main (){
    FILE *fp = fopen("shopping_data.csv", "a");
    if(fp==NULL){
        printf("ファイルを開くことができませんでした。\n");
         fclose(fp);
        return 1;
    }







#include <stdio.h>
#include <stdlib.h>
int main(void) {
    // 一時ファイルを作成
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        // エラーが発生した場合は標準エラー出力にメッセージを表示
        perror("一時ファイルの作成に失敗しました");
        return EXIT_FAILURE;
    }
    // 一時ファイルに文字列を書き込む
    const char *message = "これはテストのメッセージです。";
    if (fprintf(tempFile, "%s\n", message) < 0) {
        perror("書き込みに失敗しました");
        fclose(tempFile);
        return EXIT_FAILURE;
    }
    // ファイルポインタを先頭に戻す
    rewind(tempFile);
    // ファイルから文字列を読み込むためのバッファ
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), tempFile) == NULL) {
        perror("読み込みに失敗しました");
        fclose(tempFile);
        return EXIT_FAILURE;
    }
    // 読み込んだ内容を表示
    printf("ファイルの内容: %s", buffer);
    // 一時ファイルを閉じる(ここでファイルは自動削除される)
    fclose(tempFile);
    return EXIT_SUCCESS;
}









#include <stdio.h>

int main() {
    while(1){
        printf("\n===============================\n");
        printf("支払方法を選択してください\n");
        printf("\n===============================\n");
        printf("1:電子マネー\n");
        printf("2:現金\n");
        printf("3:クレジットカード\n");
        printf("4:クーポン\n");
        printf("\n-------------------------------\n");
    if () {
        printf();
  }

        getchar();
        return 0;
    }
}







#include <stdio.h>

typedef struct {
    int item_id;
    char item_name[50];
    int price;
    float tax;
} Item;
/*----------------------------*/
typedef struct {
    Item items[10];
    int count;
} Cart;
/*-----------------------------*/
int main() {
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
                // 商品を買う処理
                printf("商品を買う処理を実行します。\n");
                break;
            case 2:
                // カートを見る処理
                printf("カートを見る処理を実行します。\n");
                break;
            case 3:
                // 終了処理
                printf("プログラムを終了します。\n");
                return 0;
            default:
                printf("無効な番号です。もう一度入力してください。\n");
        }
    }
    return 0;
}





int Sumtax(int sum, Item item) {
    int res = 0;
    if (item.tax == 1) {
        res = sum * 8 / 100;
    } else {
        res = sum * 10 / 100;
    }
    return res;
}

void AddItemToCart(Cart *cart, Item item) {
    if (cart->count < 10) {
        cart->items[cart->count] = item;
        cart->count++;
    } else {
        printf("カートがいっぱいです。\n");
        return;
    }
}

void ViewCart(Cart *cart) {
    printf("カートの中身:\n");
    for (int i = 0; i < cart->count; i++) {
        printf("商品ID: %d, 商品名: %s,価格: %d, 税率: %.2f%%\n",
               cart->items[i].item_id,
               cart->items[i].item_name,
               cart->items[i].price,
               cart->items[i].tax);
    }
}





#include<stdio.h>

struct Item {
    char name[20];
    int price;
};

int main(){

    struct Item item;

    int quantity;
    int total;
    int payment;
    int change;

    printf("支払い金額:");
    scanf("%d", &payment);

    change = payment - total;
    printf("\n===================レシート===================\n");

    printf("%s %d円 * %d\n", item.name, item.price, quantity);

    printf("---------------------------------------------\n");
    printf("合計: %d円\n", total);
    printf("お釣り: %d円\n", change);

    return 0;
}





#include <stdio.h>
typedef struct {
int item_id;
char item_name[50];
int price;
float tax;
} ShoppingItem;
int main (){
    FILE *fp = fopen("shopping_data.csv", "w+");
    if(fp==NULL){
        printf("ファイルを開くことができませんでした。\n");
         fclose(fp);
        return 1;
    }