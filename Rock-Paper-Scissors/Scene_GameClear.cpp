#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_GameMain.h"
#include"Scene_Title.h"

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
}

//シーンの変更
AbstractScene* GameClearScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		return dynamic_cast<AbstractScene*> (new Scene_NextStage(Next));
	}
	return this;
}
