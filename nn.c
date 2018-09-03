
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//定数の定義
#define INPUTNO 2   //入力層セル数
#define HIDDENNO 2  //中間層セル数
#define MAXINPUTNO 100 //データの最大個数

//関数のプロトタイプ宣言
double f(double u);
void initwh(double wh[HIDDENNO][INPUTNO+1]);
void initwo(double wo[HIDDENNO+1]);
double forward( double wh[HIDDENNO][INPUTNO + 1]
			,double wo[HIDDENNO+1],double hi[]
			,double e[INPUTNO]);
int getdata(double e[][INPUTNO]);

//ここからスタートでーす
int main()
{
    double wh[HIDDENNO][INPUTNO+1];  //中間層の重み
    double wo[HIDDENNO+1];           //出力層の重み
    double e[MAXINPUTNO][INPUTNO];    //データセット
    double hi[HIDDENNO + 1];          //中間層の出力
    double o ;                         // 出力
    int i,j;                          //繰り返し制御
    int n_of_e;                       //データ個数

    //重みの初期化
    initwh(wh);
    initwo(wo);

    //入力データ読みこみ
    n_of_e = getdata(e);
    printf("データの個数:%d\n", n_of_e );

    //計算本体
    for(i=0; i<n_of_e; ++i){
      printf("%d ", i);
      for(j=0; j<INPUTNO; ++j)
        printf("%lf ", e[i][j] );
      o=forward(wh, wo, hi, e[i]);
      printf("%lf\n", o);
    }

    return 0;
}


//学習データ読み込み
int getdata( double e[][INPUTNO] ){
  int n_of_e = 0; //学習データセットの個数
  int j = 0;

  while (scanf("%lf", &e[n_of_e][j]) != EOF) {
    ++j;
    if( j>= INPUTNO){
      j=0;
      ++n_of_e;
    }
  }
  return n_of_e;
}


//forward関数
double forward(double wh[HIDDENNO][INPUTNO+1],
               double wo[HIDDENNO+1],
               double hi[],
               double e[INPUTNO])
{
  int i, j;    //繰り返し制御
  double u;    //重み付き和の計算
  double o;    //出力計算

  //hi計算
  for(i = 0; i<HIDDENNO ; ++i){
      u = 0; //重み付き和を求める
      for(j=0; j<INPUTNO; ++j){
        u += e[j] * wh[i][j];
      }
      u-=wh[i][j];  //しきい値の処理
      hi[i] = f(u);
  }

  //出力o計算
  o = 0;
  for(i=0; i<HIDDENNO; ++i)
    o += hi[i] * wo[i];
  o -= wo[i];//しきい値の処理

  // printf("==しきい値後====>%lf\n ", o );

  return f(o);
}

//中間層の重みの初期化
void initwh(double wh[HIDDENNO][INPUTNO + 1])
{
  //荷重を定数として与える
  wh[0][0] = -2;
  wh[0][1] = 3;
  wh[0][2] = -1;
  wh[1][0] = -2;
  wh[1][1] = 1;
  wh[1][2] = 0.5;
}

//出力層重みの初期化
void initwo(double wo[HIDDENNO + 1]){
  //荷重を定数として与える
  wo[0] = -60;
  wo[1] = 94;
  wo[2] = -1;
}


//伝搬関数
double f(double u){
  //ステップ関数
  if( u>=0 ){
    return 1.0;
  }else{
    return 0.0;
  }

  //シグモイド関数
  // return 1.0/(1.0+exp(-u))

}
