#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_GameMain.h"

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

//コンストラクタ
GameClearScene::GameClearScene(int Next):Next(Next)
{
	SetFontSize(50);
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
	
	DrawString(100, 360, "ゲームクリア", 0xffffff);
	DrawString(100, 460, "Aボタンを押してください", 0xffffff);
	DrawString(100, 560, "Bボタンで次のステージ", 0xffffff);
}

//シーンの変更
AbstractScene* GameClearScene::ChangeScene()
{
	//Aボタンで戻る
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
		//return dynamic_cast<AbstractScene*> (new Scene_Stage00());
	}
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
