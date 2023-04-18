#include "Scene_InputName.h"
#include"Scene_Ranking.h"
#include <DxLib.h>
#include "KeyManager.h"

//#define ALPHA_MAX 26      //アルファベット総数
//#define OUT_WIDTH 45      //画面左端～キーボードまでの幅
//#define OUT_HEIGHT 200    //画面上端～キーボードまでの高さ
//#define SPACE 10          //キー間のスペース
//#define KEY_WIDTH 40      //ノーマルキーの幅
//const int CurStdX = OUT_WIDTH + SPACE + 5;    //カーソルのX座標基準    (「5」はカーソルの幅 ）
//const int CurStdY = OUT_HEIGHT + SPACE + 5;   //カーソルのY座標基準

#define CENTER_X 320      //幅  720　用で作ったキーボードを無理やり中心に持ってくる
#define CENTER_Y 120      //高さ480　　　　　　　　　　不要な時は CENTER_X,Y を0にしてください
#define ALPHA_MAX 26      //アルファベット総数
#define OUT_WIDTH 45 + CENTER_X     //画面左端～キーボードまでの幅
#define OUT_HEIGHT 200 + CENTER_Y    //画面上端～キーボードまでの高さ
#define SPACE 10          //キー間のスペース
#define KEY_WIDTH 40      //ノーマルキーの幅
const int CurStdX = OUT_WIDTH + SPACE + 5;    //カーソルのX座標基準    (「5」はカーソルの幅 ）
const int CurStdY = OUT_HEIGHT + SPACE + 5;   //カーソルのY座標基準

//入力文字    ※わかりやすくするため半分（実際に表示されているキーボードと同じ配置）
const char AllStr[5][ALPHA_MAX / 2 + 1] = {
	"ABCDEFGHIJKLM",
	"NOPQRSTUVWXYZ",
	"abcdefghijklm",
	"nopqrstuvwxyz",
	"0123456789"
};

int a = 0;

Scene_InputName::Scene_InputName()
{
	KeyBoardInit();
	LoadKeyBoardImgaes();
}

//更新
void  Scene_InputName::Update()
{
	// フォントサイズの設定
	//SetFontSize(20);

	// 名前入力指示文字列の描画
	//DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
	//DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);
	
	// 名前の入力
	//DrawString(150, 310, "> ", 0xFFFFFF);
	//DrawBox(160, 305, 300, 335, 0x000055, TRUE);
	
	//ランキング入力処理
	//if (KeyInputSingleCharString(170, 310, 10, name, FALSE) == 1)
	//{
	//	sortSave.setName(9, name);
	//	sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
	//	sortSave.SortRanking();		// ランキング並べ替え
	//	sortSave.SaveRanking();		// ランキングデータの保存
	//	a = 1;
	//}
	
}
//描画
void  Scene_InputName::Draw() const
{
	// フォントサイズの設定
	//SetFontSize(20);
	
	// 名前入力指示文字列の描画
	//DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
	//DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);
	
	// 名前の入力
	//DrawString(150, 310, "> ", 0xFFFFFF);
	//DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	KeyBoard_Draw();
}

//初期処理
void Scene_InputName::KeyBoardInit()
{
	//カーソルの初期位置は"A"
	movekeyX = 0;             //ｘ方向0番目
	movekeyY = 0;             //ｙ方向1番目

	//カーソルの初期位置は「A」なのでノーマル
	CURSOR_NOW = CURSOR_TYPE::NORMAL;

	//入力文字列　初期化
	for (int i = 0; i < 10; i++)
	{
		name[i] = 0;
	}
	name[10] = '\0';     //配列の一番最後に"\0"(終端の目印)を入れておく
	input_Pos = -1;           //
	pushFlag = FALSE;         //最初はAボタンは押されていない
}

