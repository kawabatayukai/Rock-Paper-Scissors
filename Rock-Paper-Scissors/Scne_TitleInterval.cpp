#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include<fstream>
#include<string>
#include"KeyManager.h"
#include"Scene_Title.h"

//定数
namespace _C_STORY
{
	const int CENTER_X = 640;    //画面中心
	const int FIRST_Y = 300;     //テキスト1行目の高さ

	const int MIN_SPEED = 1;     //最低スクロールスピード
	const int MAX_SPEED = 7;     //最大スクロールスピード
}

//コンストラクタ
Scne_TitleInterval::Scne_TitleInterval() :
	isLoadFailed(false), str_end(false)
	, scroll_y(0), scroll_speed(_C_STORY::MIN_SPEED), skipflash_count(0)
{
	//ファイルストリーム
	std::ifstream read_file;

	//開く
	read_file.open("textdata/Arasuzi.txt", std::ios::in);

	//失敗!
	if (read_file.fail() == true) isLoadFailed = true;

	//動的に生成
	text = new std::vector<std::string>();

	//読み込み
	std::string data("");
	while (std::getline(read_file, data))
	{
		text->push_back(data);
	}

	//フォントを作成
	font_text = CreateFontToHandle("メイリオ", 30, 10, DX_FONTTYPE_ANTIALIASING, -1, 0);
	font_skip = CreateFontToHandle("メイリオ", 20, 10, DX_FONTTYPE_ANTIALIASING);
}

//デストラクタ
Scne_TitleInterval::~Scne_TitleInterval()
{
	//テキストを削除
	delete text;

	//フォントを削除
	DeleteFontToHandle(font_text);

	SetBackgroundColor(0, 0, 0);
}

void Scne_TitleInterval::Update()
{
	using namespace _C_STORY;

	//1行ずつ描画
	for (int i = 0; i < text->size(); i++)
	{
		std::string str(text->data()[i]);

		//文字列の幅
		int str_w = GetDrawStringWidthToHandle(str.c_str(), str.size(), font_text);

		//描画座標
		int str_x = CENTER_X - str_w / 2;
		int str_y = FIRST_Y + (i * 100) - scroll_y;

		//画面外でスキップ
		if (str_y < -30) continue;

		//char*に変換,
		DrawFormatStringToHandle(str_x, str_y, 0xffffff, font_text, "%s", str.c_str());

		//テキストの最終行まで終了
		if (i >= text->size() - 1 && str_y < 0) str_end = true;
	}
	if (str_end == true) DrawStringToHandle(100, 100, "Press A To Start", 0xffffff, font_text);



	//Bボタンで加速 / リセット
	if (KeyManager::OnPadClicked(PAD_INPUT_B) == true)
	{
		if (scroll_speed <= _C_STORY::MIN_SPEED)
		{
			scroll_speed = _C_STORY::MAX_SPEED;
		}
		else if (scroll_speed > _C_STORY::MIN_SPEED)
		{
			scroll_speed = _C_STORY::MIN_SPEED;
		}
		else {};
	}

	//スクロール
	scroll_y += scroll_speed;
	//点滅
	if (++skipflash_count >= 240) skipflash_count = 0;
}

//描画
void Scne_TitleInterval::Draw() const
{
	using namespace _C_STORY;

	DrawLine(CENTER_X, 0, CENTER_X, 720, 0xffffff, 3);
	SetBackgroundColor(0, 64, 0);

	//static bool str_end;

	////1行ずつ描画
	//for (int i = 0; i < text->size(); i++)
	//{
	//	std::string str(text->data()[i]);

	//	//文字列の幅
	//	int str_w = GetDrawStringWidthToHandle(str.c_str(), str.size(), font_text);

	//	//描画座標
	//	int str_x = CENTER_X - str_w / 2;
	//	int str_y = FIRST_Y + (i * 100) - scroll_y;

	//	//画面外でスキップ
	//	if (str_y < -30) continue;

	//	//char*に変換,
	//	DrawFormatStringToHandle(str_x, str_y, 0xffffff, font_text, "%s", str.c_str());

	//	//テキストの最終行まで終了
	//	if (i >= text->size() - 1 && str_y < 0) str_end = true;
	//}
	//if (str_end == true) DrawString(100, 100, "Press A To Start", 0xffffff);

	//点滅"Skip"
	if (skipflash_count < 120)
	{
		if (scroll_speed <= _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press A or B To Skip", 0xffffff, font_skip);
		}
		else if (scroll_speed > _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press B To Slowly", 0xffffff, font_skip);
		}
		else {};
	}
}

//シーンの変更
AbstractScene* Scne_TitleInterval::ChangeScene()
{
	//if (str_end == true && KeyManager::OnPadClicked(PAD_INPUT_A))
		//return dynamic_cast<AbstractScene*> (new TitleScene());
	if (KeyManager::OnPadClicked(PAD_INPUT_A) || KeyManager::OnPadClicked(PAD_INPUT_B))
		return dynamic_cast<AbstractScene*> (new TitleScene());

	//テキストファイル読み込み失敗でステージ1へ
	if (isLoadFailed == true)
		return dynamic_cast<AbstractScene*> (new TitleScene());
	//更新なし
	return this;
}