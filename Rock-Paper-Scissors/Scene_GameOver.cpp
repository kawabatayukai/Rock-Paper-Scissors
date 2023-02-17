#include "Scene_GameOver.h"
#include"Scene_GameMain.h"
#include"Scene_Stage00.h"
#include"DxLib.h"
#include"KeyManager.h"

//コンストラクタ
GameOverScene::GameOverScene()
{
	SetFontSize(50);
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
	SetFontSize(50);
	DrawString(100, 360, "ゲームオーバー", 0xffffff);
	DrawString(100, 460, "Aボタンを押してください", 0xffffff);
}

//シーンの変更
AbstractScene* GameOverScene::ChangeScene()
{
	//Aボタンで戻る
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
		//return dynamic_cast<AbstractScene*> (new Scene_Stage00());
	}

	return this;
}
