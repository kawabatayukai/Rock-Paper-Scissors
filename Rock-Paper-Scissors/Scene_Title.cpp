#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"

#include"GameData.h"

//コンストラクタ
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");
}

//デストラクタ
TitleScene::~TitleScene()
{

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
	SetFontSize(50);
	DrawGraph(0,0,TitleImage,TRUE);
	DrawString(70, 350, "GAMEMAIN", 0xf);
	DrawString(70, 395, "END", 0xf);


	//メニューカーソル
	DrawTriangle(40, 355 + (T_selectnum * 52), 60, 370 + (T_selectnum * 52), 40, 385 + (T_selectnum * 52), GetColor(255, 0, 0), TRUE);
}

//シーンの変更
AbstractScene* TitleScene::ChangeScene()
{
	
	switch (T_selectnum)
	{
	case 0:

		if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		{
			GameData::Init_Data();   //データの初期化

			return dynamic_cast<AbstractScene*> (new GameMainScene());
		}
		/*case 1:
			if (KeyManager::OnPadClicked(PAD_INPUT_A))
			{
				return dynamic_cast<AbstractScene*> (new GameEnd());
			}*/

	default:
		break;
	}

	return this;  //更新なし
}