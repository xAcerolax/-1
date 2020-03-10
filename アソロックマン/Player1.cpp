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
	player1.pos.x		= 0;
	player1.pos.y		= 0;
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
	//当たり判定用
	int xRight = 0;
	int xLeft = 0;
	int xCenter = 0;
	int yUp = 0;
	int yBottom = 0;
	int yCenter = 0;

	player1.flag = false;
	player1.jumpFlag = false;



}

void PlayerDraw()
{
	DrawGraph(player1.pos.x + 48.0f, player1.pos.y + 64.0f, damageImage, true);
}