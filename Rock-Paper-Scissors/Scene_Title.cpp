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

//コンストラクタ
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//フォントデータを作成
	font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	font_debug = CreateFontToHandle("Yu Gothic UI", 20, 2, DX_FONTTYPE_ANTIALIASING_4X4);

	//データの初期化
	GameData::Init_Data();
}

//デストラクタ
TitleScene::~TitleScene()
{
	//フォントデータを削除
	DeleteFontToHandle(font_title);
	DeleteFontToHandle(font_debug);
	SoundSystem::StopBGM(BGM::TITLE);
}

//更新
void TitleScene::Update()
{
	SoundSystem::PlayBGM(BGM::TITLE);

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

	DrawStringToHandle(70, 150, "START", 0xf, font_title);
	DrawStringToHandle(70, 195, "HELP", 0xf, font_title);
	DrawStringToHandle(70, 245, "RANKING", 0xf, font_title);
	DrawStringToHandle(70, 295, "END", 0xf, font_title);

	

	//メニューカーソル
	DrawTriangle(40, 155 + (T_selectnum * 50), 60, 170 + (T_selectnum * 50), 40, 185 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);

	//デバッグ
	DrawStringToHandle(10, 650, "RT + A で選択画面(開発)", 0xf, font_debug);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	// RT + A でセレクト画面
	if (KeyManager::GetValue_RT() >= 40 && KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
		SoundSystem::StopBGM(BGM::TITLE);
	}
	//Aボタンで決定
	else if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0:
			/*return dynamic_cast<AbstractScene*> (new Scene_Story());
			SoundSystem::StopBGM(BGM::TITLE);*/
			return dynamic_cast<AbstractScene*> (new Scene_Title_GameLevel());
			break;
		case 1:
			return dynamic_cast<AbstractScene*> (new HelpScene());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		case 2:
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		case 3:
			return dynamic_cast<AbstractScene*> (new EndScene());
			SoundSystem::StopBGM(BGM::TITLE);
			break;


		default:
			break;
		}
	}

	return this;  //更新なし
}