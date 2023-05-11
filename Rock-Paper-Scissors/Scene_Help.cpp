#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Help.h"
#include"Scene_Title.h"
#include "Scene_Stage01.h"
//コンストラクタ
HelpScene::HelpScene()
{
	HelpImage = LoadGraph("images/Help2.png");
}

//デストラクタ
HelpScene::~HelpScene()
{

}

//更新
void HelpScene::Update()
{
	
}

//描画
void HelpScene::Draw() const
{

	DrawGraph(0, 0, HelpImage, TRUE);
	SetFontSize(30);
	//DrawString(100, 100, "赤色のBボタンでグー属性に変更", 0x000000);
	//DrawString(100, 500, "ヘルプシーン Bボタンでチュートリアル", 0xffffff);
}

//シーンの変更
AbstractScene* HelpScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		return dynamic_cast<AbstractScene*> (new Scene_Stage01());
	}
	return this;  //更新なし
}