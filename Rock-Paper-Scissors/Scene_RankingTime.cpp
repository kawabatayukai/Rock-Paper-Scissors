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
	//BGMロード
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

	//フォントを作成
	ranking_font = CreateFontToHandle("メイリオ", 70, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//デストラクタ
Scene_RankingTime::~Scene_RankingTime()
{
	StopSoundMem(r_bgm);
}

//更新
void Scene_RankingTime::Update()
{
	/*ランキング内部処理*/
	//sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
	//sortSave.SortRanking();		// ランキング並べ替え
	//sortSave.SaveRanking();		// ランキングデータの保存
}

//描画
void Scene_RankingTime::Draw() const
{
	//背景
	DrawGraph(0, 0, backimage, FALSE);

	DrawStringToHandle(480, 40, "ランキング", 0xffffff, ranking_font);

	/*ランキング一覧を表示*/
	SetFontSize(30);
	for (int i = 0; i < 10; i++)
	{
	/********
	* 時間  *
	********/
	/*通常モード*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
		{
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  総合時間： %10d分%10d秒 スコア：%10d NORMAL", sortSaveTime.getRankingData(i).no, sortSaveTime.getRankingData(i).name, sortSaveTime.getRankingData(i).timeMin, sortSaveTime.getRankingData(i).timeSec, sortSaveTime.getRankingData(i).score);
		}
		/*即死モード*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
		{
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s 総合時間： %10d分%10d秒 スコア：%10d EXTRA", sortSaveTime.getRankingData(i).no, sortSaveTime.getRankingData(i).name, sortSaveTime.getRankingData(i).timeMin, sortSaveTime.getRankingData(i).timeSec, sortSaveTime.getRankingData(i).score);
		}
	}

	SetFontSize(100);
	//文字の表示(点滅)
	if (++g_WaitTimeTime < 30) {
		SetFontSize(30);
		DrawString(490, 670, "--  Press A ボタン  --", 0xFF0000);
	}
	else if (g_WaitTimeTime > 60) {
		g_WaitTimeTime = 0;
	}

}

//シーンの変更処理
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