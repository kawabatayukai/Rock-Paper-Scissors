#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"



//コンストラクタ
Scne_TitleInterval::Scne_TitleInterval()
{
}

//デストラクタ
Scne_TitleInterval::~Scne_TitleInterval()
{

}

void Scne_TitleInterval::Update()
{

}

//描画
void Scne_TitleInterval::Draw() const
{
	DrawString(0, 360, "Press A", 0xffffff);
	DrawString(0, 400, "凝ったタイトル", 0xffffff);
}

//シーンの変更
AbstractScene* Scne_TitleInterval::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		return dynamic_cast<AbstractScene*> (new TitleScene());
	//更新なし
	return this;
}