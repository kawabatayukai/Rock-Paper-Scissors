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
	DrawString(400, 200 + PosY, "�ŏI�X�V���@�@2023�N05��26��", 0xFFFFFF);
	DrawString(550, 230 + PosY, "�f�ޗ��p", 0xFFFFFF);
	DrawString(300, 260 + PosY, "�摜  �҂ۂ�q�� https://pipoya.net/sozai/", 0xFFFFFF);
	DrawString(300, 290 + PosY, "�摜  OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(300, 320 + PosY, "�摜  illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(300, 350 + PosY, "�摜  ���炷�Ƃ� URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(300, 380 + PosY, "�摜  Unishar-���j�V���[ URL https://miyagame.net/wallpaper/", 0xFFFFFF);
	DrawString(300, 410 + PosY, "�摜  ��������ɂ�� URL http://guttari8.sakura.ne.jp/", 0xFFFFFF);
	DrawString(300, 440 + PosY, "BGM/SE�@MusMus URL https://musmus.main.jp", 0xFFFFFF);
	DrawString(300, 470 + PosY, "BGM/SE�@���ʉ����{ URL https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(300, 500 + PosY, "BGM/SE�@springin URL https://www.springin.org/", 0xFFFFFF);
	DrawString(300, 530 + PosY, "BGM/SE�@�������ʉ��ŗV�ڂ��I URL https://taira-komori.jpn.org/index.html", 0xFFFFFF);
	DrawString(300, 560 + PosY, "BGM/SE�@������ URL https://maou.audio/", 0xFFFFFF);
	DrawString(300, 590 + PosY, "BGM/SE�@�Ò��̉��y�H�[ URL https://amachamusic.chagasi.com/", 0xFFFFFF);
	DrawString(300, 620 + PosY, "BGM/SE�@�n�V�}�~ URL https://hashimamiweb.com/", 0xFFFFFF);
	DrawString(300, 650 + PosY, "BGM/SE�@FREE BGM URL https://ucchii0artist.wixsite.com/ucchii0", 0xFFFFFF);
	DrawString(300, 680 + PosY, "BGM/SE�@DOVA-SYNDROME URL https://dova-s.jp/", 0xFFFFFF);


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