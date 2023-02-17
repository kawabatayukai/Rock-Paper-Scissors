#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"

//コンストラクタ
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");
}

//デストラクタ
TitleScene::~TitleScene()
{

}

//更新
void TitleScene::Update()
{

}

//描画
void TitleScene::Draw() const
{
	SetFontSize(50);
	
	DrawGraph(0,0,TitleImage,TRUE);
	DrawString(100, 640, "タイトルシーン Aボタンでスタート", GetColor(255,0,0));
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}

	return this;  //更新なし
}