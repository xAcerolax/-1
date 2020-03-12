#include "Action.h"

//C言語

// ========================================
// WinMain
// ========================================


typedef enum {INIT, TITLE, GAME, OVER} GAME_MODE;
GAME_MODE gameMode;

int titleImage;
int bringCnt;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText("アソロックマン");

	//システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	//画面サイズ設定
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;				//DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);

	//初期化関数
	titleImage = LoadGraph("image/title.png");
	bringCnt = 0;
	gameMode = INIT;
	MapImageInit();
	PlayerImageInit();
	Player2ImageInit();
	

	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//画面消去

		//実際の処理↓
		switch (gameMode)
		{
		case INIT:
			PlayerInit();
			Player2Init();

			MapInit();

			gameMode = TITLE;
			break;
		case TITLE:
			DrawGraph(0, 0, titleImage, true);
			bringCnt++;

			if ((bringCnt/10) % 4)
			{
				DrawString((SCREEN_SIZE_X / 2) - 48,SCREEN_SIZE_Y - 64,  "SPACE_START", 0xffffff, true);
			}

			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				gameMode = GAME;
			}
			break;
		case GAME:
			MapDraw();

			PlayerMain();
			Player2Main();

			PlayerDraw();
			Player2Draw();

			break;
		}

		ScreenFlip();		//裏画面を表画面にコピー
	}

	DxLib_End();									//DXﾗｲﾌﾞﾗﾘの終了処理

	return 0;
}

void HitCheckPlayerShot(void)
{
	if ((player1.pos.x - PLAYER_SIZE_X / 2 <= player2.shotPos.x) &&
		(player1.pos.x + PLAYER_SIZE_X / 2 >= player2.shotPos.x) && 
		(player1.pos.y - PLAYER_SIZE_Y <= player2.shotPos.y) && 
		(player1.pos.y >= player2.shotPos.y))
	{
		//当たった時の処理
		player1.damageFlag = 1;
		player1.damageCnt  = 0;
		player2.shotFlag   = 0;
		player1.life -= 1;
	}
}

void HitCheckPlayer2Shot(void)
{
	//プレイヤー2と弾1のあたり判定
	if ((player2.pos.x - PLAYER_SIZE_X / 2 <= player1.shotPos.x) && 
		(player2.pos.x + PLAYER_SIZE_X / 2 >= player1.shotPos.x) && 
		(player2.pos.y - PLAYER_SIZE_Y <= player1.shotPos.y)     && 
		(player2.pos.y >= player1.shotPos.y))
	{
		//当たった時の処理
		player2.damageFlag = 1;
		player2.damageCnt  = 0;
		player1.shotFlag   = 0;
		player2.life -= 1;

	}
	//弾1と弾2のあたり判定
	if ((player1.shotPos.x - SHOT_SIZE_X / 2 <= player2.shotPos.x)
		&& (player1.shotPos.x + SHOT_SIZE_X / 2 >= player2.shotPos.x)
		&& (player1.shotPos.y - SHOT_SIZE_Y / 2 <= player2.shotPos.y)
		&& (player1.shotPos.y + SHOT_SIZE_Y / 2 >= player2.shotPos.y))
	{
		player1.shotFlag = 0;
		player2.shotFlag = 0;
	}

}
