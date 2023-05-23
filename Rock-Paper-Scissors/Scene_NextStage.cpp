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
Scene_NextStage::Scene_NextStage(int Next) :Next(Next), frameCount(0)
{
	nextImage[0] = LoadGraph("images/Rounds/Round1.png");
	nextImage[1] = LoadGraph("images/Rounds/Round2.png");
	nextImage[2] = LoadGraph("images/Rounds/Round3.png");
	nextImage[3] = LoadGraph("images/Rounds/Round4.png");
	nextImage[4] = LoadGraph("images/Rounds/Round5.png");
	nextImage[5] = LoadGraph("images/Rounds/Round6.png");
	nextImage[6] = LoadGraph("images/Rounds/Round7.png");
	nextImage[7] = LoadGraph("images/Rounds/Round8.png");
	nextImage[8] = LoadGraph("images/Rounds/Round9.png");
	nextImage[9] = LoadGraph("images/Rounds/Round10.png");

	next_se = LoadSoundMem("Sound/�a���ۂŃh�h��.mp3");
	PlaySoundMem(next_se, DX_PLAYTYPE_BACK);
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
}

//�`��
void Scene_NextStage::Draw() const
{
	if (Next <= 10)
	{
		DrawGraph(0, 0, nextImage[Next - 1], TRUE);
	}
}

//�V�[���̕ύX
AbstractScene* Scene_NextStage::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_B) || Next <= 10 && ++frameCount > 120)
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
			return dynamic_cast<AbstractScene*> (new Scene_Stage08());
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
			return dynamic_cast<AbstractScene*> (new Scene_Stage04());
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