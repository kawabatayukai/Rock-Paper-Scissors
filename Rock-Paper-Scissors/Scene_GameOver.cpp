#include "Scene_GameOver.h"
#include"Scene_GameMain.h"
#include"Scene_Title.h"
#include"DxLib.h"
#include"KeyManager.h"

#include"GameData.h"
#include"Scene_Stage00.h"
#include"Scene_Stage01.h"
#include"Scene_Stage02.h"
#include"Scene_Stage03.h"
#include"Scene_Stage04.h"
#include"Scene_Stage05.h"
#include"Scene_Stage06.h"
#include"Scene_Stage07.h"
#include"Scene_Stage08.h"
#include"Scene_Stage09.h"
#include"Scene_Stage10.h"
#include"Scene_Ranking.h"
#include "SortSaveTime.h"

//�R���X�g���N�^
GameOverScene::GameOverScene(int again):again(again)
{
	SetFontSize(50);
	image_back[0] = LoadGraph("images/Gameover2.png");
	image_back[1] = LoadGraph("images/GameoverHARD.png");
	gameover_se = LoadSoundMem("Sound/GameOver.mp3");

}

GameOverScene::GameOverScene() :again(11)
{
	SetFontSize(50);
	image_back[0] = LoadGraph("images/Gameover2.png");
	image_back[1] = LoadGraph("images/GameoverHARD.png");
	gameover_se = LoadSoundMem("Sound/GameOver.mp3");
}

//�f�X�g���N�^
GameOverScene::~GameOverScene()
{
	//DeleteSoundMem(gameover_se);
	StopSoundMem(gameover_se);
	SetFontSize(20);
}

//�X�V
void GameOverScene::Update()
{
	//GameOverSE
	if (CheckSoundMem(gameover_se) == 0) PlaySoundMem(gameover_se, DX_PLAYTYPE_BACK);
}

//�`��
void GameOverScene::Draw() const
{
	/*�ʏ탂�[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		//�w�i
		DrawGraph(0, 0, image_back[0], TRUE);
	}
	/*�������[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		//�w�i
		DrawGraph(0, 0, image_back[1], TRUE);
	}
}

//�V�[���̕ύX
AbstractScene* GameOverScene::ChangeScene()
{
	/*�ʏ탂�[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
	{
		//A�{�^���Ŗ߂�
		if (KeyManager::OnPadClicked(PAD_INPUT_A))
		{
			return dynamic_cast<AbstractScene*> (new TitleScene());
		}

		if (KeyManager::OnPadClicked(PAD_INPUT_B))
		{
			switch (again)
			{
			case 0:
				return dynamic_cast<AbstractScene*> (new Scene_Stage00());
				break;

			case 1:
				return dynamic_cast<AbstractScene*> (new Scene_Stage01());
				break;

			case 2:
				return dynamic_cast<AbstractScene*> (new Scene_Stage02());
				break;

			case 3:
				return dynamic_cast<AbstractScene*> (new Scene_Stage03());
				break;

			case 4:
				return dynamic_cast<AbstractScene*> (new Scene_Stage04());
				break;

			case 5:
				return dynamic_cast<AbstractScene*> (new Scene_Stage05());
				break;

			case 6:
				return dynamic_cast<AbstractScene*> (new Scene_Stage06());
				break;

			case 7:
				return dynamic_cast<AbstractScene*> (new Scene_Stage07());
				break;

			case 8:
				return dynamic_cast<AbstractScene*> (new Scene_Stage08());
				break;

			case 9:
				return dynamic_cast<AbstractScene*> (new Scene_Stage09());
				break;

			case 10:
				return dynamic_cast<AbstractScene*> (new Scene_Stage10());
				break;


			default:
				break;
			}

		}
	}

	/*�������[�h*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		if (KeyManager::OnPadClicked(PAD_INPUT_B))
		{
			/*�X�R�A��*/
			sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
			sortSave.SortRanking();		// �����L���O���בւ�
			sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�

			/*���ԏ�*/
			sortSaveTime.setTimerMin(9, 10); // �����L���O�f�[�^�̂P�O�ԖڂɎ��ԁF����o�^
			sortSaveTime.setTimerSec(9, 10); // �����L���O�f�[�^�̂P�O�ԖڂɎ��ԁF�b��o�^
			sortSaveTime.SortRanking();		// �����L���O���בւ�
			sortSaveTime.SaveRanking();		// �����L���O�f�[�^�̕ۑ�

			/*�����L���O��ʂ�*/
			return new Scene_Ranking();
		}
	}
	return this;
}
