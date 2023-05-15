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

//コンストラクタ
GameClearScene::GameClearScene(int Next):Next(Next)
{
	clearImage = LoadGraph("images/GameClear.png");
}

//デストラクタ
GameClearScene::~GameClearScene()
{
	SetFontSize(20);
}

//更新
void GameClearScene::Update()
{

}

//描画
void GameClearScene::Draw() const
{
	//背景
	DrawGraph(0, 0, clearImage, TRUE);

	SetFontSize(30);
	DrawFormatString(400,200, 0xFFFFFF,"スコア：%d ・ 時間：%d", GameData::Get_Score(), GameData::Get_Each_Time_Min());
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
			return dynamic_cast<AbstractScene*> (new Scene_Stage04());
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
			return dynamic_cast<AbstractScene*> (new Scene_Stage08());
			break;

		case 9:
			return dynamic_cast<AbstractScene*> (new Scene_Stage09());
			break;

		case 10:
			return dynamic_cast<AbstractScene*> (new Scene_Stage10());
			break;


		default:
			break;
		}
		
	}
	return this;
}
