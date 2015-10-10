#include <stdio.h>
#include <math.h>

int main() {

    int sigX[100] = {0};    // 入力信号
    int smp = 0;            // 入力信号のサンプリング数
    int mul = 0;            // 乗数
    int tmp;                // アダマール行列作成時の途中計算（論理積）

    // フーリエ変換する信号を入力
    printf("信号を入力（10000以上を入力して入力終了）\n");
    for (int i = 0; sigX[smp] < 10000; i++, smp = i - 1) {
        printf("> ");
        scanf("%d", &sigX[i]);
    }

    int sigY[smp][smp]; // アダマール行列を代入する配列を宣言

    printf("**%d**\n", smp);    // smpの値確認

    for (int i = 0; i < smp; i++) {
        for (int j = 0; j < smp; j++) {
            mul = 0;
            tmp = i & j;
            printf("%d%d , tmp = %d\n", i, j, tmp);
            for (int k = 0; tmp > 0; k++) {
                mul += tmp % 2;
                tmp /= 2;
            }
            printf("mul = %d\n", mul);
            sigY[i][j] = (int)pow(-1, mul);
            }
    }

    for (int i = 0; i < smp; i++) { // 直交基底の値確認
        printf("信号%d = ", i + 1);
        for (int j = 0; j < smp; j++) {
            printf("%d\t", sigY[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < smp; i++) { // 入力信号の値確認
        printf("%d\n", sigX[i]);
    }

    double cor[smp];    // フーリエ変換後の相関値を代入する配列

    for (int i = 0; i < smp; i++) { // 相関を求める
        cor[i] = 0;
        for (int j = 0; j < smp; j++) {
            cor[i] += sigX[j] * sigY[i][j];
        }
        cor[i] /= smp;
    }

    for (int i = 0; i < smp; i++) { // 求めた相関値を出力
        printf("%f\n", cor[i]);
    }

    return 0;
}