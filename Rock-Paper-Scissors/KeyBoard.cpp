#include "KeyBoard.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"SortSave.h"
#include"SortSaveTime.h"

namespace KEY_CONSTANTS
{
	const int CUR_INIT_X = 145;   //カーソル初期位置ｘ
	const int CUR_INIT_Y = 315;   //カーソル初期位置ｙ

	const int CUR_NL_W = 60;      //カーソル幅ノーマル
	const int CUR_NL_H = 60;      //カーソル高ノーマル

	const int KEY_DISTANCE = 10;  //キー間の距離(カーソル幅差分)

	const int INPUTSPACE_X = 350; //名前入力欄ｘ
	const int INPUTSPACE_Y = 160; //名前入力欄ｙ

	const int INPUT_INTERVAL = 10;//連続入力制御

	//入力文字   （実際に表示されているキーボードと同じ配置）
	const char AllStr[5][14] = 
	{
		"ABCDEFGHIJKLM",
		"NOPQRSTUVWXYZ",
		"abcdefghijklm",
		"nopqrstuvwxyz",
		"0123456789!?%"
	};

	//入力がない時に表示される文字列
	const std::string No_Input("Please Your Name");
}

int KeyBoard::font_input = 0;

//コンストラクタ
KeyBoard::KeyBoard() :isStartKey(true), frame(0), frame_CL(0), KeyType(_KEY_TYPE::NORMAL), num_x(0), num_y(0)
{
	if (font_input == 0) font_input = CreateFontToHandle("メイリオ", 50, 10, DX_FONTTYPE_ANTIALIASING);
	
	//開幕Aが押されている状態
	if (KeyManager::OnPadPressed(PAD_INPUT_A)) isStartKey = false;

	//--------------------- image -------------------------
	image_back = LoadGraph("images/Story/starback.png");              //背景
	image_key = LoadGraph("images/KeyBoard/Keyboard_AlNum03.png");    //キーボード
	LoadDivGraph("images/KeyBoard/Cursor_normal.png", 2, 2, 1, 60, 60, image_cur_NL);    //ノーマルカーソル
	LoadDivGraph("images/KeyBoard/Cursor_Cancel.png", 2, 2, 1, 80, 130, image_cur_CL);   //キャンセル
	LoadDivGraph("images/KeyBoard/Cursor_Done.png", 2, 2, 1, 80, 200, image_cur_DN);     //確定
	image_button[0] = LoadGraph("images/KeyBoard/Bbutton.png");       //"B"
	image_button[1] = LoadGraph("images/KeyBoard/start.png");         //"START"
	image_inputSpace = LoadGraph("images/KeyBoard/Input_Frame.png");  //名前入力欄

	//--------------------- sound -------------------------
	se_normalkey = LoadSoundMem("Sound/KeyBoard/key_normalpush.wav");
	se_cancelkey = LoadSoundMem("Sound/KeyBoard/key_cancel.wav");
	se_donekey = LoadSoundMem("Sound/KeyBoard/key_ok.wav");
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	using namespace KEY_CONSTANTS;

	//開幕Aが押されている状態を無効化
	if (isStartKey == false && KeyManager::OnPadReleased(PAD_INPUT_A)) isStartKey = true;

	//左
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		//一瞬の入力と長押し入力に対応する
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_LEFT))
		{
			num_x--;
			if (num_x < 0) num_x = 13;   //右端へ

			KeyType = _KEY_TYPE::NORMAL; //ノーマル
		}

		//ノーマルキー以外のキー調整
		if (num_x == 13 && num_y == 1) num_y = 0;
		if (num_x == 13 && num_y >= 3) num_y = 2;
	}
	//右
	else if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		//一瞬の入力と長押し入力に対応する
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_RIGHT))
		{
			num_x++;
			if (num_x > 13) num_x = 0;   //左端へ

			KeyType = _KEY_TYPE::NORMAL; //ノーマル
		}

		//ノーマルキー以外のキー調整
		if (num_x == 13 && num_y == 1) num_y = 0;
		if (num_x == 13 && num_y >= 3) num_y = 2;
	}
	//上
	else if (KeyManager::OnPadPressed(PAD_INPUT_UP))
	{
		//一瞬の入力と長押し入力に対応する
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_UP))
		{
			num_y--;
			if (num_y < 0) num_y = 4;    //下端へ

			KeyType = _KEY_TYPE::NORMAL; //ノーマル
		}

		//ノーマルキー以外のキー調整
		if (num_x == 13 && num_y >= 2) num_y = 2;
		else if (num_x == 13 && num_y == 1) num_y = 0;
	}
	//下
	else if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		//一瞬の入力と長押し入力に対応する
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_DOWN))
		{
			num_y++;
			if (num_y > 4) num_y = 0;   //上端へ

			KeyType = _KEY_TYPE::NORMAL; //ノーマル
		}

		//ノーマルキー以外のキー調整
		if (num_x == 13 && num_y == 0 || num_x == 13 && num_y == 1) num_y = 2;
		else if (num_x == 13 && num_y == 2 || num_x == 13 && num_y == 3) num_y = 0;
	}
	else {};

	//キャンセルキー
	if (num_x == 13 && num_y == 0 || num_x == 13 && num_y == 1) KeyType = _KEY_TYPE::CANCEL;
	//確定キー
	if (num_x == 13 && num_y >= 2) KeyType = _KEY_TYPE::DONE;

	//離したとき
	if (KeyManager::OnPadReleased(PAD_INPUT_LEFT))  frame = 0;
	if (KeyManager::OnPadReleased(PAD_INPUT_RIGHT)) frame = 0;
	if (KeyManager::OnPadReleased(PAD_INPUT_UP))    frame = 0;
	if (KeyManager::OnPadReleased(PAD_INPUT_DOWN))  frame = 0;
}

