#include "Scene_Title_GameLevel.h"
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
#include "Scene_InputNameRanking.h"

//コンストラクタ
Scene_Title_GameLevel::Scene_Title_GameLevel()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//フォントデータを作成
	font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);
	font_debug = CreateFontToHandle("Yu Gothic UI", 20, 2, DX_FONTTYPE_ANTIALIASING_4X4);

	//データの初期化
	GameData::Init_Data();
	SetBackgroundColor(255, 255, 255);
}

//デストラクタ
Scene_Title_GameLevel::~Scene_Title_GameLevel()
{
	//フォントデータを削除
	DeleteFontToHandle(font_title);
	DeleteFontToHandle(font_debug);
	SoundSystem::StopBGM(BGM::TITLE);
	SetBackgroundColor(0, 0, 0);
}

//更新
void Scene_Title_GameLevel::Update()
{
	//SoundSystem::PlayBGM(BGM::TITLE);

	//カーソルを合わせてボタンを押すと遷移
	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {

		//上ボタンで上に
		T_selectnum++;

		if (T_selectnum > 1) T_selectnum = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {

		//下ボタンで下に
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 1;

	}

}

//描画
void Scene_Title_GameLevel::Draw() const
{
	

	DrawStringToHandle(70, 200, "難易度選択", 0xf, font_title);
	DrawStringToHandle(70, 350, "NOMAL", 0xf, font_title); 
	DrawStringToHandle(70, 400, "REAL JANKEN", 0xf, font_title);
	DrawStringToHandle(70, 500, "Bボタンで戻る", 0xf, font_title);
	
	//メニューカーソル
	DrawTriangle(40, 355 + (T_selectnum * 50), 60, 370 + (T_selectnum * 50), 40, 385 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);

	//デバッグ
	DrawStringToHandle(10, 650, "RT + A で選択画面(開発)", 0xf, font_debug);
}

//シーンの変更
AbstractScene* Scene_Title_GameLevel::ChangeScene()
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
		case 0:/*通常モード*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::NOMAL);
			//return dynamic_cast<AbstractScene*> (new Scene_Story());
			//return dynamic_cast<AbstractScene*> (new Scene_InputNamePlayer());
			return dynamic_cast<AbstractScene*> (new Scene_InputNameRanking());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		case 1:/*即死モード*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::HARD);
			//return dynamic_cast<AbstractScene*> (new Scene_Story());
			//return dynamic_cast<AbstractScene*> (new Scene_InputNamePlayer());
			return dynamic_cast<AbstractScene*> (new Scene_InputNameRanking());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		default:
			break;
		}
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	return this;  //更新なし
}