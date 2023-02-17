#pragma once
#include"DxLib.h"

class KeyManager
{
public:
	static void Update();

	//キーボード
	static bool OnKeyClicked(int key);       //押した瞬間 (確認するキー)
	static bool OnKeyReleased(int key);      //離した瞬間
	static bool OnKeyPressed(int key);       //押している間

	//マウス
	static bool OnMouseClicked(int key);     //押した瞬間 (確認するキー)
	static bool OnMouseReleased(int key);    //離した瞬間
	static bool OnMousePressed(int key);     //押している間

	//コントローラー
	static bool OnPadClicked(int key);       //押した瞬間 (確認するキー)
	static bool OnPadReleased(int key);      //離した瞬間
	static bool OnPadPressed(int key);       //押している間

	static XINPUT_STATE GetPadInputState();  //pad入力情報取得

private:
	//privateにコンストラクタ→アクセスできない（オブジェクトが作れない）
	KeyManager() = default;

private:
	static char oldKey[256];     //前回の入力
	static char nowKey[256];     //今回の入力

	static int oldMouse;         //前回のマウス入力
	static int nowMouse;         //今回のマウス入力

	static int oldKey_Pad;       //前回の入力（コントローラー
	static int nowKey_Pad;       //今回の入力（コントローラー
	static XINPUT_STATE input_Pad;      //コントローラーの入力情報
};


//PAD_INPUT_DOWN　	// ↓チェックマスク(下キー or テンキーの２キー)
//PAD_INPUT_LEFT　	// ←チェックマスク(左キー or テンキーの４キー)
//PAD_INPUT_RIGHT　	// →チェックマスク(右キー or テンキーの６キー)
//PAD_INPUT_UP　	// ↑チェックマスク(上キー or テンキーの８キー)
//PAD_INPUT_1　	// 1ボタンチェックマスク(Ｚキー)
//PAD_INPUT_2　	// 2ボタンチェックマスク(Ｘキー)
//PAD_INPUT_3　	// 3ボタンチェックマスク(Ｃキー)
//PAD_INPUT_4　	// 4ボタンチェックマスク(Ａキー)
//PAD_INPUT_5　	// 5ボタンチェックマスク(Ｓキー)
//PAD_INPUT_6　	// 6ボタンチェックマスク(Ｄキー)
//PAD_INPUT_7　	// 7ボタンチェックマスク(Ｑキー)
//PAD_INPUT_8　	// 8ボタンチェックマスク(Ｗキー)
//PAD_INPUT_9　	// 9ボタンチェックマスク(ＥＳＣキー)
//PAD_INPUT_10　	// 10ボタンチェックマスク(スペースキー)
