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
	if (++WaitTime < 950) PosY = 500 - WaitTime / 2;



	//�^�C���̉��Z�������I��
	if (++WaitTime > 950) GameState = 99;
	framecount++;
}

//�`��
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(300, 100, "Thank You for Playing!!!", 0xffffff);
	SetFontSize(24);
	DrawString(450, 170 + PosY, "�^�C�g���@�@�@JankenWorld", 0xFFFFFF);
	DrawString(450, 230 + PosY, "�ŏI�X�V���@�@2023�Nxx��xx��", 0xFFFFFF);
	DrawString(450, 260 + PosY, "����ҁ@�@�@�@���ۓd�q�r�W�l�X���w�Z", 0xFFFFFF);
	DrawString(450, 290 + PosY, "�X�e�[�W2     �o�ߌ��@��", 0xFFFFFF);
	DrawString(450, 320 + PosY, "�X�e�[�W3     �{��W���X�e�B��", 0xFFFFFF);
	DrawString(450, 350 + PosY, "�X�e�[�W4     �ʊ�  ���m", 0xFFFFFF);
	DrawString(450, 380 + PosY, "�X�e�[�W5�@   ����  ����", 0xFFFFFF);
	DrawString(450, 410 + PosY, "�X�e�[�W6     �V�_  ���", 0xFFFFFF);
	DrawString(450, 440 + PosY, "�X�e�[�W7     �씨  �E��", 0xFFFFFF);
	DrawString(450, 470 + PosY, "�X�e�[�W8     �I��  �ɐl", 0xFFFFFF);
	DrawString(450, 500 + PosY, "�X�e�[�W9     ���g  �V��", 0xFFFFFF);
	DrawString(450, 530 + PosY, "�X�e�[�W10    �o��  �F�O", 0xFFFFFF);
	DrawString(450, 565 + PosY, "�f�ޗ��p", 0xFFFFFF);
	DrawString(450, 600 + PosY, "�@BGM/SE�@MusMus https://musmus.main.jp", 0xFFFFFF);
	DrawString(450, 630 + PosY, "�@BGM/SE�@���ʉ����{ https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
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