#include "Scene_Ranking_GameLevel.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include "Scene_Ranking.h"
#include"GameData.h"
#include"SoundSystem.h"

int Scene_Ranking_GameLevel::font_title = 0;

//コンストラクタ
Scene_Ranking_GameLevel::Scene_Ranking_GameLevel()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//フォントデータを作成
	if (font_title == 0)
		font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);

	//データの初期化
	GameData::Init_Data();
	SetBackgroundColor(255, 255, 255);
}

//デストラクタ
Scene_Ranking_GameLevel::~Scene_Ranking_GameLevel()
{
	//フォントデータを削除
	SoundSystem::StopBGM(BGM::TITLE);
	SetBackgroundColor(0, 0, 0);
}

//更新
void Scene_Ranking_GameLevel::Update()
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
void Scene_Ranking_GameLevel::Draw() const
{


	DrawStringToHandle(70, 200, "ゲームモード選択選択", 0xf, font_title);
	DrawStringToHandle(70, 350, "STANDARD", 0xf, font_title);
	DrawStringToHandle(70, 400, "EXTRA JANKEN", 0xf, font_title);
	DrawStringToHandle(70, 500, "Bボタンで戻る", 0xf, font_title);

	//メニューカーソル
	DrawTriangle(40, 355 + (T_selectnum * 50), 60, 370 + (T_selectnum * 50), 40, 385 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);
}

//シーンの変更
AbstractScene* Scene_Ranking_GameLevel::ChangeScene()
{
	//Aボタンで決定
	 if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0:/*通常モード*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::NORMAL);

			sortSave.ReadRanking();		// ランキングデータの読み込み
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			SoundSystem::StopBGM(BGM::TITLE);
			break;
		case 1:/*即死モード*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::HARD);

			sortSave.ReadRanking();		// ランキングデータの読み込み
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
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