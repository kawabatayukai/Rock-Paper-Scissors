#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_End.h"
#include"Scene_GameMain.h"

//コンストラクタ
EndScene::EndScene() : framecount(0)
{

}

//デストラクタ
EndScene::~EndScene()
{

}

//更新
void EndScene::Update()
{
	framecount++;
}

//描画
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 100, "End..", 0xffffff);
}

//シーンの変更
AbstractScene* EndScene::ChangeScene()
{
	if (framecount > 120)
	{
		return nullptr;
	}

	return this;  //更新なし
}