#include "Scene_Ranking.h"
#include"Scene_InputRanking.h"
#include <DxLib.h>
#include"Scene_Title.h"
#include "KeyManager.h"
<<<<<<< HEAD
=======
#include"SortSave.h"
#include"Scene_InputRanking.h"
>>>>>>> parent of bfaa0a9 (ランキング処理の変更追加)

int g_WaitTime = 0;

//�X�V
void Scene_Ranking::Update()
{

}

//�`��
void Scene_Ranking::Draw() const
{
	//�����L���O�ꗗ��\��
	SetFontSize(30);
	for (int i = 0; i < 10; i++)
	{
<<<<<<< HEAD
=======
		//DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s  %10d", dataRanking[i].rank, dataRanking[i].name, dataRanking[i].score);
>>>>>>> parent of bfaa0a9 (ランキング処理の変更追加)
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s  %10d", inputRanking.getRankingData(i).no, inputRanking.getRankingData(i).name, inputRanking.getRankingData(i).score);
	}

	SetFontSize(100);
	//�����̕\��(�_��)
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "--  Press A �{�^��  --", 0xFF0000);
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