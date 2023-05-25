#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"
#include"Scene_End.h"
#include"Scene_Stage01.h"
#include "Scene_Ranking.h"
#include "Scene_Help.h"
#include"GameData.h"
#include"Scene_Story.h"
#include "Scene_Title_GameLevel.h"
#include"Scene_Ranking_GameLevel.h"
#include"SortSaveTime.h"


int TitleScene::font_title;   //�t�H���g�n���h��

//�R���X�g���N�^
TitleScene::TitleScene() : frame(0), obj_death(nullptr)
{
	TitleImage = LoadGraph("images/Title/TitleNoHead.png");
	image_Eye = LoadGraph("images/Title/Eye2.png");
	image_head = LoadGraph("images/Title/Head.png");

	//�t�H���g�f�[�^���쐬
	if (font_title == 0)
		font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	//�f�[�^�̏�����
	GameData::Init_Data();
	//��Փx
	GameData::Set_DIFFICULTY(GAME_DIFFICULTY::NORMAL);

	//BGM���[�h
	bgm = LoadSoundMem("Sound/Title/titlebgm.wav");
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
	StopSoundMem(bgm);
	delete obj_death;
	
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

	if (KeyManager::OnPadClicked(PAD_INPUT_8))
	{
		if (obj_death == nullptr) obj_death = new Enemy_Death((366 + 102), (250 + 110), 99);
	}
	if (obj_death != nullptr) obj_death->Update();

	if (frame++ > 180) frame = 0;
}

//�`��
void TitleScene::Draw() const
{
	DrawGraph(0, 0, TitleImage, FALSE);

	//����łȂ�
	if (obj_death == nullptr)
	{
		//�ʏ�w�b�h
		DrawGraph(366, 250, image_head, TRUE);
		if (frame >= 170 && frame < 180) DrawGraph(384, 300, image_Eye, TRUE);
	}
	else
	{
		obj_death->Draw();
	}

	DrawStringToHandle(70, 250, "START", 0xf, font_title);
	DrawStringToHandle(70, 295, "HELP", 0xf, font_title);
	DrawStringToHandle(70, 345, "RANKING", 0xf, font_title);
	DrawStringToHandle(70, 395, "END", 0xf, font_title);

	//���j���[�J�[�\��
	DrawTriangle(40, 255 + (T_selectnum * 50), 60, 270 + (T_selectnum * 50), 40, 285 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);
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