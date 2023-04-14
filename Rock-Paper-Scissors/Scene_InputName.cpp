//#include "Scene_InputName.h"
//#include"Scene_Ranking.h"
//#include <DxLib.h>
//#include "KeyManager.h"
//#include"SortSave.h"
//
//#define CENTER_X 320      //幅  720　用で作ったキーボードを無理やり中心に持ってくる
//#define CENTER_Y 120      //高さ480　　　　　　　　　　不要な時は CENTER_X,Y を0にしてください
//#define ALPHA_MAX 26      //アルファベット総数
//#define OUT_WIDTH 45 + CENTER_X     //画面左端～キーボードまでの幅
//#define OUT_HEIGHT 200 + CENTER_Y    //画面上端～キーボードまでの高さ
//#define SPACE 10          //キー間のスペース
//#define KEY_WIDTH 40      //ノーマルキーの幅
//const int CurStdX = OUT_WIDTH + SPACE + 5;    //カーソルのX座標基準    (「5」はカーソルの幅 ）
//const int CurStdY = OUT_HEIGHT + SPACE + 5;   //カーソルのY座標基準
//
////入力文字    ※わかりやすくするため半分（実際に表示されているキーボードと同じ配置）
//const char AllStr[5][ALPHA_MAX / 2 + 1] = {
//	"ABCDEFGHIJKLM",
//	"NOPQRSTUVWXYZ",
//	"abcdefghijklm",
//	"nopqrstuvwxyz",
//	"0123456789"
//};
//
//Scene_InputName::Scene_InputName()
//{
//	KeyBoardInit();
//	LoadKeyBoardImgaes();
//}
//
///*コンストラクタ*/
////virtual ~Scene_InputName() {};
//
//char name[11];
//
////更新
//void Scene_InputName::Update()
//{
//
//}
//
////描画
//void Scene_InputName::Draw()const
//{
//	KeyBoard_Draw();
//}
//
////初期処理
//void Scene_InputName::KeyBoardInit()
//{
//	//カーソルの初期位置は"A"
//	movekeyX = 0;             //ｘ方向0番目
//	movekeyY = 0;             //ｙ方向1番目
//
//	//カーソルの初期位置は「A」なのでノーマル
//	CURSOR_NOW = CURSOR_TYPE::NORMAL;
//
//	//入力文字列　初期化
//	for (int i = 0; i < 10; i++)
//	{
//		InputName[i] = 0;
//	}
//	InputName[10] = '\0';     //配列の一番最後に"\0"(終端の目印)を入れておく
//	input_Pos = -1;           //
//	pushFlag = FALSE;         //最初はAボタンは押されていない
//}
//
////画像読み込み
//int Scene_InputName::LoadKeyBoardImgaes()
//{
//	//背景
//	if ((backimage = LoadGraph("images/KeyBoard/back02.png")) == -1) return -1;
//	//キーボード
//	if ((keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png")) == -1) return -1;
//	//分割読み込み　押したよ/押してない が連結した画像
//	//ノーマルカーソル
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
//	//「×」カーソル
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
//	//「OK」カーソル
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;
//	return 0;
//}
//
////効果音読み込み
////int Scene_InputName::LoadSounds()
////{
//
////}
//
////描画
//void Scene_InputName::KeyBoard_Draw()const
//{
//	//背景
//	DrawGraph(320, 120, backimage, FALSE);
//
//	//キーボード
//	DrawGraph(45 + CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);
//
//	// ノーマル(A～Z,a～z,0～9)・「×」・「ＯＫ」によって画像変化　 switch文で操作
//	// 　　　　　　　　押す・押さないによって画像変化　　　　　　　 画像配列を PushFlg で操作
//	//画像配列の 0番目 は「押していない」カーソル　　1番目は 「押している」カーソル
//	switch (CURSOR_NOW)
//	{
//	case CURSOR_TYPE::NORMAL:    //ノーマルカーソル
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[pushFlag], TRUE);
//		break;
//	case CURSOR_TYPE::CANCEL:    //「×」カーソル
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[pushFlag], TRUE);
//		break;
//	case CURSOR_TYPE::DONE:      //「OK」カーソル
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[pushFlag], TRUE);
//		break;
//	default:
//		break;
//	}
//	//入力中の文字を表示
//	DrawInputInfo();
//}
//
////更新
//void Scene_InputName::KeyBoard_Update()
//{
//	//フレーム数カウント
//	frame++;
//
//	//→ 右
//	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyX++;     //タイミング調整 + 移動
//		}
//		if (movekeyX > 12) movekeyX = 0;   //右端以上で左端へ
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;  //現在のキーはノーマル
//	}
//	//← 左
//	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyX--;     //タイミング調整 + 移動
//		}
//		if (movekeyX < 0) movekeyX = 12;     //左端以上で右端へ
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;    //現在のキーはノーマル
//	}
//	//↑ 上
//	if (KeyManager::OnPadPressed(PAD_INPUT_UP))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyY--;     //タイミング調整 + 移動
//		}
//		if (movekeyY <= 0) movekeyY = 0;     //上端でストップ
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //現在のキーはノーマル
//	}
//	//↓ 下
//	if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyY++;     //タイミング調整 + 移動
//		}
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //現在のキーはノーマル
//	}
//	//「×」ボタン   「a～z」段より下 かつ 「9」キーより右側
//	if (movekeyY == 4 && movekeyX >= 10)
//	{
//		movekeyX = 10;                       //ボタンの位置
//		CURSOR_NOW = CURSOR_TYPE::CANCEL;         //現在のキーはキャンセル「×」
//	}
//	//「OK」ボタン   キーボード最下段より下
//	if (movekeyY >= 5)
//	{
//		movekeyX = 4;                        //ボタンの位置
//		movekeyY = 5;
//		CURSOR_NOW = CURSOR_TYPE::DONE;           //現在のキーはDONE「OK」
//	}
//}
//
////カーソルの移動・ボタンの長押しを調整
//bool Scene_InputName::CursorControl()
//{
//	int timing = 8;
//	if (frame % timing == 0) return true;
//	//frame = 0;
//	return false;
//}
//
////Aボタンが押された時の処理  入力が終わると 1 が返ってくる
//int Scene_InputName::KeyBoard_PushA(char* name)       //keyflg　 は"押された瞬間"キー
//{
//	//　Aボタンを押している間
//	if (KeyManager::OnPadPressed(PAD_INPUT_A))
//	{
//		//長押しでの連続入力のタイミングを調整（PCのような）
//		if (CursorControl() == true)
//		{
//			// "A～Z","a～z","1～9"の上で押された
//			if (CURSOR_NOW == CURSOR_TYPE::NORMAL)
//			{
//				pushFlag = true;        //押されているよ
//				++input_Pos;            //入力位置を一つ右に
//
//				//上限は10文字   （配列の0～9）
//				if (input_Pos > 9) input_Pos = 9;
//
//				//文字配列に入力
//				InputName[input_Pos] = AllStr[movekeyY][movekeyX];
//			}
//			else if (CURSOR_NOW == CURSOR_TYPE::CANCEL)                  //「×」キーの上で押された　一文字削除
//			{
//				pushFlag = true;        //押されているよ
//
//				//一文字でも入力されていれば一文字消す
//				if (InputName[input_Pos] != 0) InputName[input_Pos] = 0; //0 は何も入力されていない状態
//				input_Pos--;            //入力位置を一つ左に
//
//				//入力位置は最低-1まで
//				if (input_Pos < -1) input_Pos = -1;
//			}
//			else if (CURSOR_NOW == CURSOR_TYPE::DONE)                  //「OK」キーの上で押された　確定
//			{
//				//一文字も入力されていない場合は確定できない
//				if (InputName[input_Pos] != 0)
//				{
//					//一文字でも入力アリ
//					InputName[input_Pos + 1] = '\0';       //最後の文字の一つ右に'\0'
//
//					//ランキングにセット
//					DrawString(0, 0, "Ranking", 0xffffff);
//
//					return 1;   //終了
//				}
//				else
//				{
//					//ダメだよ！　　な効果音
//				}
//			}
//		}
//	}
//	else
//	{
//		pushFlag = false;          //押されていないよ
//	}
//	return 0;
//}
//
////入力情報表示
//void Scene_InputName::DrawInputInfo()const
//{
//	if (InputName[0] == 0)
//	{
//		//SetDrawBlendMode
//		SetFontSize(20);
//		DrawString(200 + CENTER_X, 125 + CENTER_Y, "・ ・ 名前を入力 ・ ・", 0xffffff);
//	}
//	for (int i = 0; InputName[i] != '\0'; i++)
//	{
//		SetFontSize(30);
//		DrawFormatString((220 + 20 * i) + CENTER_X, 120 + CENTER_Y, 0xffffff, " %c", InputName[i]);
//	}
//}
//
////シーンの変更処理
//AbstractScene* Scene_InputName::ChangeScene()
//{
//	//if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
//	if (KeyBoard_PushA(name) != 1)
//	{
//		KeyBoard_Update();
//	}
//	else
//	{
//		return dynamic_cast<AbstractScene*>(new SortSave(name));
//
//	}
//	return this;
//}
//
//int Scene_InputName::GetName()
//{
//	for (int j = 0; '\0' != InputName[j]; j++)
//	{
//		return InputName[j];
//	}
//}