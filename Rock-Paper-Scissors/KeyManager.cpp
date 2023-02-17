#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];     //前回の入力
char KeyManager::nowKey[256];     //今回の入力

int KeyManager::oldMouse;         //前回のマウス入力
int KeyManager::nowMouse;         //今回のマウス入力

int KeyManager::oldKey_Pad;         //前回の入力（コントローラー
int KeyManager::nowKey_Pad;         //今回の入力（コントローラー
XINPUT_STATE KeyManager::input_Pad;      //Padの入力情報

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

	//コントローラー入力情報
	SetJoypadDeadZone(DX_INPUT_KEY_PAD1,0.5);
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input_Pad);
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

/****************************************************************************/