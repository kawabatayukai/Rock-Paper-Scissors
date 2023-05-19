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
	if (++WaitTime < 1700) PosY = 650 - WaitTime / 1;



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
	DrawString(350, 110 + PosY, "タイトル　JankenWorld", 0xFFFFFF);
	SetFontSize(24);
	DrawString(400, 200 + PosY, "最終更新日　　2023年xx月xx日", 0xFFFFFF);
	DrawString(400, 230 + PosY, "制作者　　　　国際電子ビジネス専門学校", 0xFFFFFF);
	DrawString(450, 260 + PosY, "ステージ2  與那原 廉", 0xFFFFFF);
	DrawString(450, 290 + PosY, "ステージ3  宮城ジャスティン", 0xFFFFFF);
	DrawString(450, 320 + PosY, "ステージ4  玉寄 兼仁", 0xFFFFFF);
	DrawString(450, 350 + PosY, "ステージ5  備瀬 龍樹", 0xFFFFFF);
	DrawString(450, 380 + PosY, "ステージ6  新垣 大喜", 0xFFFFFF);
	DrawString(450, 410 + PosY, "ステージ7  川畑  勇快", 0xFFFFFF);
	DrawString(450, 440 + PosY, "ステージ8  棚原  碧人", 0xFFFFFF);
	DrawString(450, 470 + PosY, "ステージ9  仲吉  彪流", 0xFFFFFF);
	DrawString(450, 500 + PosY, "ステージ10 與座  芳弘", 0xFFFFFF);
	DrawString(550, 530 + PosY, "素材利用", 0xFFFFFF);
	DrawString(300, 560 + PosY, "画像  ぴぽや倉庫 https://pipoya.net/sozai/", 0xFFFFFF);
	DrawString(300, 590 + PosY, "画像  OKUMONO URL https://sozaino.site/", 0xFFFFFF);
	DrawString(300, 620 + PosY, "画像  illustAC URL https://www.ac-illust.com/", 0xFFFFFF);
	DrawString(300, 650 + PosY, "画像  いらすとや URL https://www.irasutoya.com/", 0xFFFFFF);
	DrawString(300, 680 + PosY, "画像  Unishar-ユニシャー URL https://miyagame.net/wallpaper/", 0xFFFFFF);
	DrawString(300, 710 + PosY, "BGM/SE　MusMus URL https://musmus.main.jp", 0xFFFFFF);
	DrawString(300, 740 + PosY, "BGM/SE　効果音ラボ URL https://soundeffect-lab.info/sound/battle/", 0xFFFFFF);
	DrawString(300, 770 + PosY, "BGM/SE　springin URL https://www.springin.org/", 0xFFFFFF);
	DrawString(300, 800 + PosY, "BGM/SE　無料効果音で遊ぼう！ URL https://taira-komori.jpn.org/index.html", 0xFFFFFF);
	DrawString(300, 830 + PosY, "BGM/SE　魔王魂 URL https://maou.audio/", 0xFFFFFF);
	DrawString(300, 860 + PosY, "BGM/SE　甘茶の音楽工房 URL https://amachamusic.chagasi.com/", 0xFFFFFF);
	DrawString(300, 890 + PosY, "BGM/SE　ハシマミ URL https://hashimamiweb.com/", 0xFFFFFF);
	DrawString(300, 920 + PosY, "BGM/SE　FREE BGM URL https://ucchii0artist.wixsite.com/ucchii0", 0xFFFFFF);
	DrawString(300, 950 + PosY, "BGM/SE　DOVA-SYNDROME URL https://dova-s.jp/", 0xFFFFFF);


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