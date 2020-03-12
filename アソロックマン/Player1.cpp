#include "Action.h"

//キャラクター画像
CHARACTER player1;
int stopImage;			
int runImage[4];		
int jumpImage;			
int shotStopImage;		
int shotRunImage;		
int shotJump1Image;		
int shot1Image;			
int stopShotImage;		
int runShotImage[4];
int jumpShotImage;
int damageImage;
int lifeImage;

//リソース初期化
void PlayerImageInit()
{
	stopImage = LoadGraph("image/stop.png");
	stopShotImage = LoadGraph("image/stop_shot.png");
	jumpImage = LoadGraph("image/jump.png");
	shot1Image = LoadGraph("image/shot1.png");
	jumpShotImage = LoadGraph("image/jump_shot.png");
	damageImage = LoadGraph("image/damage.png");
	LoadDivGraph("image/run.png", 4, 4, 1, 96, 64, runImage);
	LoadDivGraph("image/run_shot.png", 4, 4, 1, 96, 64, runShotImage);
	lifeImage = LoadGraph("image/life.png");
}

//初期化
void PlayerInit()
{
	player1.flag		= 0;
	player1.pos.x		= 150.0f;
	player1.pos.y		= SCREEN_SIZE_Y - 64.0f;
	player1.move.x		= 0.0f;
	player1.move.y		= 0.0f;
	player1.LRflag		= 1;		
	player1.accel		= 0.08f;	
	player1.speed		= 0.0f;		
	player1.speedMax	= 6.0f;		
	player1.animCnt		= 0;

	player1.jumpFlag	= 0;		
	player1.gravity		= 0.30f;	
	player1.jumpPow		= 0.0f;		
	player1.jumpPowMax	= 9.0f;		
	player1.fillMax		= -20.0f;	

	player1.shotFlag	= 0.0f;
	player1.shotPos.x	= 0.0f;		
	player1.shotPos.y	= 0.0f;
	player1.shotMove.x	= 0.0f;		
	player1.shotMove.y	= 0.0f;		
	player1.shotSpeed	= 6.0f;		
	player1.shotCnt		= 30.0f;	

	player1.life = 10.0f;
}

void PlayerMain()
{
	//-----------------初期化------------------
	//当たり判定用
	int xRight	= 0;		//X座標右
	int xLeft	= 0;		//	　 左
	int xCenter = 0;		//     中央

	int yTop		= 0;		//Y座標上
	int yBottom = 0;		//	   下
	int yCenter = 0;		//　　 中央

	player1.flag = false;
	player1.jumpFlag = 1;

	//重力加算
	player1.jumpPow += player1.gravity;

	//落下スピードの上限を決める
	if (player1.jumpPow < player1.fillMax)
	{
		player1.jumpPow = -player1.fillMax;
	}

	//ジャンプ量加算
	player1.pos.y += player1.jumpPow;


	//それぞれのブロックとの判定(Box)
	//上判定
	xRight  = (player1.pos.x + 15) / 32;
	xLeft	= (player1.pos.x - 15) / 32;
	xCenter = player1.pos.x / 32;
	yBottom = player1.pos.y / 32;

	//調べたいチップと同じ番号であれば
	if ((mapData[yBottom][xRight]  >= 8) ||
		(mapData[yBottom][xLeft]   >= 8) ||
		(mapData[yBottom][xCenter] >= 8))
	{
		//プレイヤーのY座標（頭上）を補正
		player1.pos.y    = yBottom * 32;

		player1.jumpPow  = 0.0f;
		player1.jumpFlag = 0;
	}

	xRight	 = (player1.pos.x + 15) / 32;
	xLeft	 = (player1.pos.x - 15) / 32;
	xCenter  = player1.pos.x / 32;
	yTop	 = (player1.pos.y - 54) / 32;

	if ((mapData[yTop][xRight]  >= 8) ||
		(mapData[yTop][xLeft]   >= 8) ||
		(mapData[yTop][xCenter] >= 8))
	{
		//プレイヤーのY座標（頭下）補正
		player1.pos.y = (yTop + 1) * 32 + 54;

		player1.jumpPow = 3.0f;
	}


	//-------------キャラの動き--------------
	//ジャンプ処理
	if (player1.jumpFlag == 0)
	{
		//上キーが押されたとき
		if (CheckHitKey(KEY_INPUT_UP))
		{
			player1.jumpPow  = -player1.jumpPowMax;
			player1.jumpFlag = 1;
		}
	}

	//右移動
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//加速
		player1.speed += player1.accel;

		//加速量の最大値より大きくなったら
		if (player1.speed >= player1.speedMax)
		{
			player1.speed = player1.speedMax;
		}
		player1.flag	= 1;
		player1.LRflag	= 1;
	}

	//左移動
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player1.speed -= player1.accel;

		if (player1.speed <= -player1.speedMax)
		{
			player1.speed = -player1.speedMax;
		}
		player1.flag	= 1;	
		player1.LRflag  = -1;
	}

	//停止中の処理
	if (player1.flag == 0)
	{
		//右に移動したら
		if (player1.LRflag == 1)
		{
			player1.speed -= 0.2f;
			if (player1.speed < 0.0f) player1.speed = 0.0f;
		}

		//左に移動したら
		if (player1.LRflag == -1)
		{
			player1.speed += 0.2f;
			if (player1.speed > 0.0f) player1.speed = 0.0f;
		}
	}

	player1.pos.x += player1.speed;
}

void PlayerDraw()
{
	player1.animCnt++;

	//右移動時
	if (player1.LRflag == 1)
	{
		if (player1.flag == 0)
		{
			//停止状態
			DrawGraph(player1.pos.x, player1.pos.y, stopImage, true);
		}
		else
		{
			//走り状態
			DrawGraph(player1.pos.x, player1.pos.y, runImage[(player1.animCnt / 10) % 4], true);
		}
	}
	
	//左移動時
	if (player1.LRflag == -1)
	{
		if (player1.flag == 0)
		{
			//停止状態
			DrawTurnGraph(player1.pos.x, player1.pos.y, stopImage, true);
		}
		else
		{
			//走り状態
			DrawTurnGraph(player1.pos.x, player1.pos.y, runImage[(player1.animCnt / 10) % 4], true);
		}
	}
	
	
}