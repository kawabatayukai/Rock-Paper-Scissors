#pragma once
#include"DxLib.h"

//コントローラースティックの識別番号
namespace Stick_Code
{
	const int LEFT_STICK_X = 0;            //左スティックｘ方向
	const int LEFT_STICK_Y = 1;            //左スティックｙ方向
	const int RIGHT_STICK_X = 2;           //右スティックｘ方向
	const int RIGHT_STICK_Y = 3;           //右スティックｙ方向

	const int STICK_MAX_VALUE = 32767;     //スティック入力最大値
	const int STICK_MIN_VALUE = -32768;    //スティック入力最小値
};


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

	static int  Get_StickValue(const int& stick_code);  //スティック入力値取得

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

	//---------   コントローラー（スティック入力値） ------------------------

	static XINPUT_STATE input_Pad;      //コントローラーの入力情報
	static int stick_value[4];          //入力値   0:左ｘ　1:左ｙ　2:右ｘ　3:右ｙ


	//無効範囲(デッドゾーン)・・・入力を受け付けない値
	
	//左スティック
	static short stickLX_DeadZoneMAX;   //無効範囲最大値　x方向
	static short stickLX_DeadZoneMIN;   //無効範囲最小値　x方向
	static short stickLY_DeadZoneMAX;   //無効範囲最大値　y方向
	static short stickLY_DeadZoneMIN;   //無効範囲最小値　y方向

	//右スティック
	static short stickRX_DeadZoneMAX;   //無効範囲最大値　x方向
	static short stickRX_DeadZoneMIN;   //無効範囲最小値　x方向
	static short stickRY_DeadZoneMAX;   //無効範囲最大値　y方向
	static short stickRY_DeadZoneMIN;   //無効範囲最小値　y方向

	//-----------------------------------------------------------------------
};
