#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"

//コンストラクタ
Scne_TitleInterval::Scne_TitleInterval() : frame(0), speed(10)
{
	image_high = LoadGraph("images/title_high.png");
	image_middle = LoadGraph("images/title_middle.png");
	image_low = LoadGraph("images/title_low.png");
}

//デストラクタ
Scne_TitleInterval::~Scne_TitleInterval()
{

}

void Scne_TitleInterval::Update()
{
	frame++;
	if (frame > 128) frame = 128;
}

//描画
void Scne_TitleInterval::Draw() const
{
	//DrawString(0, 360, "Press A", 0xffffff);
	//DrawString(0, 400, "凝ったタイトル", 0xffffff);

	DrawGraph(-1280 + (frame * speed + 10), 0, image_high,TRUE);
	DrawGraph(1280 - (frame * speed + 10), (720 - 250), image_low, TRUE);
}

//シーンの変更
AbstractScene* Scne_TitleInterval::ChangeScene()
{
	if (frame == 128)
		return dynamic_cast<AbstractScene*> (new TitleScene());
	//更新なし
	return this;
}