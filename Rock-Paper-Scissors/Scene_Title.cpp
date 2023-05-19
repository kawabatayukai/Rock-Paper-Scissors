#include"DxLib.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"
#include"Scene_End.h"
#include"Scene_Stage01.h"
#include "Scene_Ranking.h"
#include "Scene_Help.h"
#include"GameData.h"
#include"SoundSystem.h"
#include"Scene_Story.h"
#include "Scene_Title_GameLevel.h"
#include"Scene_Ranking_GameLevel.h"


int TitleScene::font_title;   //フォントハンドル

//コンストラクタ
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//フォントデータを作成
	if (font_title == 0)
		font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	//データの初期化
	GameData::Init_Data();

	//BGMロード
	bgm = LoadSoundMem("Sound/TitleBGM.mp3");

}

//デストラクタ
TitleScene::~TitleScene()
{
	StopSoundMem(bgm);
	
}

//更新
void TitleScene::Update()
{
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//カーソルを合わせてボタンを押すと遷移
	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {

		//上ボタンで上に
		T_selectnum++;

		if (T_selectnum > 3) T_selectnum = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {

		//下ボタンで下に
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 3;

	}

}

//描画
void TitleScene::Draw() const
{
	DrawGraph(0, 0, TitleImage, FALSE);

	DrawStringToHandle(70, 250, "START", 0xf, font_title);
	DrawStringToHandle(70, 295, "HELP", 0xf, font_title);
	DrawStringToHandle(70, 345, "RANKING", 0xf, font_title);
	DrawStringToHandle(70, 395, "END", 0xf, font_title);

	//メニューカーソル
	DrawTriangle(40, 255 + (T_selectnum * 50), 60, 270 + (T_selectnum * 50), 40, 285 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);

	//デバッグ
	//DrawStringToHandle(10, 650, "RT + A で選択画面(開発)", 0xf, font_title);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	// RT + A でセレクト画面
	if (KeyManager::GetValue_RT() >= 40 && KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}
	//Aボタンで決定
	else if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0: //ゲームモードの選択
			return dynamic_cast<AbstractScene*> (new Scene_Title_GameLevel());
			break;
		case 1: //ヘルプ画面
			return dynamic_cast<AbstractScene*> (new HelpScene());
			break;
		case 2: //ランキング画面
			return dynamic_cast<AbstractScene*> (new Scene_Ranking_GameLevel());
			break;
		case 3: //エンド画面
			return dynamic_cast<AbstractScene*> (new EndScene());
			break;


		default:
			break;
		}
	}

	return this;  //更新なし
}