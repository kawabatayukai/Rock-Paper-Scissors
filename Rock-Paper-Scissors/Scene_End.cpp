#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_End.h"
#include"Scene_GameMain.h"

//コンストラクタ
EndScene::EndScene() : framecount(0), PosY(0)
{
	font = CreateFontToHandle("Yu Gothic UI", 24, 5, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 2);
}

//デストラクタ
EndScene::~EndScene()
{
	DeleteFontToHandle(font);
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
	DrawString(300, 1400 + PosY, "Thank You for Playing!!!", 0xffffff);
	SetFontSize(70);
	DrawString(220, 100 + PosY, "J A N K E N  W O R L D", 0xFFFFFF);
	SetFontSize(24);
	//DrawStringToHandle(300, 200 + PosY, "最終更新日　　2023年05月26日", 0xFFFFFF,font);
	DrawStringToHandle(550, 230 + PosY, "素材利用", 0xFFFFFF,font);
	DrawStringToHandle(200, 260 + PosY, "画像  ぴぽや倉庫 https://pipoya.net/sozai/", 0xFFFFFF,font);
	DrawStringToHandle(200, 290 + PosY, "画像  OKUMONO URL https://sozaino.site/", 0xFFFFFF,font);
	DrawStringToHandle(200, 320 + PosY, "画像  illustAC URL https://www.ac-illust.com/", 0xFFFFFF,font);
	DrawStringToHandle(200, 350 + PosY, "画像  いらすとや URL https://www.irasutoya.com/", 0xFFFFFF,font);
	DrawStringToHandle(200, 380 + PosY, "画像  Unishar-ユニシャー URL https://miyagame.net/wallpaper/", 0xFFFFFF,font);
	DrawStringToHandle(200, 410 + PosY, "画像  ぐったりにゃんこ URL http://guttari8.sakura.ne.jp/", 0xFFFFFF,font);
	DrawStringToHandle(200, 440 + PosY, "BGM/SE　MusMus URL https://musmus.main.jp", 0xFFFFFF,font);
	DrawStringToHandle(200, 470 + PosY, "BGM/SE　効果音ラボ URL https://soundeffect-lab.info/sound/battle/", 0xFFFFFF,font);
	DrawStringToHandle(200, 500 + PosY, "BGM/SE　springin URL https://www.springin.org/", 0xFFFFFF,font);
	DrawStringToHandle(200, 530 + PosY, "BGM/SE　無料効果音で遊ぼう！ URL https://taira-komori.jpn.org/index.html", 0xFFFFFF,font);
	DrawStringToHandle(200, 560 + PosY, "BGM/SE　魔王魂 URL https://maou.audio/", 0xFFFFFF,font);
	DrawStringToHandle(200, 590 + PosY, "BGM/SE　甘茶の音楽工房 URL https://amachamusic.chagasi.com/", 0xFFFFFF,font);
	DrawStringToHandle(200, 620 + PosY, "BGM/SE　ハシマミ URL https://hashimamiweb.com/", 0xFFFFFF,font);
	DrawStringToHandle(200, 650 + PosY, "BGM/SE　FREE BGM URL https://ucchii0artist.wixsite.com/ucchii0", 0xFFFFFF,font);
	DrawStringToHandle(200, 680 + PosY, "BGM/SE　DOVA-SYNDROME URL https://dova-s.jp/", 0xFFFFFF,font);
	DrawStringToHandle(200, 710 + PosY, "動画用合成音声  バズ読 URL https://buzzdoku.itl-portal.com/", 0xFFFFFF, font);


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