#include "Scene_Ranking.h"
#include <DxLib.h>
#include"Scene_Title.h"
#include "KeyManager.h"
#include"SortSave.h"
#include"SortSave.h"

int g_WaitTime = 0;

Scene_Ranking::Scene_Ranking(/*const RankingData* Data*/)
{
	/*for (int i = 0; i < RANKING_DATA; i++)
	{
		for (int j = 0; dataRanking[i].name[j] != '\0'; j++)
		{
			dataRanking[i].name[j] = Data->name[j];
		}
		this->dataRanking[i].score = Data[i].score;
		this->dataRanking[i].rank = Data[i].rank;
	}*/
}

//更新
void Scene_Ranking::Update()
{

}

//描画
void Scene_Ranking::Draw() const
{
	//ランキング一覧を表示
	SetFontSize(30);
	for (int i = 0; i < 10; i++)
	{
		//DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s  %10d", dataRanking[i].rank, dataRanking[i].name, dataRanking[i].score);
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s  %10d", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score);
	}

	SetFontSize(100);
	//文字の表示(点滅)
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "--  Press A ボタン  --", 0xFF0000);
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}

}

//シーンの変更処理
AbstractScene* Scene_Ranking::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)//KEY_INPUT_RETURN
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	return this;
}