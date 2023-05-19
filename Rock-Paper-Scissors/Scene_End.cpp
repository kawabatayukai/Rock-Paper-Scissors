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
	if (++WaitTime < 1700) PosY = 650 - WaitTime / 1;



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
	DrawString(350, 110 + PosY, "�^�C�g���@JankenWorld", 0xFFFFFF);
	SetFontSize(24);
	DrawString(400, 200 + PosY, "�ŏI�X�V���@�@2023�Nxx��xx��", 0xFFFFFF);
	DrawString(400, 230 + PosY, "����ҁ@�@�@�@���ۓd�q�r�W�l�X���w�Z", 0xFFFFFF);
	DrawString(450, 260 + PosY, "�X�e�[�W2  �o�ߌ� ��", 0xFFFFFF);
	DrawString(450, 290 + PosY, "�X�e�[�W3  �{��W���X�e�B��", 0xFFFFFF);
	DrawString(450, 320 + PosY, "�X�e�[�W4  �ʊ� ���m", 0xFFFFFF);
	DrawString(450, 350 + PosY, "�X�e�[�W5  ���� ����", 0xFFFFFF);
	DrawString(450, 380 + PosY, "�X�e�[�W6  �V�_ ���", 0xFFFFFF);
	DrawString(450, 410 + PosY, "�X�e�[�W7  �씨  �E��", 0xFFFFFF);
	DrawString(450, 440 + PosY, "�X�e�[�W8  �I��  �ɐl", 0xFFFFFF);
	DrawString(450, 470 + PosY, "�X�e�[�W9  ���g  �V��", 0xFFFFFF);
	DrawString(450, 500 + PosY, "�X�e�[�W10 �o��  �F�O", 0xFFFFFF);
	DrawString(550, 530 + PosY, "�f�ޗ��p", 0xFFFFFF);
	DrawString(300, 560 + PosY, "�摜  �҂ۂ�q�� https://pipoya.net/sozai/", 0xFFFFFF);
	DrawString(300, 590 + PosY, "�摜  OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(300, 620 + PosY, "�摜  illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(300, 650 + PosY, "�摜  ���炷�Ƃ� URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(300, 680 + PosY, "�摜  Unishar-���j�V���[ URL https://miyagame.net/wallpaper/", 0xFFFFFF);
	DrawString(300, 710 + PosY, "BGM/SE�@MusMus URL https://musmus.main.jp", 0xFFFFFF);
	DrawString(300, 740 + PosY, "BGM/SE�@���ʉ����{ URL https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(300, 770 + PosY, "BGM/SE�@springin URL https://www.springin.org/", 0xFFFFFF);
	DrawString(300, 800 + PosY, "BGM/SE�@�������ʉ��ŗV�ڂ��I URL https://taira-komori.jpn.org/index.html", 0xFFFFFF);
	DrawString(300, 830 + PosY, "BGM/SE�@������ URL https://maou.audio/", 0xFFFFFF);
	DrawString(300, 860 + PosY, "BGM/SE�@�Ò��̉��y�H�[ URL https://amachamusic.chagasi.com/", 0xFFFFFF);
	DrawString(300, 890 + PosY, "BGM/SE�@�n�V�}�~ URL https://hashimamiweb.com/", 0xFFFFFF);
	DrawString(300, 920 + PosY, "BGM/SE�@�������ʉ��ŗV�ڂ��I URL https://taira-komori.jpn.org/", 0xFFFFFF);
	DrawString(300, 950 + PosY, "BGM/SE�@FREE BGM URL https://ucchii0artist.wixsite.com/ucchii0", 0xFFFFFF);
	DrawString(300, 980 + PosY, "BGM/SE�@DOVA-SYNDROME URL https://dova-s.jp/", 0xFFFFFF);


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