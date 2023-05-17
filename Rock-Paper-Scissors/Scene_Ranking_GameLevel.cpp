#include "Scene_Ranking_GameLevel.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include "Scene_Ranking.h"
#include"GameData.h"
#include"SoundSystem.h"

int Scene_Ranking_GameLevel::font_title = 0;

//�R���X�g���N�^
Scene_Ranking_GameLevel::Scene_Ranking_GameLevel()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//�t�H���g�f�[�^���쐬
	if (font_title == 0)
		font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	//�f�[�^�̏�����
	GameData::Init_Data();
	SetBackgroundColor(255, 255, 255);
}

//�f�X�g���N�^
Scene_Ranking_GameLevel::~Scene_Ranking_GameLevel()
{
	//�t�H���g�f�[�^���폜
	SoundSystem::StopBGM(BGM::TITLE);
	SetBackgroundColor(0, 0, 0);
}

//�X�V
void Scene_Ranking_GameLevel::Update()
{
	//SoundSystem::PlayBGM(BGM::TITLE);

	//�J�[�\�������킹�ă{�^���������ƑJ��
	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {

		//��{�^���ŏ��
		T_selectnum++;

		if (T_selectnum > 1) T_selectnum = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {

		//���{�^���ŉ���
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 1;

	}

}

//�`��
void Scene_Ranking_GameLevel::Draw() const
{


	DrawStringToHandle(70, 200, "�Q�[�����[�h�I��I��", 0xf, font_title);
	DrawStringToHandle(70, 350, "STANDARD", 0xf, font_title);
	DrawStringToHandle(70, 400, "EXTRA JANKEN", 0xf, font_title);
	DrawStringToHandle(70, 500, "B�{�^���Ŗ߂�", 0xf, font_title);

	//���j���[�J�[�\��
	DrawTriangle(40, 355 + (T_selectnum * 50), 60, 370 + (T_selectnum * 50), 40, 385 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);
}

//�V�[���̕ύX
AbstractScene* Scene_Ranking_GameLevel::ChangeScene()
{
	//A�{�^���Ō���
	 if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0:/*�ʏ탂�[�h*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::NORMAL);

			sortSave.ReadRanking();		// �����L���O�f�[�^�̓ǂݍ���
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		case 1:/*�������[�h*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::HARD);

			sortSave.ReadRanking();		// �����L���O�f�[�^�̓ǂݍ���
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		default:
			break;
		}
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	return this;  //�X�V�Ȃ�
}