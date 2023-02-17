#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_End.h"
#include"Scene_GameMain.h"

//コンストラクタ
EndScene::EndScene()
{

}

//デストラクタ
EndScene::~EndScene()
{

}

//更新
void EndScene::Update()
{

}

//描画
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 100, "エンドシーン Aボタンで終了", 0xffffff);
}

//シーンの変更
AbstractScene* EndScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return nullptr;
	}

	return this;  //更新なし
}