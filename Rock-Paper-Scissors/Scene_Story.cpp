#include"DxLib.h"
#include"Scene_Story.h"
#include"Scene_Stage01.h"
#include<fstream>
#include<string>
#include<sstream>
#include"KeyManager.h"
#include "SortSave.h"
#include"Scene_NextStage.h"

int Scene_Story::font_text = 0;      //テキスト用フォント
int Scene_Story::font_skip = 0;      //"skip"用フォント

//定数
namespace _C_STORY
{
	const int CENTER_X = 640;    //画面中心
	const int FIRST_Y = 720;     //テキスト1行目の高さ

	const int MIN_SPEED = 2;     //最低スクロールスピード
	const int MAX_SPEED = 10;     //最大スクロールスピード
}

//コンストラクタ
Scene_Story::Scene_Story() :
	isLoadFailed(false), str_end(false)
	, scroll_y(0), scroll_speed(_C_STORY::MIN_SPEED), skipflash_count(0)
{

	story_bgm = LoadSoundMem("Sound/Story.wav");

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
		if (data.compare("そんな世界を正すべく、主人公「」がじゃんけん世界大会に出場する-----") == 0)
		{
			std::string name(sortSave.getRankingData(9).name);
			data.insert(data.find("「") + 2, name);
		}

		text->push_back(data);
	}

	//フォントを作成
	if (font_text == 0)
		font_text = CreateFontToHandle("メイリオ", 30, 10, DX_FONTTYPE_ANTIALIASING, -1, 0);
	if (font_skip == 0)
		font_skip = CreateFontToHandle("メイリオ", 20, 10, DX_FONTTYPE_ANTIALIASING);

	image_back = LoadGraph("images/Story/Story_Back.png");
	

}

//デストラクタ
Scene_Story::~Scene_Story()
{

	StopSoundMem(story_bgm);

	//テキストを削除
	delete text;
}

void Scene_Story::Update()
{

	//StoryBGM
	if (CheckSoundMem(story_bgm) == 0) PlaySoundMem(story_bgm, DX_PLAYTYPE_LOOP);

	using namespace _C_STORY;

	DrawGraph(0, 0, image_back, TRUE);

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
void Scene_Story::Draw() const
{
	using namespace _C_STORY;

	//DrawLine(CENTER_X, 0, CENTER_X, 720, 0xffffff, 3);
	

	//点滅"Skip"
	if (skipflash_count < 120)
	{
		if (scroll_speed <= _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press B To Skip", 0xffffff, font_skip);
		}
		else if (scroll_speed > _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press B To Slowly", 0xffffff, font_skip);
		}
		else {};
	}
}

//シーンの変更
AbstractScene* Scene_Story::ChangeScene()
{
	if(str_end == true && KeyManager::OnPadClicked(PAD_INPUT_A))
		//return dynamic_cast<AbstractScene*> (new Scene_Stage01());
		return dynamic_cast<AbstractScene*> (new Scene_NextStage(1));

	//テキストファイル読み込み失敗でステージ1へ
	if (isLoadFailed == true)  
		return dynamic_cast<AbstractScene*> (new Scene_Stage01());
	//更新なし
	return this;
}