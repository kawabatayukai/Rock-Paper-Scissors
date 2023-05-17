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
	if (++WaitTime < 15000) PosY = 650 - WaitTime / 1;



	//タイムの加算処理＆終了
	if (++WaitTime < 10000) GameState = 99;
	framecount++;
}

//描画
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(300, 1380 + PosY, "Thank You for Playing!!!", 0xffffff);
	SetFontSize(50);
	DrawString(350, 140 + PosY, "タイトル　　　JankenWorld", 0xFFFFFF);
	SetFontSize(24);
	DrawString(400, 200 + PosY, "最終更新日　　2023年xx月xx日", 0xFFFFFF);
	DrawString(400, 230 + PosY, "制作者　　　　国際電子ビジネス専門学校", 0xFFFFFF);
	DrawString(250, 260 + PosY, "ステージ2,3,4,5,6 與那原 廉,宮城ジャスティン,玉寄 兼仁,備瀬 龍樹,新垣 大喜", 0xFFFFFF);
	DrawString(250, 290 + PosY, "ステージ7,8,9,10  川畑  勇快,棚原  碧人,仲吉  彪流,與座  芳弘", 0xFFFFFF);
	DrawString(550, 320 + PosY, "素材利用", 0xFFFFFF);
	DrawString(300, 350 + PosY, "画像  ぴぽや倉庫 https://pipoya.net/sozai/", 0xFFFFFF);
	DrawString(300, 380 + PosY, "画像  OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(300, 410 + PosY, "画像  illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(300, 440 + PosY, "画像  いらすとや URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(300, 470 + PosY, "画像  Unishar-ユニシャー URL https://miyagame.net/wallpaper/", 0xFFFFFF);
	DrawString(300, 500 + PosY, "BGM/SE　MusMus URL https://musmus.main.jp", 0xFFFFFF);
	DrawString(300, 530 + PosY, "BGM/SE　効果音ラボ URL https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(300, 565 + PosY, "BGM/SE　springin URL https://www.springin.org/", 0xFFFFFF);
	DrawString(300, 600 + PosY, "BGM/SE　無料効果音で遊ぼう！ URL https://taira-komori.jpn.org/index.html", 0xFFFFFF);
	DrawString(300, 630 + PosY, "BGM/SE　魔王魂 URL https://maou.audio/", 0xFFFFFF);
	DrawString(300, 660 + PosY, "BGM/SE　甘茶の音楽工房 URL https://amachamusic.chagasi.com/", 0xFFFFFF);
	DrawString(300, 690 + PosY, "BGM/SE　ハシマミ URL https://hashimamiweb.com/", 0xFFFFFF);
	DrawString(300, 720 + PosY, "BGM/SE　無料効果音で遊ぼう！ URL https://taira-komori.jpn.org/", 0xFFFFFF);


	//DrawFormatString(100, 600, 0xFFFFFF, "%f", framecount);
	/*DrawString(450, 630 + PosY, "  画像    OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(450, 660 + PosY, "  画像    illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(450, 690 + PosY, "  画像    いらすとや URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(450, 720 + PosY, "　BGM/SE　MusMus https://musmus.main.jp", 0xFFFFFF);
	DrawString(450, 750 + PosY, "　BGM/SE　効果音ラボ https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(450, 780 + PosY, "　BGM/SE　springin https://www.springin.org/", 0xFFFFFF);
	DrawString(450, 810 + PosY, "　BGM/SE　無料効果音で遊ぼう！ https://taira-komori.jpn.org/index.html", 0xFFFFFF);*/
}

//シーンの変更
AbstractScene* EndScene::ChangeScene()
{
	if (framecount > 900)
	{
		return nullptr;
	}

	return this;  //更新なし
}