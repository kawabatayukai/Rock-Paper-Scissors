#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Help.h"
#include"Scene_Title.h"

int HelpScene::font_help = 0;

//コンストラクタ
HelpScene::HelpScene()
{
	HelpImage = LoadGraph("images/help/help_2.png");
	if(font_help == 0) font_help = CreateFontToHandle("メイリオ", 40, 10, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 3);
}

//デストラクタ
HelpScene::~HelpScene()
{

}

//更新
void HelpScene::Update()
{
	
}

//描画
void HelpScene::Draw() const
{
	DrawGraph(0, 0, HelpImage, TRUE);
	DrawStringToHandle(50, 660, "A : タイトル", 0xffffff, font_help, 0x7cd900);

	// ボタン演出
	SetDrawBlendMode(DX_BLENDMODE_ADD, 80);

	//LB
	if (KeyManager::OnPadPressed(PAD_INPUT_5)) 
		DrawRoundRect(398, 58, (398 + 90), (58 + 60), 10, 10, 0xffffff, TRUE);
	//RB
	if (KeyManager::OnPadPressed(PAD_INPUT_6)) 
		DrawRoundRect(777, 58, (777 + 89), (58 + 60), 10, 10, 0xffffff, TRUE);
	//LT
	if (KeyManager::GetValue_LT() > 30)        
		DrawRoundRect(268, 318, (268 + 90), (318 + 60), 10, 10, 0xffffff, TRUE);
	//RT
	if (KeyManager::GetValue_RT() > 30)
		DrawRoundRect(48, 318, (48 + 90), (318 + 60), 10, 10, 0xffffff, TRUE);
	//B
	if (KeyManager::OnPadPressed(PAD_INPUT_B))
		DrawCircle(975, 275, 33, 0xffffff, TRUE);
	//Y
	if (KeyManager::OnPadPressed(PAD_INPUT_4))
		DrawCircle(975, 362, 33, 0xffffff, TRUE);
	//X
	if (KeyManager::OnPadPressed(PAD_INPUT_3))
		DrawCircle(975, 455, 33, 0xffffff, TRUE);

	//LEFT Stick
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT) || KeyManager::OnPadPressed(PAD_INPUT_RIGHT)
	   || KeyManager::OnPadPressed(PAD_INPUT_UP) || KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		DrawCircle(566, 392, 33, 0xffffff, TRUE);

		if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			DrawTriangle(520, 310, 505, 295, 505, 326, 0xffffff, TRUE);
			DrawRoundRect(475, 295, 505, 326, 5, 5, 0xffffff, TRUE);
		}
		if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			DrawTriangle(532, 310, 544, 297, 544, 327, 0xffffff, TRUE);
			DrawRoundRect(544, 297, 575, 328, 5, 5, 0xffffff, TRUE);
		}
	}
	//Right Stick
	if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) != 0 || KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) != 0)
	{
		DrawCircle(713, 392, 33, 0xffffff, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//シーンの変更
AbstractScene* HelpScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	return this;  //更新なし
}