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
	player1.pos.y		= 480.0f - 64.0f;
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

	int yTop	= 0;		//Y座標上
	int yBottom = 0;		//	   下
	int yCenter = 0;		//　　 中央

	player1.flag = 0;
	player1.jumpFlag = 1;


	//重力加算--------------------------
	player1.jumpPow += player1.gravity;

	
	//落下スピードの上限----------------
	if (player1.jumpPow < player1.fillMax)
	{
		player1.jumpPow = -player1.fillMax;
	}


	//ジャンプ量加算--------------------
	player1.pos.y += player1.jumpPow;


	//それぞれのブロックとの判定(Box)
	//上判定----------------------------
	xRight  = (player1.pos.x + 15) / 32;
	xLeft	= (player1.pos.x - 15) / 32;
	xCenter = player1.pos.x / 32;
	yBottom = (player1.pos.y / 32);

	//調べたいチップと同じ番号であれば
	if ((mapData[yBottom][xRight]  >= 8) ||
		(mapData[yBottom][xLeft]   >= 8) ||
		(mapData[yBottom][xCenter] >= 8))
	{
		//座標補正
		player1.pos.y    = (yBottom * 32);

		player1.jumpPow  = 0.0f;
		player1.jumpFlag = 0;
	}


	//下判定-----------------------------
	xRight	 = (player1.pos.x + 15) / 32;
	xLeft	 = (player1.pos.x - 15) / 32;
	xCenter  = player1.pos.x / 32;
	yTop	 = (player1.pos.y - 54) / 32;

	if ((mapData[yTop][xRight]  >= 8) ||
		(mapData[yTop][xLeft]   >= 8) ||
		(mapData[yTop][xCenter] >= 8))
	{
		//座標補正
		player1.pos.y = (yTop + 1) * 32 + 54;

		player1.jumpPow = 3.0f;
	}


	//-------------キャラの動き------------
	//ジャンプ処理
	if (player1.jumpFlag == 0)
	{
		//上キーが押されたとき
		if (CheckHitKey(KEY_INPUT_W))
		{
			player1.jumpPow  = -player1.jumpPowMax;
			player1.jumpFlag = 1;
		}
	}

	//右移動
	if (CheckHitKey(KEY_INPUT_D))
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
	if (CheckHitKey(KEY_INPUT_A))
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

	//右移動時の判定------------------------
	if (player1.speed > 0)
	{
		xRight	= (player1.pos.x + 16) / 32;
		yTop	= (player1.pos.y - 48) / 32;
		yBottom = (player1.pos.y - 1) / 32;
		yCenter = (player1.pos.y - 24) / 32;
		
		if ((mapData[yTop][xRight]    == 8) ||
			(mapData[yBottom][xRight] == 8)  ||
			(mapData[yCenter][xRight] == 8))
		{
			//座標補正
			player1.pos.x = (xRight * 32) - 16;
			player1.speed = 0.0f;
		}
	}

	//左移動時の判定
	if (player1.speed < 0)
	{
		xLeft	= (player1.pos.x - 16) / 32;
		yTop	= (player1.pos.y - 48) / 32;
		yBottom = (player1.pos.y - 1) / 32;
		yCenter = (player1.pos.y - 24) / 32;

		if ((mapData[yTop][xLeft]    == 8) ||
			(mapData[yBottom][xLeft] == 8) ||
			(mapData[yCenter][xLeft] == 8))
		{
			//座標補正
			player1.pos.x = (xLeft + 1) * 32 + 16;
			player1.speed = 0.0f;
		}
	}

	//ショット処理
	if ((player1.shotFlag == 0) && (player1.shotCnt > 20))
	{
		if (CheckHitKey(KEY_INPUT_LCONTROL))
		{
			player1.shotPos.x = player1.pos.x;
			player1.shotPos.y = player1.pos.y - 32;

			if (player1.jumpFlag == 1) player1.shotPos.y -= 6.0f;

			//向きに合わせて移動量を代入
			player1.shotMove.x = player1.shotSpeed * player1.LRflag;

			//発射
			player1.shotFlag = 1;
			player1.shotCnt	 = 0;
		}
	}

	//ショットの移動
	if (player1.shotFlag == 1)
	{
		player1.shotPos.x += player1.shotMove.x;

		//壁に当たった際消滅
		xCenter = player1.shotPos.x / 32;
		yCenter = player1.shotPos.y / 32;
		if (mapData[yCenter][xCenter] >= 8)
		{
			player1.shotFlag = false;
		}
	}

	//相手のショットの当たり判定
	//相手のショットのあたり判定
	if ((player1.damageFlag == 0) && (player2.shotFlag == 1)) {
		HitCheckPlayerShot();
		//HItCheckPlayerVsShot(&p1, &p2);
	}
	//ダメージ中から解除する
	if (player1.damageFlag == 1) {
		player1.damageCnt++;
		if (player1.damageCnt > 20) {
			player1.damageFlag = 0;
		}
	}

	player1.pos.x += player1.speed;
}

void PlayerDraw()
{
	player1.animCnt++;
	player1.shotCnt++;

	//右移動時
	if (player1.LRflag == 1) {
		if (player1.damageFlag == 1) {
			if (player1.damageCnt < 30) {
				DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, damageImage, true);
			}
		}
		else {
			//ジャンプ
			if (player1.jumpFlag == 1) {
				if (player1.shotFlag == 1) {
					DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, jumpShotImage, true);
				}
				else {
					DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, jumpImage, true);
				}
			}
			else {
				//停止
				if (player1.flag == 0) {
					if (player1.shotFlag == 1) {
						DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, stopShotImage, true);
					}
					else {
						DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, stopImage, true);
					}
				}
				else {
					//走り
					if (player1.flag == 1) {
						if (player1.shotFlag == 1) {
							//走りの画像を表示
							DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, runShotImage[player1.animCnt / 10 % 4], true);
						}
						else {
							DrawGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, runImage[player1.animCnt / 10 % 4], true);
						}
					}
				}
			}
		}
	}

	//左移動時
	if (player1.LRflag == -1) {
		if (player1.damageFlag == 1) {
			if (player1.damageCnt < 30) {
				DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, damageImage, true);
			}
		}
		else {
			//ジャンプ
			if (player1.jumpFlag == 1) {
				if (player1.shotFlag == 1) {
					DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, jumpShotImage, true);
				}
				else {
					DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, jumpImage, true);
				}
			}
			else {
				//停止
				if (player1.flag == 0) {
					if (player1.shotFlag == 1) {
						DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, stopShotImage, true);
					}
					else {
						DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, stopImage, true);
					}
				}
				else {
					//走り
					if (player1.flag == 1) {
						if (player1.shotFlag == 1) {
							//走りの画像を表示
							DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, runShotImage[player1.animCnt / 10 % 4], true);
						}
						else {
							DrawTurnGraph(player1.pos.x - 48.0f, player1.pos.y - 64.0f, runImage[player1.animCnt / 10 % 4], true);
						}
					}
				}
			}
		}
	}
	

	//弾
	if (player1.shotFlag == 1) {
		DrawGraph(player1.shotPos.x - 8, player1.shotPos.y - 8, shot1Image, true);
	}
	
	// ﾗｲﾌ描画    
	for (int i = 0; i <player1.life; i++) {
		// 下から順番に隙間を空けながらﾗｲﾌの画像を描画する 
		DrawGraph(48, 100 - 8 * i, lifeImage, true);
	}
}