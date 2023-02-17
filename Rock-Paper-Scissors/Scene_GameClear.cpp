#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_GameMain.h"
#include"Scene_Stage00.h"

//コンストラクタ
GameClearScene::GameClearScene()
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

	return this;
}
