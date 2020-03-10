#pragma once

#include "DxLib.h"
#include <math.h>

//画面の横縦サイズ
#define SCREEN_SIZE_X 760
#define SCREEN_SIZE_Y 480

typedef struct
{
	float x;
	float y;
}XY;

//キャラクター用
typedef struct
{
	//-----------キャラ------------
	//状態フラグ
	int flag;			//停止or走る
	int LRflag;			//左右移動
	int jumpFlag;		//ジャンプ

	XY pos;				//座標
	XY move;			//移動量

	float accel;		//加速
	float speed;		//移動スピード
	float speedMax;		//最大スピード
	float gravity;		//重力
	float jumpPow;		//ジャンプ力
	float jumpPowMax;	//最大ジャンプ力
	float fillMax;		//最大落下力

	int animCnt;		//アニメーションカウント

	//-----------弾------------
	int shotFlag;		//発射フラグ

	XY shotPos;			//座標
	XY shotMove;		//移動量

	float shotSpeed;	//スピード
	int shotCnt;		


	int damageFlag;		//ダメージフラグ
	int damageCnt;		//ダメージカウント
	int life;			//HP
	XY localPos;
}CHARACTER;


//-----プロトタイプ宣言-----
void PlayerImageInit(void);
void PlayerInit(void);
void PlayerMain(void);
void PlayerDraw(void);


