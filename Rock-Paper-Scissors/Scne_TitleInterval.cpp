#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"



//コンストラクタ
Scne_TitleInterval::Scne_TitleInterval()
{
	band[0] = LoadGraph("images/ロール1.png");
	band[1] = LoadGraph("images/ロール2.png");
	band[2] = LoadGraph("images/ロール3.png");
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