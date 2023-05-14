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
	////エンド画像表示
	//DrawGraph(0, 0, g_EndImage, FALSE);

	
}

//更新
void EndScene::Update()
{
	//エンディング表示
	if (++WaitTime < 950) PosY = 500 - WaitTime / 2;



	//タイムの加算処理＆終了
	if (++WaitTime > 950) GameState = 99;
	framecount++;
}

//描画
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(300, 100, "Thank You for Playing!!!", 0xffffff);
	SetFontSize(24);
	DrawString(450, 170 + PosY, "タイトル　　　JankenWorld", 0xFFFFFF);
	DrawString(450, 230 + PosY, "最終更新日　　2023年xx月xx日", 0xFFFFFF);
	DrawString(450, 260 + PosY, "制作者　　　　国際電子ビジネス専門学校", 0xFFFFFF);
	DrawString(450, 290 + PosY, "ステージ2     與那原　廉", 0xFFFFFF);
	DrawString(450, 320 + PosY, "ステージ3     宮城ジャスティン", 0xFFFFFF);
	DrawString(450, 350 + PosY, "ステージ4     玉寄  兼仁", 0xFFFFFF);
	DrawString(450, 380 + PosY, "ステージ5　   備瀬  龍樹", 0xFFFFFF);
	DrawString(450, 410 + PosY, "ステージ6     新垣  大喜", 0xFFFFFF);
	DrawString(450, 440 + PosY, "ステージ7     川畑  勇快", 0xFFFFFF);
	DrawString(450, 470 + PosY, "ステージ8     棚原  碧人", 0xFFFFFF);
	DrawString(450, 500 + PosY, "ステージ9     仲吉  彪流", 0xFFFFFF);
	DrawString(450, 530 + PosY, "ステージ10    與座  芳弘", 0xFFFFFF);
	DrawString(450, 565 + PosY, "素材利用", 0xFFFFFF);
	DrawString(450, 600 + PosY, "　BGM/SE　MusMus https://musmus.main.jp", 0xFFFFFF);
	DrawString(450, 630 + PosY, "　BGM/SE　効果音ラボ https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
}

//シーンの変更
AbstractScene* EndScene::ChangeScene()
{
	if (framecount > 620)
	{
		return nullptr;
	}

	return this;  //更新なし
}