#include "Scene_Ranking.h"
#include "Scene_RankingTime.h"
#include <DxLib.h>
#include"Scene_Title.h"
#include "KeyManager.h"
#include"SortSave.h"
#include"GameData.h"

int g_WaitTime = 0;

Scene_Ranking::Scene_Ranking(/*const RankingData* Data*/)
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
Scene_Ranking::~Scene_Ranking()
{
	StopSoundMem(r_bgm);
}


//更新
void Scene_Ranking::Update()
{
	//rankingBGM
	if (CheckSoundMem(r_bgm) == 0) PlaySoundMem(r_bgm, DX_PLAYTYPE_LOOP);

	/*ランキング内部処理*/
	//sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
	//sortSave.SortRanking();		// ランキング並べ替え
	//sortSave.SaveRanking();		// ランキングデータの保存
}

//描画
void Scene_Ranking::Draw() const
{
	//背景
	DrawGraph(0, 0, backimage, FALSE);

	DrawStringToHandle(480, 40, "ランキング", 0xffffff, ranking_font);

	/*ランキング一覧を表示*/
	SetFontSize(30);

	DrawString(1000, 50, "B：時間順", 0xffffff);

	for (int i = 0; i < 10; i++)
	{
	/*********
	* スコア *
	*********/
		/*通常モード*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
		{
			//DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  スコア：%10d  総合時間： %10d分%10d秒 NORMAL", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, GameData::Get_Total_Time() / 3600, (GameData::Get_Total_Time() % 3600) / 60);
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  スコア：%10d  総合時間： %10d分%10d秒 NORMAL", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, sortSave.getRankingData(i).timeMin, sortSave.getRankingData(i).timeSec);
		}
		/*即死モード*/
		if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
		{
			//DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  スコア：%10d  総合時間： %10d分%10d秒 EXTRA", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, GameData::Get_Total_Time() / 3600, (GameData::Get_Total_Time() % 3600) / 60);
			DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  スコア：%10d  総合時間： %10d分%10d秒 EXTRA", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, sortSave.getRankingData(i).timeMin, sortSave.getRankingData(i).timeSec);
		}

	/********
	* 時間  *
	********/
		///*通常モード*/
		//if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NORMAL)
		//{
		//	//DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  スコア：%10d  総合時間： %10d分%10d秒 NORMAL", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, GameData::Get_Total_Time() / 3600, (GameData::Get_Total_Time() % 3600) / 60);
		//	DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  総合時間： %10d分%10d秒 スコア：%10d NORMAL", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).timeMin, sortSave.getRankingData(i).timeSec, sortSave.getRankingData(i).score);
		//}
		///*即死モード*/
		//if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
		//{
		//	//DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s  スコア：%10d  総合時間： %10d分%10d秒 EXTRA", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).score, GameData::Get_Total_Time() / 3600, (GameData::Get_Total_Time() % 3600) / 60);
		//	DrawFormatString(0, 170 + i * 50, 0xFFFFFF, "%2d位   %10s 総合時間： %10d分%10d秒 スコア：%10d EXTRA", sortSave.getRankingData(i).no, sortSave.getRankingData(i).name, sortSave.getRankingData(i).timeMin, sortSave.getRankingData(i).timeSec, sortSave.getRankingData(i).score);
		//}
	}

	SetFontSize(100);
	//文字の表示(点滅)
	if (++g_WaitTime < 30) {
		SetFontSize(30);
		DrawString(490, 670, "--  Press A ボタン  --", 0xFF0000);
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
	if (KeyManager::OnPadClicked(PAD_INPUT_B) == true)//KEY_INPUT_RETURN
	{
		return dynamic_cast<AbstractScene*> (new Scene_RankingTime());
	}
	return this;

}

