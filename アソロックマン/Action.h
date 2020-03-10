#pragma once

#include "DxLib.h"
#include <math.h>

//��ʂ̉��c�T�C�Y
#define SCREEN_SIZE_X 760
#define SCREEN_SIZE_Y 480

typedef struct
{
	float x;
	float y;
}XY;

//�L�����N�^�[�p
typedef struct
{
	//-----------�L����------------
	//��ԃt���O
	int flag;			//��~or����
	int LRflag;			//���E�ړ�
	int jumpFlag;		//�W�����v

	XY pos;				//���W
	XY move;			//�ړ���

	float accel;		//����
	float speed;		//�ړ��X�s�[�h
	float speedMax;		//�ő�X�s�[�h
	float gravity;		//�d��
	float jumpPow;		//�W�����v��
	float jumpPowMax;	//�ő�W�����v��
	float fillMax;		//�ő嗎����

	int animCnt;		//�A�j���[�V�����J�E���g

	//-----------�e------------
	int shotFlag;		//���˃t���O

	XY shotPos;			//���W
	XY shotMove;		//�ړ���

	float shotSpeed;	//�X�s�[�h
	int shotCnt;		


	int damageFlag;		//�_���[�W�t���O
	int damageCnt;		//�_���[�W�J�E���g
	int life;			//HP
	XY localPos;
}CHARACTER;


//-----�v���g�^�C�v�錾-----
void PlayerImageInit(void);
void PlayerInit(void);
void PlayerMain(void);
void PlayerDraw(void);


