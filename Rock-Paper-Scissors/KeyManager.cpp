#include"DxLib.h"
#include "KeyManager.h"

char KeyManager::oldKey[256];     //�O��̓���
char KeyManager::nowKey[256];     //����̓���

int KeyManager::oldMouse;         //�O��̃}�E�X����
int KeyManager::nowMouse;         //����̃}�E�X����

int KeyManager::oldKey_Pad;       //�O��̓��́i�R���g���[���[
int KeyManager::nowKey_Pad;       //����̓��́i�R���g���[���[

//---------   �R���g���[���[�i�X�e�B�b�N���͒l�j ------------------------

XINPUT_STATE KeyManager::input_Pad;    //�R���g���[���[�̓��͏��
int KeyManager::stick_value[4];        //���͒l   0:�����@1:�����@2:�E���@3:�E��

//���X�e�B�b�N
short KeyManager::stickLX_DeadZoneMAX = 20000;       //�����͈͍ő�l�@x����
short KeyManager::stickLX_DeadZoneMIN = -20000;      //�����͈͍ŏ��l�@x����
short KeyManager::stickLY_DeadZoneMAX = 20000;       //�����͈͍ő�l�@y����
short KeyManager::stickLY_DeadZoneMIN = -20000;      //�����͈͍ŏ��l�@y����

//�E�X�e�B�b�N
short KeyManager::stickRX_DeadZoneMAX = 20000;       //�����͈͍ő�l�@x����
short KeyManager::stickRX_DeadZoneMIN = -20000;      //�����͈͍ŏ��l�@x����
short KeyManager::stickRY_DeadZoneMAX = 20000;       //�����͈͍ő�l�@y����
short KeyManager::stickRY_DeadZoneMIN = -20000;      //�����͈͍ŏ��l�@y����

//-----------------------------------------------------------------------

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

	// ���͏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input_Pad);

	//�X�e�B�b�N���͊֌W ---------------------------------------------------
	{
		//�X�e�B�b�N�̃f�b�h�]�[�����l���������͐��l���擾�i�f�b�h�]�[���͎󂯕t���Ȃ��l

		// ���X�e�B�b�N���E   ���͒l���f�b�h�]�[���O
		if (input_Pad.ThumbLX > stickLX_DeadZoneMAX || input_Pad.ThumbLX < stickLX_DeadZoneMIN)
		{
			stick_value[Stick_Code::LEFT_STICK_X] = input_Pad.ThumbLX;
		}
		else
		{
			// ���͒l���f�b�h�]�[�����Ȃ�󂯕t���Ȃ�
			if (stick_value[Stick_Code::LEFT_STICK_X] != 0) stick_value[Stick_Code::LEFT_STICK_X] = 0;
		}

		// ���X�e�B�b�N�㉺   ���͒l���f�b�h�]�[���O
		if (input_Pad.ThumbLY > stickLY_DeadZoneMAX || input_Pad.ThumbLY < stickLY_DeadZoneMIN)
		{
			stick_value[Stick_Code::LEFT_STICK_Y] = input_Pad.ThumbLY;
		}
		else
		{
			// ���͒l���f�b�h�]�[�����Ȃ�󂯕t���Ȃ�
			if (stick_value[Stick_Code::LEFT_STICK_Y] != 0) stick_value[Stick_Code::LEFT_STICK_Y] = 0;
		}



		// �E�X�e�B�b�N���E   ���͒l���f�b�h�]�[���O
		if (input_Pad.ThumbRX > stickRX_DeadZoneMAX || input_Pad.ThumbRX < stickRX_DeadZoneMIN)
		{
			stick_value[Stick_Code::RIGHT_STICK_X] = input_Pad.ThumbRX;
		}
		else
		{
			// ���͒l���f�b�h�]�[�����Ȃ�󂯕t���Ȃ�
			if (stick_value[Stick_Code::RIGHT_STICK_X] != 0) stick_value[Stick_Code::RIGHT_STICK_X] = 0;
		}

		// �E�X�e�B�b�N�㉺   ���͒l���f�b�h�]�[���O
		if (input_Pad.ThumbRY > stickRY_DeadZoneMAX || input_Pad.ThumbRY < stickRY_DeadZoneMIN)
		{
			stick_value[Stick_Code::RIGHT_STICK_Y] = input_Pad.ThumbRY;
		}
		else
		{
			// ���͒l���f�b�h�]�[�����Ȃ�󂯕t���Ȃ�
			if (stick_value[Stick_Code::RIGHT_STICK_Y] != 0) stick_value[Stick_Code::RIGHT_STICK_Y] = 0;
		}

	}
	// ---------------------------------------------------------------------

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

//�X�e�B�b�N���͒l�擾
int  KeyManager::Get_StickValue(const int& stick_code)
{
	return stick_value[stick_code];
}

/****************************************************************************/