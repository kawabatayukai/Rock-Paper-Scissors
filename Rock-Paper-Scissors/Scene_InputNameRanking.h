#pragma once
#include "AbstractScene.h"

//キーの種類
enum class CURSOR_TYPE
{
	NONE = 0,   // 入力0（なにも押されていない）
	NORMAL,     // A～B,a～b,1～9
	CANCEL,     //「×」(ひとつ消す)
	DONE,       //「OK」(確定)
	MISS = 99
};

class Scene_InputNameRanking : public AbstractScene
{
public:
	Scene_InputNameRanking();

	/*コンストラクタ*/
	virtual ~Scene_InputNameRanking() {};

	char name[11];

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;

	//初期処理
	void KeyBoardInit();

	//画像読み込み
	int LoadKeyBoardImgaes();

	//効果音読み込み
	//int LoadSounds();

	//描画
	void KeyBoard_Draw()const;

	//更新
	void KeyBoard_Update();
	//カーソルの移動・ボタンの長押しを調整
	bool CursorControl();

	//Aボタンが押された時の処理  入力が終わると 1 が返ってくる
	int KeyBoard_PushA(char* name);       //keyflg　 は"押された瞬間"キー

	//入力情報表示
	void DrawInputInfo()const;

	int GetName();

private:

	/************* 変数 *************/
	int backimage = 0;            //背景画像
	int keyboardimage = 0;        //キーボード画像
	int Cursorimage[2] = { 0 };   //ノーマルカーソル画像  0 : 通常時　　1 : 押されたとき
	int Cancelimage[2] = { 0 };   //  「×」カーソル画像
	int OKimage[2] = { 0 };       //  「OK」カーソル画像
	///////////////////////////////////////////////////////////////////////////////////////
	bool pushFlag = false;           //Aが　押されている/押されてない フラグ    TRUE:押されている　FALSE:押されていない
	int frame = 0;                   //フレームをカウント
	//移動量   (キーボード〇番目)
	int movekeyX = 0;
	int movekeyY = 0;
	CURSOR_TYPE CURSOR_NOW = CURSOR_TYPE::NORMAL;  //現在のカーソル
	//char InputName[11];              //入力した文字が入る配列 0～9に文字(10文字ﾏﾃﾞ)　10番目には \0 です
	int input_Pos;                   //入力中の配列の〇番目
	/********************************/



//	//初期処理
//	void KeyBoardInit();
//	//画像読み込み
//	int LoadImgae();
//	//効果音読み込み
//	int LoadSounds();
//	//描画
//	void DrawKeyBoard();
//	//移動
//	void KeyBoardControl(int NowKey);
//	//Aボタンが押された時の処理
//	void Push_A_Key(int NowKey, int* GameState, int Score);
//	//入力情報表示
//	void DrawInputInfo();
//	//コントローラー調整
//	int InputControl();
//	//＊test用＊　各種情報表示
//	void DrawTestInfo();
//
//private:
//	/*--------------------　UI　--------------------*/
//	//背景画像
//	int backimage = 0;
//	//キーボード画像
//	int keyboardimage = 0;
//	//ノーマルカーソル画像  0 : 通常時　　1 : 押されたとき
//	int Cursorimage[2] = { 0 };
//	//「×」カーソル画像
//	int Cancelimage[2] = { 0 };
//	//「OK」カーソル画像
//	int OKimage[2] = { 0 };
//	//SE
//	int SE_push = 0;   //通常入力
//	int SE_cancel = 0; //「×」
//	int SE_ok = 0;     //「ok」
//	//移動量
//	int movekeyX = 0;
//	int movekeyY = 0;
//	//キーの状態を保持
//	KEY_TYPE PUSH_NOW;
//	/*------------------------------------------------*/
//
//	/*--------------------　他　----------------------*/
//		//フレームをカウント
//	int frame = 0;
//	//入力情報
//	char InputName[10];
//	//InputName用
//	int namePos;
//	//Bが　押されている/押されてない フラグ    TRUE:押されている　FALSE:押されていない
//	bool PushFlg;
//	/*------------------------------------------------*/
};

