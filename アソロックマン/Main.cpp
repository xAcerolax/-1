#include "Action.h"

//C言語

// ========================================
// WinMain
// ========================================
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText("アソロックマン");

	//システム処理
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	//画面サイズ設定
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;				//DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);

	//初期化関数
	MapImageInit();
	MapInit();
	PlayerImageInit();
	PlayerInit();

	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//画面消去

		//実際の処理↓
		MapDraw();

		PlayerMain();
		PlayerDraw();

		ScreenFlip();		//裏画面を表画面にコピー
	}

	DxLib_End();									//DXﾗｲﾌﾞﾗﾘの終了処理

	return 0;
}