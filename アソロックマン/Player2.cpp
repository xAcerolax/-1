#include "Action.h"

//キャラクター画像
CHARACTER player2;
int stop2Image;
int run2Image[4];
int jump2Image;
int shotStop2Image;
int shotRun2Image;
int shotJump2Image;
int shot2Image;
int stopShot2Image;
int runShot2Image[4];
int jumpShot2Image;
int damage2Image;
int life2Image;

//リソース初期化
void Player2ImageInit()
{
	stop2Image = LoadGraph("image/stop2.png");
	stopShot2Image = LoadGraph("image/stop_shot2.png");
	jump2Image = LoadGraph("image/jump2.png");
	shot2Image = LoadGraph("image/shot2.png");
	jumpShot2Image = LoadGraph("image/jump_shot2.png");
	damage2Image = LoadGraph("image/damage2.png");
	LoadDivGraph("image/run2.png", 4, 4, 1, 96, 64, run2Image);
	LoadDivGraph("image/run_shot2.png", 4, 4, 1, 96, 64, runShot2Image);
	life2Image = LoadGraph("image/life.png");
}

//初期化
void Player2Init()
{
	player2.flag = 0;
	player2.pos.x = 650.0f;
	player2.pos.y = 480.0f - 64.0f;
	player2.move.x = 0.0f;
	player2.move.y = 0.0f;
	player2.LRflag = -1;
	player2.accel = 0.08f;
	player2.speed = 0.0f;
	player2.speedMax = 6.0f;
	player2.animCnt = 0;

	player2.jumpFlag = 0;
	player2.gravity = 0.30f;
	player2.jumpPow = 0.0f;
	player2.jumpPowMax = 9.0f;
	player2.fillMax = -20.0f;

	player2.shotFlag = 0.0f;
	player2.shotPos.x = 0.0f;
	player2.shotPos.y = 0.0f;
	player2.shotMove.x = 0.0f;
	player2.shotMove.y = 0.0f;
	player2.shotSpeed = 6.0f;
	player2.shotCnt = 30.0f;

	player2.life = 10.0f;
}

void Player2Main()
{
	//-----------------初期化------------------
	//当たり判定用
	int xRight = 0;		//X座標右
	int xLeft = 0;		//	　 左
	int xCenter = 0;		//     中央

	int yTop = 0;		//Y座標上
	int yBottom = 0;		//	   下
	int yCenter = 0;		//　　 中央

	player2.flag = 0;
	player2.jumpFlag = 1;


	//重力加算--------------------------
	player2.jumpPow += player2.gravity;


	//落下スピードの上限----------------
	if (player2.jumpPow < player2.fillMax)
	{
		player2.jumpPow = -player2.fillMax;
	}


	//ジャンプ量加算--------------------
	player2.pos.y += player2.jumpPow;


	//それぞれのブロックとの判定(Box)
	//上判定----------------------------
	xRight  = (player2.pos.x + 15) / 32;
	xLeft   = (player2.pos.x - 15) / 32;
	xCenter = player2.pos.x / 32;
	yBottom = (player2.pos.y / 32);

	//調べたいチップと同じ番号であれば
	if ((mapData[yBottom][xRight]  >= 8) ||
		(mapData[yBottom][xLeft]   >= 8) ||
		(mapData[yBottom][xCenter] >= 8))
	{
		//座標補正
		player2.pos.y    = (yBottom * 32);

		player2.jumpPow  = 0.0f;
		player2.jumpFlag = 0;
	}


	//下判定-----------------------------
	xRight  = (player2.pos.x + 15) / 32;
	xLeft   = (player2.pos.x - 15) / 32;
	xCenter = player2.pos.x / 32;
	yTop    = (player2.pos.y - 54) / 32;

	if ((mapData[yTop][xRight]  >= 8) ||
		(mapData[yTop][xLeft]   >= 8) ||
		(mapData[yTop][xCenter] >= 8))
	{
		//座標補正
		player2.pos.y = (yTop + 1) * 32 + 54;

		player2.jumpPow = 3.0f;
	}


	//-------------キャラの動き------------
	//ジャンプ処理
	if (player2.jumpFlag == 0)
	{
		//上キーが押されたとき
		if (CheckHitKey(KEY_INPUT_UP))
		{
			player2.jumpPow = -player2.jumpPowMax;
			player2.jumpFlag = 1;
		}
	}

	//右移動
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//加速
		player2.speed += player2.accel;

		//加速量の最大値より大きくなったら
		if (player2.speed >= player2.speedMax)
		{
			player2.speed = player2.speedMax;
		}
		player2.flag = 1;
		player2.LRflag = 1;
	}

	//左移動
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		player2.speed -= player2.accel;

		if (player2.speed <= -player2.speedMax)
		{
			player2.speed = -player2.speedMax;
		}
		player2.flag   = 1;
		player2.LRflag = -1;
	}

	//停止中の処理
	if (player2.flag == 0)
	{
		//右に移動したら
		if (player2.LRflag == 1)
		{
			player2.speed -= 0.2f;
			if (player2.speed < 0.0f) player2.speed = 0.0f;
		}

		//左に移動したら
		if (player2.LRflag == -1)
		{
			player2.speed += 0.2f;
			if (player2.speed > 0.0f) player2.speed = 0.0f;
		}
	}

	//右移動時の判定------------------------
	if (player2.speed > 0)
	{
		xRight  = (player2.pos.x + 16) / 32;
		yTop    = (player2.pos.y - 48) / 32;
		yBottom = (player2.pos.y - 1) / 32;
		yCenter = (player2.pos.y - 24) / 32;

		if ((mapData[yTop][xRight]    == 8) ||
			(mapData[yBottom][xRight] == 8) ||
			(mapData[yCenter][xRight] == 8))
		{
			//座標補正
			player2.pos.x = (xRight * 32) - 16;
			player2.speed = 0.0f;
		}
	}

	//左移動時の判定
	if (player2.speed < 0)
	{
		xLeft   = (player2.pos.x - 16) / 32;
		yTop    = (player2.pos.y - 48) / 32;
		yBottom = (player2.pos.y - 1) / 32;
		yCenter = (player2.pos.y - 24) / 32;

		if ((mapData[yTop][xLeft]    == 8) ||
			(mapData[yBottom][xLeft] == 8) ||
			(mapData[yCenter][xLeft] == 8))
		{
			//座標補正
			player2.pos.x = (xLeft + 1) * 32 + 16;
			player2.speed = 0.0f;
		}
	}

	//ショット処理
	if ((player2.shotFlag == 0) && (player2.shotCnt > 20))
	{
		if (CheckHitKey(KEY_INPUT_RCONTROL))
		{
			player2.shotPos.x = player2.pos.x;
			player2.shotPos.y = player2.pos.y - 32;

			if (player2.jumpFlag == 1) player2.shotPos.y -= 6.0f;

			//向きに合わせて移動量を代入
			player2.shotMove.x = player2.shotSpeed * player2.LRflag;

			//発射
			player2.shotFlag = 1;
			player2.shotCnt = 0;
		}
	}

	//ショットの移動
	if (player2.shotFlag == 1)
	{
		player2.shotPos.x += player2.shotMove.x;

		//壁に当たった際消滅
		xCenter = player2.shotPos.x / 32;
		yCenter = player2.shotPos.y / 32;
		if (mapData[yCenter][xCenter] >= 8)
		{
			player2.shotFlag = false;
		}
	}

	//相手のショットの当たり判定
	//相手のショットのあたり判定
	if ((player2.damageFlag == 0) && (player2.shotFlag == 1)) {
		HitCheckPlayer2Shot();
		//HItCheckPlayerVsShot(&p1, &p2);
	}
	//ダメージ中から解除する
	if (player2.damageFlag == 1) {
		player2.damageCnt++;
		if (player2.damageCnt > 20) {
			player2.damageFlag = 0;
		}
	}

	player2.pos.x += player2.speed;
}

