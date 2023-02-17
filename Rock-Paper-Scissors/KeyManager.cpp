#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];     //�O��̓���
char KeyManager::nowKey[256];     //����̓���

int KeyManager::oldMouse;         //�O��̃}�E�X����
int KeyManager::nowMouse;         //����̃}�E�X����

int KeyManager::oldKey_Pad;         //�O��̓��́i�R���g���[���[
int KeyManager::nowKey_Pad;         //����̓��́i�R���g���[���[
XINPUT_STATE KeyManager::input_Pad;      //Pad�̓��͏��

//�X�V
void KeyManager::Update()
{
	for (int i = 0; i < 256; i++)
	{
		oldKey[i] = nowKey[i];  //�O�t���[���̓���
	}

	//���ׂẴL�[�̂̓��͏�Ԃ��擾
	if (GetHitKeyStateAll(nowKey) == -1) throw - 1;

	//�}�E�X�̓��͏�Ԃ��擾
	oldMouse = nowMouse;
	nowMouse = GetMouseInput();

	//�L�[(�R���g���[���[)���͎擾 
	oldKey_Pad = nowKey_Pad;
	nowKey_Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);   //DX_INPUT_PAD1  �ɂ���΃R���g���[���[�̂�(?)

	//�R���g���[���[���͏��
	SetJoypadDeadZone(DX_INPUT_KEY_PAD1,0.5);
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input_Pad);
}

/*****************************  �L�[�{�[�h  *****************************/

//�������u��
bool KeyManager::OnKeyClicked(int key)
{
	//���t���[��������Ă��Ȃ�        �@�@�@�@�@�@�@
	bool ret = (nowKey[key] == 1) && (oldKey[key] != 1);   //������Ă��Ȃ� �� 0
	return ret;
}

//�������u��
bool KeyManager::OnKeyReleased(int key)
{
	//          ���͉�����Ă��Ȃ��@  �O�͉�����Ă���
	bool ret = (nowKey[key] != 1) && (oldKey[key] == 1);
	return ret;
}

//�����Ă����
bool KeyManager::OnKeyPressed(int key)
{
	//
	bool ret = (nowKey[key] == 1);
	return ret;
}

/************************************************************************/



/*****************************  �}�E�X����  *****************************/

//�������u�� (�m�F����L�[)
bool KeyManager::OnMouseClicked(int key)
{
	//���t���[��������Ă��Ȃ�        �@�@�@�@�@�@�@
	bool ret = (nowMouse & key) && (~oldMouse & key);
	return ret;
}

//�������u��
bool KeyManager::OnMouseReleased(int key)
{
	//          ���͉�����Ă��Ȃ��@  �O�͉�����Ă���
	bool ret = (~nowMouse & key) && (oldMouse & key);
	return ret;
}

//�����Ă����
bool KeyManager::OnMousePressed(int key)
{
	bool ret = (nowMouse & key);
	return ret;
}

/************************************************************************/




/*****************************  �R���g���[���[  *****************************/

//�������u�� (�m�F����L�[)
bool KeyManager::OnPadClicked(int key)

{
	//���t���[��������Ă��Ȃ�        �@�@�@�@�@�@�@
	bool ret = (nowKey_Pad & key) && (~oldKey_Pad & key);
	return ret;
}

//�������u��
bool KeyManager::OnPadReleased(int key)
{
	//          ���͉�����Ă��Ȃ��@  �O�͉�����Ă���
	bool ret = (~nowKey_Pad & key) && (oldKey_Pad & key);
	return ret;
}

//�����Ă����
bool KeyManager::OnPadPressed(int key)
{
	bool ret = (nowKey_Pad & key);
	return ret;
}


//pad�̓��͏��擾
XINPUT_STATE KeyManager::GetPadInputState()
{
	return input_Pad;//.ThumbRX;
	
}

/****************************************************************************/