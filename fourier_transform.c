#include <stdio.h>
#include <math.h>

int main() {

    double sigX[100] = {0}; // 入力信号
    int smp = 0;            // 入力信号のサンプリング数
    int mul = 0;            // 乗数
    int tmp1;               // アダマール行列作成時の途中計算（行列数の決定）
    int tmp2;               // アダマール行列作成時の途中計算（論理積）


    printf("信号を入力（10000以上を入力して入力終了）\n");    // フーリエ変換する信号を入力
    for (int i = 0; sigX[smp] < 10000; i++, smp = i - 1) {
        printf("> ");
        scanf("%lf", &sigX[i]);
    }
    sigX[smp] = 0;  // 最後に入力された10000以上の値を削除


    for (int i = 0; tmp1 < smp; i++) {  // アダマール行列の行数・列数を決定（n = 2^m）
        tmp1 = (int)pow(2, i);
    }
    smp = tmp1;


    int sigY[smp][smp]; // アダマール行列を代入する配列
    double cor[smp];    // フーリエ変換後の相関値を代入する配列


    for (int i = 0; i < smp; i++) { // アダマール行列の作成
        for (int j = 0; j < smp; j++) {
            mul = 0;
            tmp2 = i & j;
            for (int k = 0; tmp2 > 0; k++) {
                mul += tmp2 % 2;
                tmp2 /= 2;
            }
            sigY[i][j] = (int)pow(-1, mul);
            }
    }


    for (int i = 0; i < smp; i++) { // 相関を求める
        cor[i] = 0;
        for (int j = 0; j < smp; j++) {
            cor[i] += sigX[j] * sigY[i][j];
        }
        cor[i] /= smp;
    }


    printf("\n==入力信号==\n");
    for (int i = 0; i < smp; i++) {
        printf("%9f\n", sigX[i]);
    }

    printf("\n==アダマール行列==\n");
    for (int i = 0; i < smp; i++) {
        printf("信号%2d = ", i + 1);
        for (int j = 0; j < smp; j++) {
            printf("%2d\t", sigY[i][j]);
        }
        printf("\n");
    }

    printf("\n==相関値==\n");
    for (int i = 0; i < smp; i++) {
        printf("%9f\n", cor[i]);
    }

    return 0;
}