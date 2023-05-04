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

//コンストラクタ
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle1.png");

	//タイトルBGM読込み
	TitleBgm = LoadSoundMem("Sound/TitleBGM.mp3");
	//タイトルBGM音量
	ChangeVolumeSoundMem(150, TitleBgm);
	//セレクトSE読込み
	SelectSE = LoadSoundMem("Sound/Select.mp3");
	//セレクトSE音量
	ChangeVolumeSoundMem(230, SelectSE);
	//決定SE読込み
	ClickSE = LoadSoundMem("Sound/決定ボタンを押す24.mp3");
	//決定SE音量
	ChangeVolumeSoundMem(230, ClickSE);
	//フォントデータを作成
	font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);
}

//デストラクタ
TitleScene::~TitleScene()
{
	//フォントデータを削除
	DeleteFontToHandle(font_title);
}

//更新
void TitleScene::Update()
{
	//カーソルを合わせてボタンを押すと遷移
	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		//上ボタンで上に
		T_selectnum++;

		if (T_selectnum > 3) T_selectnum = 0;
		/*if (T_selectnum > 2) T_selectnum = 1;
		if (T_selectnum > 3) T_selectnum = 2;*/
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);

		//下ボタンで下に
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 3;
		/*if (T_selectnum < 1) T_selectnum = 2;
		if (T_selectnum < 2) T_selectnum = 3;*/

	}

}

//描画
void TitleScene::Draw() const
{
	DrawGraph(0,0,TitleImage,TRUE);
	PlaySoundMem(TitleBgm, DX_PLAYTYPE_LOOP, FALSE);
	// 開発モード時はDebug_Manager.hの"DEBUG_MODE_GAMEMAIN"をコメントアウトする
#ifdef  DEBUG_MODE_GAMEMAIN

	DrawStringToHandle(70, 350, "START", 0xf, font_title);
#else
	DrawStringToHandle(70, 140, "GAMEMAIN", 0xf, font_title);
	DrawStringToHandle(70, 195, "HELP", 0xf, font_title);
	DrawStringToHandle(70, 245, "RANKING", 0xf, font_title);
#endif

	DrawStringToHandle(70, 295, "END", 0xf, font_title);

	//メニューカーソル
	DrawTriangle(40, 155 + (T_selectnum * 50), 60, 170 + (T_selectnum * 50), 40, 185 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	//Aボタンで決定
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
		switch (T_selectnum)
		{
		case 0:

			GameData::Init_Data();   //データの初期化

			// 開発モード時はDebug_Manager.hの"DEBUG_MODE_GAMEMAIN"をコメントアウトする
#ifdef  DEBUG_MODE_GAMEMAIN

			return dynamic_cast<AbstractScene*> (new Scene_Stage01());
#else
			return dynamic_cast<AbstractScene*> (new GameMainScene());
		case 1:
			return dynamic_cast<AbstractScene*> (new HelpScene());
			/*if (KeyManager::OnPadClicked(PAD_INPUT_A))
			{

			}*/
			break;
		case 2:
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			break;
		case 3:
			return dynamic_cast<AbstractScene*> (new EndScene());
			/*return dynamic_cast<AbstractScene*> (new HelpScene());
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			return dynamic_cast<AbstractScene*> (new EndScene());*/
#endif
			break;



#ifdef  DEBUG_MODE_GAMEMAIN


			
#endif
				


		default:
			break;
		}
	}

	return this;  //更新なし
}