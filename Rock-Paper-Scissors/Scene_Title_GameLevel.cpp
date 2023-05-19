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

int Scene_Title_GameLevel::font_title = 0;

//コンストラクタ
Scene_Title_GameLevel::Scene_Title_GameLevel()
{
	image_back = LoadGraph("images/Story/starback.png");

	//フォントデータを作成
	if (font_title == 0)
		font_title = CreateFontToHandle("メイリオ", 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	//データの初期化
	GameData::Init_Data();
	SetBackgroundColor(255, 255, 255);

	ex_image = LoadGraph("images/Story/ex.png");
	normal_image = LoadGraph("images/Story/no.png");
}

//デストラクタ
Scene_Title_GameLevel::~Scene_Title_GameLevel()
{
	//フォントデータを削除
	SetBackgroundColor(0, 0, 0);
}

//更新
void Scene_Title_GameLevel::Update()
{
	

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
	DrawGraph(0, 0, image_back, FALSE);

	DrawStringToHandle(70, 200, "ゲームモード選択", 0xffffff, font_title, 0x20b2aa);
	DrawStringToHandle(70, 350, "STANDARD", 0xffffff, font_title, 0x20b2aa);
	DrawStringToHandle(70, 400, "EXTRA JANKEN", 0xffffff, font_title, 0x20b2aa);
	DrawStringToHandle(70, 500, "B : タイトル", 0xffffff, font_title, 0x20b2aa);
	
	//メニューカーソル
	DrawTriangle(40, 355 + (T_selectnum * 50), 60, 370 + (T_selectnum * 50), 40, 385 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);

	//説明文字
	std::string str("通常のルールです。じゃん撃を駆使して戦います");

	//画像
	if (T_selectnum == 0)
	{
		DrawGraph(560, 154, normal_image, TRUE);
	}
	else if (T_selectnum == 1)
	{
		DrawGraph(560, 154, ex_image, TRUE);
		str = std::string("接触じゃんけんに勝つと即クリア。負けると即死になります");
	}
	int str_w = GetDrawStringWidthToHandle(str.c_str(), str.size(), font_title);

	DrawStringToHandle(640 - (str_w / 2), 650, str.c_str(), 0xffffff, font_title, 0x20b2aa);
}

//シーンの変更
AbstractScene* Scene_Title_GameLevel::ChangeScene()
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
		case 0:/*通常モード*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::NORMAL);
			return dynamic_cast<AbstractScene*> (new Scene_InputNameRanking());
			break;
		case 1:/*即死モード*/
			GameData::Set_DIFFICULTY(GAME_DIFFICULTY::HARD);
			return dynamic_cast<AbstractScene*> (new Scene_InputNameRanking());
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