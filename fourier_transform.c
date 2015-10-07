#include <stdio.h>

int main() {

    int sigX[100] = {0};        // 入力信号
    int smp = 0;                // 入力信号のサンプリング数
    int count = 1;              // sigYの信号を作成する際の波形が0になった回数をカウント
    int sigInd;                 // sigYの1サンプルごとの信号
    int point = 1;              // sigYの信号波形の0になる位置を決定させる
    int sinSwitch = 0;          // sin波形を扱うときに値を1にする
    double checkPoint;          // 波形と時間軸との交点
    double quarterCycle = 1;    // 4分の1周期の長さ


    // フーリエ変換する信号を入力
    printf("信号を入力（10000以上を入力して入力終了）\n");
    for (int i = 0; sigX[smp] < 10000; i++, smp = i - 1) {
        printf("> ");
        scanf("%d", &sigX[i]);
    }

    int sigY[smp][smp];

    printf("**%d**\n", smp);    // smpの値確認

    // 直交基底の作成
    for (int i = 0; i < smp; i++) {
        checkPoint = (double)smp / (4 * (double)count);
        quarterCycle = checkPoint;
        sigInd = 1;
        for (int j = 0; j < smp; j++) {
            if (sigInd == 0 && sigY[i][j-2] == 1) {
                sigInd = 1;
            } else if (sigInd == 0 && sigY[i][j-2] == -1) {
                sigInd = -1;
            }
            if (i == smp - 1 && j == 0) {
                sinSwitch = 1;
            }

            if (i == 0) {   // 直流成分
                sigInd = 1;
            } else if (j + 0.5 == checkPoint + quarterCycle * sinSwitch) {
                printf("#0\n");
                sigInd = 0;
            } else if (j + 0.5 > checkPoint + quarterCycle * sinSwitch) {
                printf("#-1\n");
                checkPoint += 2 * quarterCycle; // checkPointの値を超えたら半周期進める
                sigInd *= -1;
            }
            sigY[i][j] = sigInd;    // 直交基底を配列に代入
        }
        if (i % 2 == 0 && i != 0) { // 周波数を1つ高くする，cos波形を扱うようにする
            count++;
            sinSwitch = 0;
        } else if (i % 2 == 1) {    // sin波形を扱うようにする
            sinSwitch = 1;
        }
    }


    for (int i = 0; i < smp; i++) { // 直交基底の値確認
        for (int j = 0; j < smp; j++) {
            printf("*%d\n", sigY[i][j]);
        }
        printf("--\n");
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