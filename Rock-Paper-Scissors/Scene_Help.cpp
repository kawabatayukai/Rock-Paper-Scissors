#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Help.h"
#include"Scene_Title.h"

//コンストラクタ
HelpScene::HelpScene()
{

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
	SetFontSize(50);
	DrawString(100, 100, "ヘルプシーン Aボタンでタイトル", 0xffffff);
}

//シーンの変更
AbstractScene* HelpScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	return this;  //更新なし
}