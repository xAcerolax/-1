#include "Action.h"

//C����

// ========================================
// WinMain
// ========================================


typedef enum {INIT, TITLE, GAME, OVER} GAME_MODE;
GAME_MODE gameMode;

int titleImage;
int bringCnt;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText("�A�\���b�N�}��");

	//�V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	//��ʃT�C�Y�ݒ�
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;				//DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);

	//�������֐�
	titleImage = LoadGraph("image/title.png");
	bringCnt = 0;
	gameMode = INIT;
	MapImageInit();
	PlayerImageInit();
	Player2ImageInit();
	

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//��ʏ���

		//���ۂ̏�����
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

		ScreenFlip();		//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();									//DXײ���؂̏I������

	return 0;
}

void HitCheckPlayerShot(void)
{
	if ((player1.pos.x - PLAYER_SIZE_X / 2 <= player2.shotPos.x) &&
		(player1.pos.x + PLAYER_SIZE_X / 2 >= player2.shotPos.x) && 
		(player1.pos.y - PLAYER_SIZE_Y <= player2.shotPos.y) && 
		(player1.pos.y >= player2.shotPos.y))
	{
		//�����������̏���
		player1.damageFlag = 1;
		player1.damageCnt  = 0;
		player2.shotFlag   = 0;
		player1.life -= 1;
	}
}

void HitCheckPlayer2Shot(void)
{
	//�v���C���[2�ƒe1�̂����蔻��
	if ((player2.pos.x - PLAYER_SIZE_X / 2 <= player1.shotPos.x) && 
		(player2.pos.x + PLAYER_SIZE_X / 2 >= player1.shotPos.x) && 
		(player2.pos.y - PLAYER_SIZE_Y <= player1.shotPos.y)     && 
		(player2.pos.y >= player1.shotPos.y))
	{
		//�����������̏���
		player2.damageFlag = 1;
		player2.damageCnt  = 0;
		player1.shotFlag   = 0;
		player2.life -= 1;

	}
	//�e1�ƒe2�̂����蔻��
	if ((player1.shotPos.x - SHOT_SIZE_X / 2 <= player2.shotPos.x)
		&& (player1.shotPos.x + SHOT_SIZE_X / 2 >= player2.shotPos.x)
		&& (player1.shotPos.y - SHOT_SIZE_Y / 2 <= player2.shotPos.y)
		&& (player1.shotPos.y + SHOT_SIZE_Y / 2 >= player2.shotPos.y))
	{
		player1.shotFlag = 0;
		player2.shotFlag = 0;
	}

}
