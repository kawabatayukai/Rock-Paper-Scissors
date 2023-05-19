#include"DxLib.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"
#include"Scene_End.h"
#include"Scene_Stage01.h"
#include "Scene_Ranking.h"
#include "Scene_Help.h"
#include"GameData.h"
#include"SoundSystem.h"
#include"Scene_Story.h"
#include "Scene_Title_GameLevel.h"
#include"Scene_Ranking_GameLevel.h"


int TitleScene::font_title;   //�t�H���g�n���h��

//�R���X�g���N�^
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//�t�H���g�f�[�^���쐬
	if (font_title == 0)
		font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	//�f�[�^�̏�����
	GameData::Init_Data();

	//BGM���[�h
	bgm = LoadSoundMem("Sound/TitleBGM.mp3");

}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
	StopSoundMem(bgm);
	
}

//�X�V
void TitleScene::Update()
{
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//�J�[�\�������킹�ă{�^���������ƑJ��
	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {

		//��{�^���ŏ��
		T_selectnum++;

		if (T_selectnum > 3) T_selectnum = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {

		//���{�^���ŉ���
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 3;

	}

}

//�`��
void TitleScene::Draw() const
{
	DrawGraph(0, 0, TitleImage, FALSE);

	DrawStringToHandle(70, 250, "START", 0xf, font_title);
	DrawStringToHandle(70, 295, "HELP", 0xf, font_title);
	DrawStringToHandle(70, 345, "RANKING", 0xf, font_title);
	DrawStringToHandle(70, 395, "END", 0xf, font_title);

	//���j���[�J�[�\��
	DrawTriangle(40, 255 + (T_selectnum * 50), 60, 270 + (T_selectnum * 50), 40, 285 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);

	//�f�o�b�O
	//DrawStringToHandle(10, 650, "RT + A �őI�����(�J��)", 0xf, font_title);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	// RT + A �ŃZ���N�g���
	if (KeyManager::GetValue_RT() >= 40 && KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}
	//A�{�^���Ō���
	else if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0: //�Q�[�����[�h�̑I��
			return dynamic_cast<AbstractScene*> (new Scene_Title_GameLevel());
			break;
		case 1: //�w���v���
			return dynamic_cast<AbstractScene*> (new HelpScene());
			break;
		case 2: //�����L���O���
			return dynamic_cast<AbstractScene*> (new Scene_Ranking_GameLevel());
			break;
		case 3: //�G���h���
			return dynamic_cast<AbstractScene*> (new EndScene());
			break;


		default:
			break;
		}
	}

	return this;  //�X�V�Ȃ�
}