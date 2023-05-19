#pragma once
#include<iostream>


//キーの種類
enum class _CURSOR_TYPE
{
	NONE = 0,   // 入力0（なにも押されていない）
	NORMAL,     // A～B,a～b,1～9
	CANCEL,     //「×」(ひとつ消す)
	DONE,       //「OK」(確定)

	MISS = 99
};

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();

	void Update();
	void Draw() const;

	//カーソルの移動・ボタンの長押しを調整
	bool CursorControl();

	//Aボタンが押された時の処理  入力が終わると 1 が返ってくる
	int KeyBoard_PushA();       //keyflg　 は"押された瞬間"キー

	//入力情報表示
	void DrawInputInfo() const;

private:
	int backimage;        //背景画像
	int keyboardimage;    //キーボード画像
	int Cursorimage[2];   //ノーマルカーソル画像  0 : 通常時　　1 : 押されたとき
	int Cancelimage[2];   //  「×」カーソル画像
	int OKimage[2];       //  「OK」カーソル画像

	bool isPushA = false;           //Aが　押されている/押されてない フラグ    TRUE:押されている　FALSE:押されていない
	int frame = 0;                  //フレームをカウント
	int movekeyX = 0;               //移動量   (キーボード〇番目)
	int movekeyY = 0;
	_CURSOR_TYPE CURSOR_NOW;        //現在のカーソル
	std::string input_str;          //入力文字列
	static int font_input;          //入力表示用フォント
};