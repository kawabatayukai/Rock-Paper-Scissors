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

//コンストラクタ
GameClearScene::GameClearScene(int Next):Next(Next)
{
	clearImage = LoadGraph("images/GameClear2.png");
	clear_se = LoadSoundMem("Sound/GameClear.mp3");
}

//デストラクタ
GameClearScene::~GameClearScene()
{
	StopSoundMem(clear_se);
	SetFontSize(20);
}

//更新
void GameClearScene::Update()
{
	//clear_se
	if (CheckSoundMem(clear_se) == 0) PlaySoundMem(clear_se, DX_PLAYTYPE_BACK);
}

//描画
void GameClearScene::Draw() const
{
	//背景
	DrawGraph(0, 0, clearImage, TRUE);

	SetFontSize(50);
	DrawFormatString(200,500, 0x000000,"スコア：%d ・ 残り時間：%d分%d秒", GameData::Get_Score(), GameData::Get_Each_Time_Min(), GameData::Get_Each_Time_Sec());
	SetFontSize(20);

	/*SetFontSize(200);
	DrawString(200, 100, "StageClear", 0xffffff);

	SetFontSize(50);
	DrawString(450, 425, "B", GetColor(255, 0, 0));
	DrawString(500, 425, "NextStage...", 0xffffff);
	DrawString(450, 525, "A", GetColor(0, 255, 0));
	DrawString(500, 525, "Title", 0xffffff);*/
}

//シーンの変更
AbstractScene* GameClearScene::ChangeScene()
{
	//Aボタンで戻る
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
		//case 11:/*ランキング内部処理*/
		//	/*スコア順*/
		//	sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
		//	sortSave.SortRanking();		// ランキング並べ替え
		//	sortSave.SaveRanking();		// ランキングデータの保存
		//	/*時間順*/
		//	sortSaveTime.setTimerMin(9, 10); // ランキングデータの１０番目に時間：分を登録
		//	sortSaveTime.setTimerSec(9, 10); // ランキングデータの１０番目に時間：秒を登録
		//	sortSaveTime.SortRanking();		// ランキング並べ替え
		//	sortSaveTime.SaveRanking();		// ランキングデータの保存
		//	/*ランキング画面へ*/
		//	return new Scene_Ranking();
		//	break;
		//default:
		//	break;
		//}
		
		return dynamic_cast<AbstractScene*> (new Scene_NextStage(Next));
	}
	return this;
}
