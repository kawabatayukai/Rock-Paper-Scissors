#pragma once
#include<iostream>

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();

	void Update();
	void Draw() const;

	//Aボタンが押された時の処理  入力が終わると 1 が返ってくる
	int KeyBoard_PushA();       //keyflg　 は"押された瞬間"キー

	//入力情報表示
	void DrawInputInfo() const;

private:

	//キーの種類
	enum class _KEY_TYPE
	{
		NORMAL,     // A～B,a～b,1～9
		CANCEL,     //「×」(ひとつ消す)
		DONE,       //「OK」(確定)
	};
	_KEY_TYPE KeyType;     //キーの種類

	int num_x;             //キー配列x番目
	int num_y;             //キー配列y番目

	int frame;             //フレームをカウント(左右上下移動連続入力調整用)
	int frame_CL;          //フレームをカウント(一文字削除連続入力調整用)

	std::string input_str;          //入力文字列
	static int font_input;          //入力表示用フォント

	bool isStartKey;                //開幕Aが押されている状態防止
	bool isPushA = false;           //Aボタンが押されているか(画像変化用)

	//--------------------- image -------------------------
	int image_back;        //背景
	int image_key;         //キーボード
	int image_cur_NL[2];   //ノーマルカーソル
	int image_cur_CL[2];   //キャンセルカーソル
	int image_cur_DN[2];   //確定カーソル
	int image_button[2];   //START,Bボタン
	int image_inputSpace;  //入力欄

	//--------------------- sound -------------------------
	int se_normalkey;      //ノーマル
	int se_cancelkey;      //一文字削除
	int se_donekey;        //OK
};