#include "Action.h"

//�L�����N�^�[�摜
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

//���\�[�X������
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

//������
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
	//-----------------������------------------
	//�����蔻��p
	int xRight	= 0;		//X���W�E
	int xLeft	= 0;		//	�@ ��
	int xCenter = 0;		//     ����

	int yTop		= 0;		//Y���W��
	int yBottom = 0;		//	   ��
	int yCenter = 0;		//�@�@ ����

	player1.flag = false;
	player1.jumpFlag = 1;

	//�d�͉��Z
	player1.jumpPow += player1.gravity;

	//�����X�s�[�h�̏�������߂�
	if (player1.jumpPow < player1.fillMax)
	{
		player1.jumpPow = -player1.fillMax;
	}

	//�W�����v�ʉ��Z
	player1.pos.y += player1.jumpPow;


	//���ꂼ��̃u���b�N�Ƃ̔���(Box)
	//�㔻��
	xRight  = (player1.pos.x + 15) / 32;
	xLeft	= (player1.pos.x - 15) / 32;
	xCenter = player1.pos.x / 32;
	yBottom = player1.pos.y / 32;

	//���ׂ����`�b�v�Ɠ����ԍ��ł����
	if ((mapData[yBottom][xRight]  >= 8) ||
		(mapData[yBottom][xLeft]   >= 8) ||
		(mapData[yBottom][xCenter] >= 8))
	{
		//�v���C���[��Y���W�i����j��␳
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
		//�v���C���[��Y���W�i�����j�␳
		player1.pos.y = (yTop + 1) * 32 + 54;

		player1.jumpPow = 3.0f;
	}


	//-------------�L�����̓���--------------
	//�W�����v����
	if (player1.jumpFlag == 0)
	{
		//��L�[�������ꂽ�Ƃ�
		if (CheckHitKey(KEY_INPUT_UP))
		{
			player1.jumpPow  = -player1.jumpPowMax;
			player1.jumpFlag = 1;
		}
	}

	//�E�ړ�
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		//����
		player1.speed += player1.accel;

		//�����ʂ̍ő�l���傫���Ȃ�����
		if (player1.speed >= player1.speedMax)
		{
			player1.speed = player1.speedMax;
		}
		player1.flag	= 1;
		player1.LRflag	= 1;
	}

	//���ړ�
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

	//��~���̏���
	if (player1.flag == 0)
	{
		//�E�Ɉړ�������
		if (player1.LRflag == 1)
		{
			player1.speed -= 0.2f;
			if (player1.speed < 0.0f) player1.speed = 0.0f;
		}

		//���Ɉړ�������
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

	//�E�ړ���
	if (player1.LRflag == 1)
	{
		if (player1.flag == 0)
		{
			//��~���
			DrawGraph(player1.pos.x, player1.pos.y, stopImage, true);
		}
		else
		{
			//������
			DrawGraph(player1.pos.x, player1.pos.y, runImage[(player1.animCnt / 10) % 4], true);
		}
	}
	
	//���ړ���
	if (player1.LRflag == -1)
	{
		if (player1.flag == 0)
		{
			//��~���
			DrawTurnGraph(player1.pos.x, player1.pos.y, stopImage, true);
		}
		else
		{
			//������
			DrawTurnGraph(player1.pos.x, player1.pos.y, runImage[(player1.animCnt / 10) % 4], true);
		}
	}
	
	
}