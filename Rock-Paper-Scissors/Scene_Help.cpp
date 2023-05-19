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