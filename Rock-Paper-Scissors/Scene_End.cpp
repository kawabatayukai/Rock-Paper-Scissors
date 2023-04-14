#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_End.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
EndScene::EndScene() : framecount(0)
{

}

//�f�X�g���N�^
EndScene::~EndScene()
{
	////�G���h�摜�\��
	//DrawGraph(0, 0, g_EndImage, FALSE);

	
}

//�X�V
void EndScene::Update()
{
	//�G���f�B���O�\��
	if (++WaitTime < 900) PosY = 500 - WaitTime / 2;



	//�^�C���̉��Z�������I��
	if (++WaitTime > 900) GameState = 99;
	framecount++;
}

//�`��
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 100, "End..", 0xffffff);
	SetFontSize(24);
	DrawString(100, 170 + PosY, "�^�C�g���@�@�@JankenWorld", 0xFFFFFF);
	DrawString(100, 230 + PosY, "�ŏI�X�V���@�@201x�Nxx��xx��", 0xFFFFFF);
	DrawString(100, 260 + PosY, "����ҁ@�@�@�@���ۓd�q�r�W�l�X���w�Z", 0xFFFFFF);
	DrawString(100, 290 + PosY, "�X�e�[�W2     �o�ߌ��@��", 0xFFFFFF);
	DrawString(100, 320 + PosY, "�X�e�[�W3     �{��W���X�e�B��", 0xFFFFFF);
	DrawString(100, 350 + PosY, "�X�e�[�W4     �ʊ�  ���m", 0xFFFFFF);
	DrawString(100, 380 + PosY, "�X�e�[�W5�@   ����  ����", 0xFFFFFF);
	DrawString(100, 410 + PosY, "�X�e�[�W6     �V�_  ���", 0xFFFFFF);
	DrawString(100, 440 + PosY, "�X�e�[�W7     �씨  �E��", 0xFFFFFF);
	DrawString(100, 470 + PosY, "�X�e�[�W8     �I��  �ɐl", 0xFFFFFF);
	DrawString(100, 500 + PosY, "�X�e�[�W9     ���g  �V��", 0xFFFFFF);
	DrawString(100, 530 + PosY, "�X�e�[�W10    �o��  �F�O", 0xFFFFFF);
	DrawString(100, 565 + PosY, "�f�ޗ��p", 0xFFFFFF);
	DrawString(100, 600 + PosY, "�@BGM�@�@�@ �@�w�w�w�w", 0xFFFFFF);
	DrawString(100, 630 + PosY, "�@SE�@�@�@�@�@�w�w�w�w�w�w�w�w", 0xFFFFFF);
}

//�V�[���̕ύX
AbstractScene* EndScene::ChangeScene()
{
	if (framecount > 620)
	{
		return nullptr;
	}

	return this;  //�X�V�Ȃ�
}