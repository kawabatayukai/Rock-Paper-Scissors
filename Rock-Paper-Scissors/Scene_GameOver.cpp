#include "Scene_GameOver.h"
#include"Scene_GameMain.h"
#include"Scene_Title.h"
#include"DxLib.h"
#include"KeyManager.h"

#include"GameData.h"
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
//コンストラクタ
GameOverScene::GameOverScene(int again):again(again)
{
	SetFontSize(50);
	image_back = LoadGraph("images/GameOver.png");
}

GameOverScene::GameOverScene() :again(11)
{
	SetFontSize(50);
	image_back = LoadGraph("images/GameOver.png");
}

//デストラクタ
GameOverScene::~GameOverScene()
{
	SetFontSize(20);
}

//更新
void GameOverScene::Update()
{

}

//描画
void GameOverScene::Draw() const
{
	//背景
	DrawGraph(0, 0, image_back, TRUE);
	/*SetFontSize(50);
	DrawString(100, 360, "ゲームオーバー", 0xffffff);
	DrawString(100, 460, "Aボタンを押してください", 0xffffff);*/
}

//シーンの変更
AbstractScene* GameOverScene::ChangeScene()
{
	/*通常モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::NOMAL)
	{
		//Aボタンで戻る
		if (KeyManager::OnPadClicked(PAD_INPUT_A))
		{
			return dynamic_cast<AbstractScene*> (new TitleScene());
		}

		if (KeyManager::OnPadClicked(PAD_INPUT_B))
		{
			switch (again)
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
	}

	/*即死モード*/
	if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	return this;
}
