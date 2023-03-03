#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];     //前回の入力
char KeyManager::nowKey[256];     //今回の入力

int KeyManager::oldMouse;         //前回のマウス入力
int KeyManager::nowMouse;         //今回のマウス入力

int KeyManager::oldKey_Pad;       //前回の入力（コントローラー
int KeyManager::nowKey_Pad;       //今回の入力（コントローラー

//---------   コントローラー（スティック入力値） ------------------------

XINPUT_STATE KeyManager::input_Pad;    //コントローラーの入力情報
int KeyManager::stick_value[4];        //入力値   0:左ｘ　1:左ｙ　2:右ｘ　3:右ｙ

//左スティック
short KeyManager::stickLX_DeadZoneMAX = 20000;       //無効範囲最大値　x方向
short KeyManager::stickLX_DeadZoneMIN = -20000;      //無効範囲最小値　x方向
short KeyManager::stickLY_DeadZoneMAX = 20000;       //無効範囲最大値　y方向
short KeyManager::stickLY_DeadZoneMIN = -20000;      //無効範囲最小値　y方向

//右スティック
short KeyManager::stickRX_DeadZoneMAX = 20000;       //無効範囲最大値　x方向
short KeyManager::stickRX_DeadZoneMIN = -20000;      //無効範囲最小値　x方向
short KeyManager::stickRY_DeadZoneMAX = 20000;       //無効範囲最大値　y方向
short KeyManager::stickRY_DeadZoneMIN = -20000;      //無効範囲最小値　y方向

//-----------------------------------------------------------------------

//更新
void KeyManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];  //前フレームの入力
	}

	//すべてのキーのの入力状態を取得
	if (GetHitKeyStateAll(nowKey) == -1) throw - 1;

	//マウスの入力状態を取得
	oldMouse = nowMouse;
	nowMouse = GetMouseInput();

	//キー(コントローラー)入力取得 
	oldKey_Pad = nowKey_Pad;
	nowKey_Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);   //DX_INPUT_PAD1  にすればコントローラーのみ(?)

	// 入力状態を取得
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input_Pad);

	//スティック入力関係 ---------------------------------------------------
	{
		//スティックのデッドゾーンを考慮した入力数値を取得（デッドゾーンは受け付けない値

		// 左スティック左右   入力値がデッドゾーン外
		if (input_Pad.ThumbLX > stickLX_DeadZoneMAX || input_Pad.ThumbLX < stickLX_DeadZoneMIN)
		{
			stick_value[Stick_Code::LEFT_STICK_X] = input_Pad.ThumbLX;
		}
		else
		{
			// 入力値がデッドゾーン内なら受け付けない
			if (stick_value[Stick_Code::LEFT_STICK_X] != 0) stick_value[Stick_Code::LEFT_STICK_X] = 0;
		}

		// 左スティック上下   入力値がデッドゾーン外
		if (input_Pad.ThumbLY > stickLY_DeadZoneMAX || input_Pad.ThumbLY < stickLY_DeadZoneMIN)
		{
			stick_value[Stick_Code::LEFT_STICK_Y] = input_Pad.ThumbLY;
		}
		else
		{
			// 入力値がデッドゾーン内なら受け付けない
			if (stick_value[Stick_Code::LEFT_STICK_Y] != 0) stick_value[Stick_Code::LEFT_STICK_Y] = 0;
		}



		// 右スティック左右   入力値がデッドゾーン外
		if (input_Pad.ThumbRX > stickRX_DeadZoneMAX || input_Pad.ThumbRX < stickRX_DeadZoneMIN)
		{
			stick_value[Stick_Code::RIGHT_STICK_X] = input_Pad.ThumbRX;
		}
		else
		{
			// 入力値がデッドゾーン内なら受け付けない
			if (stick_value[Stick_Code::RIGHT_STICK_X] != 0) stick_value[Stick_Code::RIGHT_STICK_X] = 0;
		}

		// 右スティック上下   入力値がデッドゾーン外
		if (input_Pad.ThumbRY > stickRY_DeadZoneMAX || input_Pad.ThumbRY < stickRY_DeadZoneMIN)
		{
			stick_value[Stick_Code::RIGHT_STICK_Y] = input_Pad.ThumbRY;
		}
		else
		{
			// 入力値がデッドゾーン内なら受け付けない
			if (stick_value[Stick_Code::RIGHT_STICK_Y] != 0) stick_value[Stick_Code::RIGHT_STICK_Y] = 0;
		}

	}
	// ---------------------------------------------------------------------

}

/*****************************  キーボード  *****************************/

//押した瞬間
bool KeyManager::OnKeyClicked(int key)
{
	//毎フレーム押されていない        　　　　　　　
	bool ret = (nowKey[key] == 1) && (oldKey[key] != 1);   //押されていない → 0
	return ret;
}

//離した瞬間
bool KeyManager::OnKeyReleased(int key)
{
	//          今は押されていない　  前は押されていた
	bool ret = (nowKey[key] != 1) && (oldKey[key] == 1);
	return ret;
}

//押している間
bool KeyManager::OnKeyPressed(int key)
{
	//
	bool ret = (nowKey[key] == 1);
	return ret;
}

/************************************************************************/



/*****************************  マウス入力  *****************************/

//押した瞬間 (確認するキー)
bool KeyManager::OnMouseClicked(int key)
{
	//毎フレーム押されていない        　　　　　　　
	bool ret = (nowMouse & key) && (~oldMouse & key);
	return ret;
}

//離した瞬間
bool KeyManager::OnMouseReleased(int key)
{
	//          今は押されていない　  前は押されていた
	bool ret = (~nowMouse & key) && (oldMouse & key);
	return ret;
}

//押している間
bool KeyManager::OnMousePressed(int key)
{
	bool ret = (nowMouse & key);
	return ret;
}

/************************************************************************/




/*****************************  コントローラー  *****************************/

//押した瞬間 (確認するキー)
bool KeyManager::OnPadClicked(int key)

{
	//毎フレーム押されていない        　　　　　　　
	bool ret = (nowKey_Pad & key) && (~oldKey_Pad & key);
	return ret;
}

//離した瞬間
bool KeyManager::OnPadReleased(int key)
{
	//          今は押されていない　  前は押されていた
	bool ret = (~nowKey_Pad & key) && (oldKey_Pad & key);
	return ret;
}

//押している間
bool KeyManager::OnPadPressed(int key)
{
	bool ret = (nowKey_Pad & key);
	return ret;
}


//padの入力情報取得
XINPUT_STATE KeyManager::GetPadInputState()
{
	return input_Pad;//.ThumbRX;
	
}

//スティック入力値取得
int  KeyManager::Get_StickValue(const int& stick_code)
{
	return stick_value[stick_code];
}

/****************************************************************************/