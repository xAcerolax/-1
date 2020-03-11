#include "Action.h"

//C����

// ========================================
// WinMain
// ========================================
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText("�A�\���b�N�}��");

	//�V�X�e������
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);	//��ʃT�C�Y�ݒ�
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;				//DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);

	//�������֐�
	MapImageInit();
	MapInit();
	PlayerImageInit();
	PlayerInit();

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//��ʏ���

		//���ۂ̏�����
		MapDraw();

		PlayerMain();
		PlayerDraw();

		ScreenFlip();		//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();									//DXײ���؂̏I������

	return 0;
}