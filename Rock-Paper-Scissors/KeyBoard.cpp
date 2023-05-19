#include "KeyBoard.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"SortSave.h"
#include"SortSaveTime.h"

#define KEY_CENTER_X 320      //幅  720　用で作ったキーボードを無理やり中心に持ってくる
#define KEY_CENTER_Y 120      //高さ480　　　　　　　　　　不要な時は CENTER_X,Y を0にしてください

#define ALPHA_MAX 26      //アルファベット総数

#define OUT_WIDTH 45 + KEY_CENTER_X     //画面左端～キーボードまでの幅
#define OUT_HEIGHT 200 + KEY_CENTER_Y    //画面上端～キーボードまでの高さ
#define SPACE 10          //キー間のスペース
#define KEY_WIDTH 40      //ノーマルキーの幅
const int CurStdX = OUT_WIDTH + SPACE + 5;    //カーソルのX座標基準    (「5」はカーソルの幅 ）
const int CurStdY = OUT_HEIGHT + SPACE + 5;   //カーソルのY座標基準

namespace ALL_KEYS
{
	//入力文字   （実際に表示されているキーボードと同じ配置）
	const char AllStr[5][ALPHA_MAX / 2 + 1] = {
		"ABCDEFGHIJKLM",
		"NOPQRSTUVWXYZ",
		"abcdefghijklm",
		"nopqrstuvwxyz",
		"0123456789"
	};
}

int KeyBoard::font_input = 0;

//コンストラクタ
KeyBoard::KeyBoard() : movekeyX(0), movekeyY(0), CURSOR_NOW(_CURSOR_TYPE::NORMAL)
{
	keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png");
	LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage);
	//「×」カーソル
	LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage);
	//「OK」カーソル
	LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage);

	if (font_input == 0) font_input = CreateFontToHandle("メイリオ", 20, 3, DX_FONTTYPE_ANTIALIASING);\
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	frame++;  //フレームカウント

	//右
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		if (CursorControl() == true) movekeyX++;    //タイミング調整 + 移動
		if (movekeyX > 12) movekeyX = 0;            //右端以上で左端へ  
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //現在のキーはノーマル
	}
	//左
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		if (CursorControl() == true) movekeyX--;    //タイミング調整 + 移動
		if (movekeyX < 0) movekeyX = 12;            //右端以上で左端へ  
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //現在のキーはノーマル
	}
	//上
	if (KeyManager::OnPadPressed(PAD_INPUT_UP))
	{
		if (CursorControl() == true) movekeyY--;    //タイミング調整 + 移動
		if (movekeyY <= 0) movekeyY = 0;            //右端以上で左端へ  
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //現在のキーはノーマル
	}
	//下
	if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		if (CursorControl() == true) movekeyY++;    //タイミング調整 + 移動
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //現在のキーはノーマル
	}

	//「×」ボタン   「a～z」段より下 かつ 「9」キーより右側
	if (movekeyY == 4 && movekeyX >= 10)
	{
		movekeyX = 10;                             //ボタンの位置
		CURSOR_NOW = _CURSOR_TYPE::CANCEL;         //現在のキーはキャンセル「×」
	}
	//「OK」ボタン   キーボード最下段より下
	if (movekeyY >= 5)
	{
		movekeyX = 4;                              //ボタンの位置
		movekeyY = 5;

		CURSOR_NOW = _CURSOR_TYPE::DONE;           //現在のキーはDONE「OK」
	}
}

void KeyBoard::Draw() const
{
	//背景
	DrawGraph(0, 0, backimage, FALSE);
	//キーボード
	DrawGraph(45 + KEY_CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);


	// ノーマル(A～Z,a～z,0～9)・「×」・「ＯＫ」によって画像変化　 switch文で操作
	// 　　　　　　　　押す・押さないによって画像変化　　　　　　　 画像配列を PushFlg で操作

	//画像配列の 0番目 は「押していない」カーソル　　1番目は 「押している」カーソル

	switch (CURSOR_NOW)
	{
	case _CURSOR_TYPE::NORMAL:    //ノーマルカーソル
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[isPushA], TRUE);
		break;

	case _CURSOR_TYPE::CANCEL:    //「×」カーソル
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[isPushA], TRUE);
		break;

	case _CURSOR_TYPE::DONE:      //「OK」カーソル
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[isPushA], TRUE);
		break;

	default:
		break;
	}
}

bool KeyBoard::CursorControl()
{
	int timing = 8;
	if (frame % timing == 0) return true;
	return false;
}

int KeyBoard::KeyBoard_PushA()
{
	using namespace ALL_KEYS;

	if (KeyManager::OnPadPressed(PAD_INPUT_A))
	{
		if (CursorControl() == true)
		{
			// "A～Z","a～z","1～9"の上で押された
			if (CURSOR_NOW == _CURSOR_TYPE::NORMAL)
			{
				isPushA = true;

				//10文字まで
				if (input_str.size() < 10)
				{
					input_str.push_back(AllStr[movekeyY][movekeyX]);
				}
			}
			else if (CURSOR_NOW == _CURSOR_TYPE::CANCEL)
			{
				isPushA = true;
				//一文字でも入力されていれば一文字消す
				if (input_str.empty() != true) input_str.pop_back();
			}
			else if (CURSOR_NOW == _CURSOR_TYPE::DONE)
			{
				//一文字も入力されていない場合は確定できない
				if (input_str.empty() != true)
				{
					char* name = const_cast<char*>(input_str.c_str());
					sortSave.setName(9, name);
					sortSaveTime.setName(9, name);

					return 1;
				}
				else
				{
					//確定不可
				}
			}
		}
	}
	else
	{
		isPushA = false;
	}

	return 0;
}

void KeyBoard::DrawInputInfo() const
{
	if (input_str.empty() == true)
	{
		DrawStringToHandle(200 + KEY_CENTER_X, 125 + KEY_CENTER_Y, "Please Your Name", 0xffffff, font_input);
	}
	else
	{
		int str_w = GetDrawStringWidthToHandle(input_str.c_str(), input_str.length(), font_input);

		DrawStringToHandle(640 - (str_w / 2), 125 + KEY_CENTER_Y, input_str.c_str(), 0xffffff, font_input);
	}
}