//画像読み込み
int Scene_InputName::LoadKeyBoardImgaes()
{
	//背景
	if ((backimage = LoadGraph("images/KeyBoard/back04.png")) == -1) return -1;
	//キーボード
	if ((keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png")) == -1) return -1;
	//分割読み込み　押したよ/押してない が連結した画像
	//ノーマルカーソル
	if ((LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
	//「×」カーソル
	if ((LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
	//「OK」カーソル
	if ((LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;
	return 0;
}

//効果音読み込み
//int Scene_InputName::LoadSounds()
//{

//}

//描画
void Scene_InputName::KeyBoard_Draw()const
{
	//背景
	DrawGraph(0, 0, backimage, FALSE);

	//キーボード
	DrawGraph(45 + CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);

	// ノーマル(A～Z,a～z,0～9)・「×」・「ＯＫ」によって画像変化　 switch文で操作
	// 　　　　　　　　押す・押さないによって画像変化　　　　　　　 画像配列を PushFlg で操作
	//画像配列の 0番目 は「押していない」カーソル　　1番目は 「押している」カーソル
	switch (CURSOR_NOW)
	{
	case CURSOR_TYPE::NORMAL:    //ノーマルカーソル
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[pushFlag], TRUE);
		break;
	case CURSOR_TYPE::CANCEL:    //「×」カーソル
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[pushFlag], TRUE);
		break;
	case CURSOR_TYPE::DONE:      //「OK」カーソル
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[pushFlag], TRUE);
		break;
	default:
		break;
	}
	//入力中の文字を表示
	DrawInputInfo();
}

//更新
void Scene_InputName::KeyBoard_Update()
{
	//フレーム数カウント
	frame++;

	//→ 右
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		if (CursorControl() == true)
		{
			movekeyX++;     //タイミング調整 + 移動
		}
		if (movekeyX > 12) movekeyX = 0;   //右端以上で左端へ
		CURSOR_NOW = CURSOR_TYPE::NORMAL;  //現在のキーはノーマル
	}
	//← 左
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		if (CursorControl() == true)
		{
			movekeyX--;     //タイミング調整 + 移動
		}
		if (movekeyX < 0) movekeyX = 12;     //左端以上で右端へ
		CURSOR_NOW = CURSOR_TYPE::NORMAL;    //現在のキーはノーマル
	}
	//↑ 上
	if (KeyManager::OnPadPressed(PAD_INPUT_UP))
	{
		if (CursorControl() == true)
		{
			movekeyY--;     //タイミング調整 + 移動
		}
		if (movekeyY <= 0) movekeyY = 0;     //上端でストップ
		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //現在のキーはノーマル
	}
	//↓ 下
	if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		if (CursorControl() == true)
		{
			movekeyY++;     //タイミング調整 + 移動
		}
		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //現在のキーはノーマル
	}
	//「×」ボタン   「a～z」段より下 かつ 「9」キーより右側
	if (movekeyY == 4 && movekeyX >= 10)
	{
		movekeyX = 10;                       //ボタンの位置
		CURSOR_NOW = CURSOR_TYPE::CANCEL;         //現在のキーはキャンセル「×」
	}
	//「OK」ボタン   キーボード最下段より下
	if (movekeyY >= 5)
	{
		movekeyX = 4;                        //ボタンの位置
		movekeyY = 5;
		CURSOR_NOW = CURSOR_TYPE::DONE;           //現在のキーはDONE「OK」
	}
}

//カーソルの移動・ボタンの長押しを調整
bool Scene_InputName::CursorControl()
{
	int timing = 8;
	if (frame % timing == 0) return true;
	//frame = 0;
	return false;
}

//Aボタンが押された時の処理  入力が終わると 1 が返ってくる
int Scene_InputName::KeyBoard_PushA(char* name)       //keyflg　 は"押された瞬間"キー
{
	//　Aボタンを押している間
	if (KeyManager::OnPadPressed(PAD_INPUT_A))
	{
		//長押しでの連続入力のタイミングを調整（PCのような）
		if (CursorControl() == true)
		{
			// "A～Z","a～z","1～9"の上で押された
			if (CURSOR_NOW == CURSOR_TYPE::NORMAL)
			{
				pushFlag = true;        //押されているよ
				++input_Pos;            //入力位置を一つ右に

				//上限は10文字   （配列の0～9）
				if (input_Pos > 9) input_Pos = 9;

				//文字配列に入力
				name[input_Pos] = AllStr[movekeyY][movekeyX];
			}
			else if (CURSOR_NOW == CURSOR_TYPE::CANCEL)                  //「×」キーの上で押された　一文字削除
			{
				pushFlag = true;        //押されているよ

				//一文字でも入力されていれば一文字消す
				if (name[input_Pos] != 0) name[input_Pos] = 0; //0 は何も入力されていない状態
				input_Pos--;            //入力位置を一つ左に

				//入力位置は最低-1まで
				if (input_Pos < -1) input_Pos = -1;
			}
			else if (CURSOR_NOW == CURSOR_TYPE::DONE)                  //「OK」キーの上で押された　確定
			{
				//一文字も入力されていない場合は確定できない
				if (name[input_Pos] != 0)
				{
					//一文字でも入力アリ
					name[input_Pos + 1] = '\0';       //最後の文字の一つ右に'\0'

					//ランキングにセット
					DrawString(0, 0, "Ranking", 0xffffff);

					sortSave.setName(9, name);
					sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
					sortSave.SortRanking();		// ランキング並べ替え
					sortSave.SaveRanking();		// ランキングデータの保存

					return 1;   //終了
				}
				else
				{
					//ダメだよ！　　な効果音
				}
			}
		}
	}
	else
	{
		pushFlag = false;          //押されていないよ
	}
	return 0;
}

//入力情報表示
void Scene_InputName::DrawInputInfo()const
{
	if (name[0] == 0)
	{
		//SetDrawBlendMode
		SetFontSize(20);
		DrawString(200 + CENTER_X, 75 + CENTER_Y, "・ ・ 名前を入力 ・ ・", 0xffffff);
	}
	for (int i = 0; name[i] != '\0'; i++)
	{
		SetFontSize(30);
		DrawFormatString((220 + 20 * i) + CENTER_X, 70 + CENTER_Y, 0xffffff, " %c", name[i]);
	}
}

//シーンの変更処理
AbstractScene* Scene_InputName::ChangeScene()
{
	if (KeyBoard_PushA(name) != 1)
	{
		KeyBoard_Update();
	}
	else
	{
		//Scene_sortSave();
		return new Scene_Ranking();

	}
	return this;
}





//初期処理
//void Scene_InputName::KeyBoardInit()
//{
//	//移動量
//	movekeyX = 0;
//	movekeyY = 0;
//	//カーソルの初期位置は「A」
//	PUSH_NOW = KEY_TYPE::NORMAL;
//	//入力文字列　初期化
//	for (int i = 0; i < 10; i++)
//	{
//		InputName[i] = 0;
//	}
//	InputName[9] = '\0';
//	namePos = -1;
//	//削除・確定フラグ
//	PushFlg = FALSE;
//}
////画像読み込み
//int Scene_InputName::LoadImgae()
//{
//	//背景
//	if ((backimage = LoadGraph("images/KeyBoard/back02.png")) == -1) return -1;
//	//キーボード
//	if ((keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png")) == -1) return -1;
//	//分割読み込み　押された/押してない が連結した画像
//	//ノーマルカーソル
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
//	//「×」カーソル
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
//	//「OK」カーソル
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;
//}
////効果音読み込み
//int Scene_InputName::LoadSounds()
//{
//	//if ((SE_push = LoadSoundMem("BGM/SE_Key_push.wav")) == -1) return -1;
//	//if ((SE_cancel = LoadSoundMem("BGM/SE_Key_cancel.wav")) == -1) return -1;
//	//if ((SE_ok = LoadSoundMem("BGM/SE_Key_ok.wav")) == -1) return -1;
//
//	return 0;
//}
////描画
//void Scene_InputName::DrawKeyBoard()
//{
//	//背景
//	DrawGraph(0, 0, backimage, FALSE);
//	//キーボード
//	DrawGraph(45, OUT_HEIGHT, keyboardimage, TRUE);
//	//test
//	//DrawTestInfo();
//	DrawInputInfo();
//	// ノーマル(A～Z,a～z,0～9)・「×」・「ＯＫ」によって画像変化　 switch文で操作
//	// 　　　　　　　　押す・押さないによって画像変化　　　　　　　 画像配列を PushFlg で操作
//	switch (PUSH_NOW)
//	{
//	case KEY_TYPE::NORMAL:    //ノーマルカーソル
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[PushFlg], TRUE);
//		break;
//	case KEY_TYPE::CANCEL:    //「×」カーソル
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[PushFlg], TRUE);
//		break;
//	case KEY_TYPE::DONE:      //「OK」カーソル
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[PushFlg], TRUE);
//		break;
//	default:
//		break;
//	}
//}
////移動
//void Scene_InputName::KeyBoardControl(int NowKey)
//{
//	//フレーム数カウント
//	frame++;
//	//→ 右
//	if (NowKey & PAD_INPUT_RIGHT)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyX++;     //タイミング調整 + 移動
//		}
//		if (movekeyX >= 12) movekeyX = 12;   //右端でストップ
//		PUSH_NOW = KEY_TYPE::NORMAL;         //現在のキーはノーマル
//	}
//	//← 左
//	if (NowKey & PAD_INPUT_LEFT)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyX--;     //タイミング調整 + 移動
//		}
//		if (movekeyX <= 0) movekeyX = 0;     //左端でストップ
//		PUSH_NOW = KEY_TYPE::NORMAL;         //現在のキーはノーマル
//	}
//	//↑ 上
//	if (NowKey & PAD_INPUT_UP)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyY--;     //タイミング調整 + 移動
//		}
//		if (movekeyY <= 0) movekeyY = 0;     //上端でストップ
//		PUSH_NOW = KEY_TYPE::NORMAL;         //現在のキーはノーマル
//	}
//	//↓ 下
//	if (NowKey & PAD_INPUT_DOWN)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyY++;     //タイミング調整 + 移動
//		}
//		PUSH_NOW = KEY_TYPE::NORMAL;         //現在のキーはノーマル
//	}
//	//「×」ボタン   「a～z」段より下 かつ 「9」キーより右側
//	if (movekeyY == 4 && movekeyX >= 10)
//	{
//		movekeyX = 10;                       //ボタンの位置
//		PUSH_NOW = KEY_TYPE::CANCEL;         //現在のキーはキャンセル「×」
//	}
//	//「OK」ボタン   キーボード最下段より下
//	if (movekeyY >= 5)
//	{
//		movekeyX = 4;                        //ボタンの位置
//		movekeyY = 5;
//		PUSH_NOW = KEY_TYPE::DONE;           //現在のキーはDONE「OK」
//	}
//	//Bボタンで確定
//	//testPush_B_Key2(NowKey);
//}
////Aボタンが押された時の処理　引数はrankingで使います
//void Scene_InputName::Push_A_Key(int NowKey, int* GameState, int Score)
//{
//	//"押した瞬間"を判定
//	static int push_B;
//	if (NowKey & PAD_INPUT_A)
//	{
//		push_B++;
//		if (PUSH_NOW == KEY_TYPE::NORMAL)
//		{
//			//"押した瞬間"のみ入力
//			if (push_B >= 1 && push_B < 8)
//			{
//				//B押されたよフラグ　TRUE
//				PushFlg = TRUE;
//				//入力タイミング
//				if (InputControl() == 0)
//				{
//					//SE
//					PlaySoundMem(SE_push, DX_PLAYTYPE_BACK);
//					++namePos;
//					//上限は9文字
//					if (namePos >= 8) namePos = 8;
//					//配列に入力
//					InputName[namePos] = AllStr[movekeyY][movekeyX];
//				}
//			}
//		}
//		else if (PUSH_NOW == KEY_TYPE::CANCEL) //「×」キー上で押して一文字削除
//		{
//			//B押されたよフラグ　TRUE
//			PushFlg = TRUE;
//			//入力タイミング
//			if (InputControl() == 0)
//			{
//				PlaySoundMem(SE_cancel, DX_PLAYTYPE_BACK);
//				InputName[namePos] = 0;
//				//０文字以下にはならない
//				if (namePos >= 0) namePos--;
//			}
//		}
//		else if (PUSH_NOW == KEY_TYPE::DONE)   //「OK」キー上で押して確定（ランキング変数に代入）
//		{
//			//A押されたよフラグ　TRUE
//			PushFlg = TRUE;
//			//入力タイミング
//			if (InputControl() == 0)
//			{
//				//未入力での確定は不可
//				if (InputName[0] != '\0')
//				{
//					//SE
//					PlaySoundMem(SE_ok, DX_PLAYTYPE_BACK);
//					InputName[namePos + 1] = '\0';
//					//ランキング変数へ name・Score を代入 --> 画面遷移
//					//ranking.SetRanking(InputName, GameState, Score);
//				}
//				{
//					//SE 未入力時はカチカチなります
//					PlaySoundMem(SE_push, DX_PLAYTYPE_BACK);
//				}
//			}
//		}
//	}
//	else
//	{
//		if (push_B > 0) push_B = -1;
//		else push_B = 0;
//		PushFlg = FALSE;
//	}
//}
////入力情報表示
//void Scene_InputName::DrawInputInfo()
//{
//	if (InputName[0] == 0)
//	{
//		//SetDrawBlendMode
//		SetFontSize(20);
//		DrawString(200, 125, "・ ・ 名前を入力 ・ ・", 0xffffff);
//	}
//	for (int i = 0; InputName[i] != '\0'; i++)
//	{
//		SetFontSize(30);
//		DrawFormatString(220 + 20 * i, 120, 0xffffff, " %c", InputName[i]);
//	}
//}
////コントローラー調整
//int Scene_InputName::InputControl()
//{
//	int timing = 8;
//	return frame % timing;
//}
////＊test用＊　各種情報表示
//void Scene_InputName::DrawTestInfo()
//{
//	//InputNameチェック
//	//if (InputName[0] == 0) InputName[0] = '|';
//	for (int i = 0; InputName[i] != '\0'; i++)
//	{
//		SetFontSize(20);
//		DrawString(0, 0, "NAME : ", 0xffffff);
//		DrawFormatString(80 + 15 * i, 0, 0xffffff, "%c", InputName[i]);
//	}
//	//PushFlgチェック
//	DrawFormatString(0, 30, 0xffffff, "Push : %s", PushFlg == FALSE ? "押されてない" : "押されてる");
//}