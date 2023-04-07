#include"DxLib.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"
#include"Scene_End.h"
#include"Scene_Stage01.h"

#include"GameData.h"

//コンストラクタ
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

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
	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {

		//上ボタンで上に
		T_selectnum++;

		if (T_selectnum > 1) T_selectnum = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {

		//下ボタンで下に
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 1;

	}

}

//描画
void TitleScene::Draw() const
{
	DrawGraph(0,0,TitleImage,TRUE);
	
	// 開発モード時はDebug_Manager.hの"DEBUG_MODE_GAMEMAIN"をコメントアウトする
#ifdef  DEBUG_MODE_GAMEMAIN

	DrawStringToHandle(70, 350, "START", 0xf, font_title);
#else
	DrawStringToHandle(70, 350, "GAMEMAIN", 0xf, font_title);
#endif

	DrawStringToHandle(70, 395, "END", 0xf, font_title);

	//メニューカーソル
	DrawTriangle(40, 355 + (T_selectnum * 52), 60, 370 + (T_selectnum * 52), 40, 385 + (T_selectnum * 52), GetColor(255, 0, 0), TRUE);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	//Aボタンで決定
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0:

			GameData::Init_Data();   //データの初期化

			// 開発モード時はDebug_Manager.hの"DEBUG_MODE_GAMEMAIN"をコメントアウトする
#ifdef  DEBUG_MODE_GAMEMAIN

			return dynamic_cast<AbstractScene*> (new Scene_Stage01);
#else
			return dynamic_cast<AbstractScene*> (new GameMainScene());
#endif
			break;



#ifdef  DEBUG_MODE_GAMEMAIN

			case 1:
				if (KeyManager::OnPadClicked(PAD_INPUT_A))
				{
					return dynamic_cast<AbstractScene*> (new EndScene());
				}
				break;
#endif

		default:
			break;
		}
	}

	return this;  //更新なし
}