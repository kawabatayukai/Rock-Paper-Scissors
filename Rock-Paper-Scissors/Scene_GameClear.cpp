#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
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
#include"Scene_NextStage.h"

//�R���X�g���N�^
GameClearScene::GameClearScene(int Next):Next(Next)
{
	clearImage = LoadGraph("images/GameClear2.png");
	clear_se = LoadSoundMem("Sound/GameClear.mp3");
}

//�f�X�g���N�^
GameClearScene::~GameClearScene()
{
	StopSoundMem(clear_se);
	SetFontSize(20);
}

//�X�V
void GameClearScene::Update()
{
	//clear_se
	if (CheckSoundMem(clear_se) == 0) PlaySoundMem(clear_se, DX_PLAYTYPE_BACK);
}

//�`��
void GameClearScene::Draw() const
{
	//�w�i
	DrawGraph(0, 0, clearImage, TRUE);

	SetFontSize(50);
	DrawFormatString(200,500, 0x000000,"�X�R�A�F%d �E �c�莞�ԁF%d��%d�b", GameData::Get_Score(), GameData::Get_Each_Time_Min(), GameData::Get_Each_Time_Sec());
	SetFontSize(20);

	/*SetFontSize(200);
	DrawString(200, 100, "StageClear", 0xffffff);

	SetFontSize(50);
	DrawString(450, 425, "B", GetColor(255, 0, 0));
	DrawString(500, 425, "NextStage...", 0xffffff);
	DrawString(450, 525, "A", GetColor(0, 255, 0));
	DrawString(500, 525, "Title", 0xffffff);*/
}

//�V�[���̕ύX
AbstractScene* GameClearScene::ChangeScene()
{
	//A�{�^���Ŗ߂�
	/*if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}*/
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		//switch (Next)
		//{
		//case 0:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage00());
		//	break;
		//case 1:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage01());
		//	break;
		//case 2:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage02());
		//	break;
		//case 3:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage03());
		//	break;
		//case 4:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage04());
		//	break;
		//case 5:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage05());
		//	break;
		//case 6:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage06());
		//	break;
		//case 7:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage07());
		//	break;
		//case 8:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage08());
		//	break;
		//case 9:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage09());
		//	break;
		//case 10:
		//	return dynamic_cast<AbstractScene*> (new Scene_Stage10());
		//	break;
		//case 11:/*�����L���O��������*/
		//	/*�X�R�A��*/
		//	sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
		//	sortSave.SortRanking();		// �����L���O���בւ�
		//	sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
		//	/*���ԏ�*/
		//	sortSaveTime.setTimerMin(9, 10); // �����L���O�f�[�^�̂P�O�ԖڂɎ��ԁF����o�^
		//	sortSaveTime.setTimerSec(9, 10); // �����L���O�f�[�^�̂P�O�ԖڂɎ��ԁF�b��o�^
		//	sortSaveTime.SortRanking();		// �����L���O���בւ�
		//	sortSaveTime.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
		//	/*�����L���O��ʂ�*/
		//	return new Scene_Ranking();
		//	break;
		//default:
		//	break;
		//}
		
		return dynamic_cast<AbstractScene*> (new Scene_NextStage(Next));
	}
	return this;
}
