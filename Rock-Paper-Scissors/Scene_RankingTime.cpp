#include "Scene_RankingTime.h"
#include "Scene_Ranking.h"
#include <DxLib.h>
#include"Scene_Title.h"
#include "KeyManager.h"
#include"SortSave.h"
#include"GameData.h"
#include "SortSaveTime.h"

int g_WaitTimeTime = 0;

Scene_RankingTime::Scene_RankingTime()
{
	backimage = LoadGraph("images/Rankingback.png");
	//BGM���[�h
	r_bgm = LoadSoundMem("Sound/Ranking.wav");
	/*for (int i = 0; i < RANKING_DATA; i++)
	{
		for (int j = 0; dataRanking[i].name[j] != '\0'; j++)
		{
			dataRanking[i].name[j] = Data->name[j];
		}
		this->dataRanking[i].score = Data[i].score;
		this->dataRanking[i].rank = Data[i].rank;
	}*/

	//�t�H���g���쐬
	ranking_font = CreateFontToHandle("���C���I", 70, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//�f�X�g���N�^
Scene_RankingTime::~Scene_RankingTime()
{
	StopSoundMem(r_bgm);
}

//�X�V
void Scene_RankingTime::Update()
{
	/*�����L���O��������*/
	//sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
	//sortSave.SortRanking();		// �����L���O���בւ�
	//sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
}

//�`��
void Scene_RankingTime::Draw() const
{
	//�w�i
	DrawGraph(0, 0, backimage, FALSE);

	DrawStringToHandle(480, 40, "�����L���O", 0xffffff, ranking_font);

	/*�����L���O�ꗗ��\��*/
	SetFontSize(30);
	for (int i = 0; i < 10; i++)
	{
	/********
	* ����  *
	********/
	/*�ʏ탂�[�h*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
		{
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d��   %10s  �������ԁF %10d��%10d�b �X�R�A�F%10d NORMAL", sortSaveTime.getRankingData(i).no, sortSaveTime.getRankingData(i).name, sortSaveTime.getRankingData(i).timeMin, sortSaveTime.getRankingData(i).timeSec, sortSaveTime.getRankingData(i).score);
		}
		/*�������[�h*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
		{
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d��   %10s �������ԁF %10d��%10d�b �X�R�A�F%10d EXTRA", sortSaveTime.getRankingData(i).no, sortSaveTime.getRankingData(i).name, sortSaveTime.getRankingData(i).timeMin, sortSaveTime.getRankingData(i).timeSec, sortSaveTime.getRankingData(i).score);
		}
	}

	SetFontSize(100);
	//�����̕\��(�_��)
	if (++g_WaitTimeTime < 30) {
		SetFontSize(30);
		DrawString(490, 670, "--  Press A �{�^��  --", 0xFF0000);
	}
	else if (g_WaitTimeTime > 60) {
		g_WaitTimeTime = 0;
	}

}

//�V�[���̕ύX����
AbstractScene* Scene_RankingTime::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)//KEY_INPUT_RETURN
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	if (KeyManager::OnPadClicked(PAD_INPUT_B) == true)//KEY_INPUT_RETURN
	{
		return dynamic_cast<AbstractScene*> (new Scene_Ranking());
	}
	return this;
}