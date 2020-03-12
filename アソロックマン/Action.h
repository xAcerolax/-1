#pragma once

#include "DxLib.h"
#include <math.h>

//画面の横縦サイズ
#define SCREEN_SIZE_X 768
#define SCREEN_SIZE_Y 480

#define MAP_CHIP_X 24
#define MAP_CHIP_Y 15

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 48

#define SHOT_SIZE_X 16
#define SHOT_SIZE_Y 16

#define RIGHT_SCROLL_LINE 750	// ｽｸﾛｰﾙ開始ﾗｲﾝ(右基準)
#define LEFT_SCROLL_LINE 50	// ｽｸﾛｰﾙ開始ﾗｲﾝ(左基準)

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

//グローバル変数
extern CHARACTER player1;
extern CHARACTER player2;
extern int mapData[MAP_CHIP_Y][MAP_CHIP_X];


//-----プロトタイプ宣言-----
//マップ
void MapImageInit(void);
void MapInit(void);
void MapDraw(void);

//プレイヤー
void PlayerImageInit(void);
void PlayerInit(void);
void PlayerMain(void);
void PlayerDraw(void);

//プレイヤー2
void Player2ImageInit(void);
void Player2Init(void);
void Player2Main(void);
void Player2Draw(void);

void HitCheckPlayerShot(void);
void HitCheckPlayer2Shot(void);



