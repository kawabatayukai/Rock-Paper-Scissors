#include "Scene_NextStage.h"
#include"DxLib.h"
#include"KeyManager.h"

#include"Scene_GameMain.h"
#include"Scene_Title.h"

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

#include"Scene_End.h"
#include"Scene_Help.h"
#include"SortSave.h"
#include"GameData.h"
#include"SortSave.h"
#include"Scene_Ranking.h"
#include "SortSaveTime.h"


//�R���X�g���N�^
Scene_NextStage::Scene_NextStage(int Next) :Next(Next)
{
	nextImage[0] = LoadGraph("images/GameClear2.png");
	nextImage[1] = LoadGraph("images/GameClear2.png");
	nextImage[2] = LoadGraph("images/GameClear2.png");
	nextImage[3] = LoadGraph("images/GameClear2.png");
	nextImage[4] = LoadGraph("images/GameClear2.png");
	nextImage[5] = LoadGraph("images/GameClear2.png");
	nextImage[6] = LoadGraph("images/GameClear2.png");
	nextImage[7] = LoadGraph("images/GameClear2.png");
	nextImage[8] = LoadGraph("images/GameClear2.png");
	nextImage[9] = LoadGraph("images/GameClear2.png");

	next_se = LoadSoundMem("Sound/�a���ۂŃh�h��.mp3");
}

//�f�X�g���N�^
Scene_NextStage::~Scene_NextStage()
{
	StopSoundMem(next_se);
	SetFontSize(20);
}

//�X�V
void Scene_NextStage::Update()
{
	//clear_se
	if (CheckSoundMem(next_se) == 0) PlaySoundMem(next_se, DX_PLAYTYPE_BACK);
}

//�`��
void Scene_NextStage::Draw() const
{
	switch (Next)
	{
	case 1:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 2:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 3:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 4:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 5:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 6:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 7:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 8:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 9:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 10:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 11:
		//�w�i
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;
	}

}

//�V�[���̕ύX
AbstractScene* Scene_NextStage::ChangeScene()
{
	//A�{�^���Ŗ߂�
	/*if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}*/
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		switch (Next)
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

		case 11:/*�����L���O��������*/

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
			break;

		default:
			break;
		}

	}
	return this;
}