void KeyBoard::Draw() const
{
	using namespace KEY_CONSTANTS;

	//背景
	DrawGraph(0, 0, image_back, FALSE);
	//キーボード
	DrawGraph(0,0, image_key, TRUE);
	//" (B) "
	DrawGraph(1110, 325, image_button[0], TRUE);
	//" (START) "
	DrawGraph(1080, 465, image_button[1], TRUE);
	//名前入力
	DrawGraph(INPUTSPACE_X, INPUTSPACE_Y, image_inputSpace, TRUE);

	//カーソル座標
	int draw_x = 0;
	int draw_y = 0;
	//カーソル画像
	const int* draw_image = image_cur_NL;

	//キーの種類で描画位置を調整
	switch (KeyType)
	{
	case KeyBoard::_KEY_TYPE::NORMAL:
		draw_x = CUR_INIT_X + (num_x * (CUR_NL_W + KEY_DISTANCE));
		draw_y = CUR_INIT_Y + (num_y * (CUR_NL_H + KEY_DISTANCE));
		break;

	case KeyBoard::_KEY_TYPE::CANCEL:
		draw_x = CUR_INIT_X + (num_x * (CUR_NL_W + KEY_DISTANCE));
		draw_y = CUR_INIT_Y;
		draw_image = image_cur_CL;
		break;

	case KeyBoard::_KEY_TYPE::DONE:
		draw_x = CUR_INIT_X + (num_x * (CUR_NL_W + KEY_DISTANCE));
		draw_y = 455;
		draw_image = image_cur_DN;
		break;

	default:
		break;
	}

	//カーソル
	DrawGraph(draw_x, draw_y, draw_image[isPushA], TRUE);
}

int KeyBoard::KeyBoard_PushA()
{
	using namespace KEY_CONSTANTS;

	// Aボタン押され中　かつ　開幕A防止
	if (KeyManager::OnPadPressed(PAD_INPUT_A) && isStartKey == true)
	{
		//押せるのは一回のみ
		switch (KeyType)
		{
		case KeyBoard::_KEY_TYPE::NORMAL:

			//10文字まで 入力できるのは1回
			if (isPushA == false && input_str.size() < 10)
			{
				input_str.push_back(KEY_CONSTANTS::AllStr[num_y][num_x]);
				PlaySoundMem(se_normalkey, DX_PLAYTYPE_BACK);
			}
			break;


		case KeyBoard::_KEY_TYPE::CANCEL:

			//一瞬の入力と長押し入力に対応する
			if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_A))
			{
				//一文字でも入力されていれば一文字消す
				if (input_str.empty() != true) 
				{
					input_str.pop_back();
					PlaySoundMem(se_cancelkey, DX_PLAYTYPE_BACK);
				}
			}
			break;

		case KeyBoard::_KEY_TYPE::DONE:

			//一文字も入力されていない場合は確定できない
			if (input_str.empty() != true)
			{
				char* name = const_cast<char*>(input_str.c_str());
				sortSave.setName(9, name);
				sortSaveTime.setName(9, name);
				if (CheckSoundMem(se_donekey) == 0) PlaySoundMem(se_donekey, DX_PLAYTYPE_BACK);

				return 1;
			}
			else
			{
				//確定不可
			}
			break;

		default:
			break;
		}
		isPushA = true;
	}
	else
	{
		isPushA = false;
	}

	//Bボタンでも一文字消せる
	if (KeyManager::OnPadPressed(PAD_INPUT_B))
	{
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_B))
		{
			if (input_str.empty() != true)
			{
				input_str.pop_back();
				PlaySoundMem(se_cancelkey, DX_PLAYTYPE_BACK);
			}
		}
		
	}
	//離したとき
	if (KeyManager::OnPadReleased(PAD_INPUT_B)) frame_CL = 0;
	
	//STARTボタンでも確定できる
	if (KeyManager::OnPadClicked(PAD_INPUT_8))
	{
		//一文字も入力されていない場合は確定できない
		if (input_str.empty() != true)
		{
			char* name = const_cast<char*>(input_str.c_str());
			sortSave.setName(9, name);
			sortSaveTime.setName(9, name);
			if (CheckSoundMem(se_donekey) == 0) PlaySoundMem(se_donekey, DX_PLAYTYPE_BACK);

			return 1;
		}
		else
		{
			//確定不可
		}
	}

	return 0;
}

//入力文字列表示
void KeyBoard::DrawInputInfo() const
{
	using namespace KEY_CONSTANTS;

	//入力なし
	if (input_str.empty() == true)
	{
		int str_w = GetDrawStringWidthToHandle(No_Input.c_str(), No_Input.length(), font_input);

		DrawStringToHandle((640 - (str_w / 2)), INPUTSPACE_Y + 15, "Please Your Name", 0xffffff, font_input);
	}
	else
	{
		int str_w = GetDrawStringWidthToHandle(input_str.c_str(), input_str.length(), font_input);

		DrawStringToHandle(640 - (str_w / 2), INPUTSPACE_Y + 15, input_str.c_str(), 0xffffff, font_input);
	}
}
