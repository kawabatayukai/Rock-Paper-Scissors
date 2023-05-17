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
	if (++WaitTime < 15000) PosY = 650 - WaitTime / 1;



	//�^�C���̉��Z�������I��
	if (++WaitTime < 10000) GameState = 99;
	framecount++;
}

//�`��
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(300, 1380 + PosY, "Thank You for Playing!!!", 0xffffff);
	SetFontSize(50);
	DrawString(350, 140 + PosY, "�^�C�g���@�@�@JankenWorld", 0xFFFFFF);
	SetFontSize(24);
	DrawString(400, 200 + PosY, "�ŏI�X�V���@�@2023�Nxx��xx��", 0xFFFFFF);
	DrawString(400, 230 + PosY, "����ҁ@�@�@�@���ۓd�q�r�W�l�X���w�Z", 0xFFFFFF);
	DrawString(250, 260 + PosY, "�X�e�[�W2,3,4,5,6 �o�ߌ� ��,�{��W���X�e�B��,�ʊ� ���m,���� ����,�V�_ ���", 0xFFFFFF);
	DrawString(250, 290 + PosY, "�X�e�[�W7,8,9,10  �씨  �E��,�I��  �ɐl,���g  �V��,�o��  �F�O", 0xFFFFFF);
	DrawString(550, 320 + PosY, "�f�ޗ��p", 0xFFFFFF);
	DrawString(300, 350 + PosY, "�摜  �҂ۂ�q�� https://pipoya.net/sozai/", 0xFFFFFF);
	DrawString(300, 380 + PosY, "�摜  OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(300, 410 + PosY, "�摜  illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(300, 440 + PosY, "�摜  ���炷�Ƃ� URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(300, 470 + PosY, "�摜  Unishar-���j�V���[ URL https://miyagame.net/wallpaper/", 0xFFFFFF);
	DrawString(300, 500 + PosY, "BGM/SE�@MusMus URL https://musmus.main.jp", 0xFFFFFF);
	DrawString(300, 530 + PosY, "BGM/SE�@���ʉ����{ URL https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(300, 565 + PosY, "BGM/SE�@springin URL https://www.springin.org/", 0xFFFFFF);
	DrawString(300, 600 + PosY, "BGM/SE�@�������ʉ��ŗV�ڂ��I URL https://taira-komori.jpn.org/index.html", 0xFFFFFF);
	DrawString(300, 630 + PosY, "BGM/SE�@������ URL https://maou.audio/", 0xFFFFFF);
	DrawString(300, 660 + PosY, "BGM/SE�@�Ò��̉��y�H�[ URL https://amachamusic.chagasi.com/", 0xFFFFFF);
	DrawString(300, 690 + PosY, "BGM/SE�@�n�V�}�~ URL https://hashimamiweb.com/", 0xFFFFFF);
	DrawString(300, 720 + PosY, "BGM/SE�@�������ʉ��ŗV�ڂ��I URL https://taira-komori.jpn.org/", 0xFFFFFF);


	//DrawFormatString(100, 600, 0xFFFFFF, "%f", framecount);
	/*DrawString(450, 630 + PosY, "  �摜    OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(450, 660 + PosY, "  �摜    illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(450, 690 + PosY, "  �摜    ���炷�Ƃ� URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(450, 720 + PosY, "�@BGM/SE�@MusMus https://musmus.main.jp", 0xFFFFFF);
	DrawString(450, 750 + PosY, "�@BGM/SE�@���ʉ����{ https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(450, 780 + PosY, "�@BGM/SE�@springin https://www.springin.org/", 0xFFFFFF);
	DrawString(450, 810 + PosY, "�@BGM/SE�@�������ʉ��ŗV�ڂ��I https://taira-komori.jpn.org/index.html", 0xFFFFFF);*/
}

//�V�[���̕ύX
AbstractScene* EndScene::ChangeScene()
{
	if (framecount > 900)
	{
		return nullptr;
	}

	return this;  //�X�V�Ȃ�
}