void Player2Draw()
{
	player2.animCnt++;
	player2.shotCnt++;

	//右移動時
	if (player2.LRflag == 1) {
		if (player2.damageFlag == 1) {
			if (player2.damageCnt < 30) {
				DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, damage2Image, true);
			}
		}
		else {
			//ジャンプ
			if (player2.jumpFlag == 1) {
				if (player2.shotFlag == 1) {
					DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, jumpShot2Image, true);
				}
				else {
					DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, jump2Image, true);
				}
			}
			else {
				//停止
				if (player2.flag == 0) {
					if (player2.shotFlag == 1) {
						DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, stopShot2Image, true);
					}
					else {
						DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, stop2Image, true);
					}
				}
				else {
					//走り
					if (player2.flag == 1) {
						if (player2.shotFlag == 1) {
							//走りの画像を表示
							DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, runShot2Image[player2.animCnt / 10 % 4], true);
						}
						else {
							DrawGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, run2Image[player2.animCnt / 10 % 4], true);
						}
					}
				}
			}
		}
	}

	//左移動時
	if (player2.LRflag == -1) {
		if (player2.damageFlag == 1) {
			if (player2.damageCnt < 30) {
				DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, damage2Image, true);
			}
		}
		else {
			//ジャンプ
			if (player2.jumpFlag == 1) {
				if (player2.shotFlag == 1) {
					DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, jumpShot2Image, true);
				}
				else {
					DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, jump2Image, true);
				}
			}
			else {
				//停止
				if (player2.flag == 0) {
					if (player2.shotFlag == 1) {
						DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, stopShot2Image, true);
					}
					else {
						DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, stop2Image, true);
					}
				}
				else {
					//走り
					if (player2.flag == 1) {
						if (player2.shotFlag == 1) {
							//走りの画像を表示
							DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, runShot2Image[player2.animCnt / 10 % 4], true);
						}
						else {
							DrawTurnGraph(player2.pos.x - 48.0f, player2.pos.y - 64.0f, run2Image[player2.animCnt / 10 % 4], true);
						}
					}
				}
			}
		}
	}


	//弾
	if (player2.shotFlag == 1) {
		DrawGraph(player2.shotPos.x - 8, player2.shotPos.y - 8, shot2Image, true);
	}

	// ﾗｲﾌ描画    
	for (int i = 0; i <player2.life; i++) {
		// 下から順番に隙間を空けながらﾗｲﾌの画像を描画する 
		DrawGraph(702, 100 - 8 * i, life2Image, true);
	}
}

