#include "Scene_Ranking.h"
#include <DxLib.h>
#include"Scene_Title.h"
#include "KeyManager.h"
#include"SortSave.h"
#include"GameData.h"

int g_WaitTime = 0;

Scene_Ranking::Scene_Ranking(/*const RankingData* Data*/)
{
	backimage = LoadGraph("images/Rankingback.png");
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

//�X�V
void Scene_Ranking::Update()
{
	/*�����L���O��������*/
	//sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
	//sortSave.SortRanking();		// �����L���O���בւ�
	//sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
}

//�`��
void Scene_Ranking::Draw() const
{
	//�w�i
	DrawGraph(0, 0, backimage, FALSE);
	//�����L���O�ꗗ��\��
	DrawStringToHandle(480, 40, "�����L���O", 0xffffff, ranking_font);
	SetFontSize(30);
	for (int i = 0; i < 10; i++)
	{
		/*�ʏ탂�[�h*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
		{
			//DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d��   %10s  �X�R�A�F%10d  �������ԁF %10d��%10d�b NORMAL", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, GameData::Get_Total_Time() / 3600, (GameData::Get_Total_Time() % 3600) / 60);
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d��   %10s  �X�R�A�F%10d  �������ԁF %10d��%10d�b NORMAL", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, sortSave.getRankingData(i).timeMin, sortSave.getRankingData(i).timeSec);
		}

		/*�������[�h*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
		{                                                                                                                                                                                                                                                                    
			//DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d��   %10s  �X�R�A�F%10d  �������ԁF %10d��%10d�b EXTRA", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, GameData::Get_Total_Time() / 3600, (GameData::Get_Total_Time() % 3600) / 60);
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d��   %10s  �X�R�A�F%10d  �������ԁF %10d��%10d�b EXTRA", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, sortSave.getRankingData(i).timeMin, sortSave.getRankingData(i).timeSec);
		}
	}

	SetFontSize(100);
	//�����̕\��(�_��)
	if (++g_WaitTime < 30) {
		SetFontSize(30);
		DrawString(490, 670, "--  Press A �{�^��  --", 0xFF0000);
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}

}

//�V�[���̕ύX����
AbstractScene* Scene_Ranking::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)//KEY_INPUT_RETURN
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	return this;
}