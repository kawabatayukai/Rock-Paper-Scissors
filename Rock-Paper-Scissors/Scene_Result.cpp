#include "Scene_Result.h"
#include"Scene_Ranking.h"
#include"Scene_InputRanking.h"
#include <DxLib.h>
#include "KeyManager.h"

int a = 0;

//更新
void  Scene_Result::Update()
{
	// フォントサイズの設定
	SetFontSize(20);

	// 名前入力指示文字列の描画
	DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
	DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);

	// 名前の入力
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	//ランキング入力処理
	if (KeyInputSingleCharString(170, 310, 10, name, FALSE) == 1)
	{
		inputRanking.setName(9, name);
		inputRanking.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
		inputRanking.SortRanking();		// ランキング並べ替え
		inputRanking.SaveRanking();		// ランキングデータの保存
		a = 1;
	}
}
//描画
void  Scene_Result::Draw() const
{
	// フォントサイズの設定
	SetFontSize(20);

	// 名前入力指示文字列の描画
	DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
	DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);

	// 名前の入力
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
}

//シーンの変更処理
AbstractScene* Scene_Result::ChangeScene()
{
	//if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	if (a == 1)
	{
		return new Scene_Ranking();
	}
	return this;
}