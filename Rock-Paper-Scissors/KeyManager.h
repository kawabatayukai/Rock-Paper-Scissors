#pragma once
#include"DxLib.h"

//�R���g���[���[�X�e�B�b�N�̎��ʔԍ�
namespace Stick_Code
{
	const int LEFT_STICK_X = 0;            //���X�e�B�b�N������
	const int LEFT_STICK_Y = 1;            //���X�e�B�b�N������
	const int RIGHT_STICK_X = 2;           //�E�X�e�B�b�N������
	const int RIGHT_STICK_Y = 3;           //�E�X�e�B�b�N������

	const int STICK_MAX_VALUE = 32767;     //�X�e�B�b�N���͍ő�l
	const int STICK_MIN_VALUE = -32768;    //�X�e�B�b�N���͍ŏ��l
};


class KeyManager
{
public:
	static void Update();

	//�L�[�{�[�h
	static bool OnKeyClicked(int key);       //�������u�� (�m�F����L�[)
	static bool OnKeyReleased(int key);      //�������u��
	static bool OnKeyPressed(int key);       //�����Ă����

	//�}�E�X
	static bool OnMouseClicked(int key);     //�������u�� (�m�F����L�[)
	static bool OnMouseReleased(int key);    //�������u��
	static bool OnMousePressed(int key);     //�����Ă����

	//�R���g���[���[
	static bool OnPadClicked(int key);       //�������u�� (�m�F����L�[)
	static bool OnPadReleased(int key);      //�������u��
	static bool OnPadPressed(int key);       //�����Ă����

	static int  Get_StickValue(const int& stick_code);  //�X�e�B�b�N���͒l�擾

private:
	//private�ɃR���X�g���N�^���A�N�Z�X�ł��Ȃ��i�I�u�W�F�N�g�����Ȃ��j
	KeyManager() = default;

private:
	static char oldKey[256];     //�O��̓���
	static char nowKey[256];     //����̓���

	static int oldMouse;         //�O��̃}�E�X����
	static int nowMouse;         //����̃}�E�X����

	static int oldKey_Pad;       //�O��̓��́i�R���g���[���[
	static int nowKey_Pad;       //����̓��́i�R���g���[���[

	//---------   �R���g���[���[�i�X�e�B�b�N���͒l�j ------------------------

	static XINPUT_STATE input_Pad;      //�R���g���[���[�̓��͏��
	static int stick_value[4];          //���͒l   0:�����@1:�����@2:�E���@3:�E��


	//�����͈�(�f�b�h�]�[��)�E�E�E���͂��󂯕t���Ȃ��l
	
	//���X�e�B�b�N
	static short stickLX_DeadZoneMAX;   //�����͈͍ő�l�@x����
	static short stickLX_DeadZoneMIN;   //�����͈͍ŏ��l�@x����
	static short stickLY_DeadZoneMAX;   //�����͈͍ő�l�@y����
	static short stickLY_DeadZoneMIN;   //�����͈͍ŏ��l�@y����

	//�E�X�e�B�b�N
	static short stickRX_DeadZoneMAX;   //�����͈͍ő�l�@x����
	static short stickRX_DeadZoneMIN;   //�����͈͍ŏ��l�@x����
	static short stickRY_DeadZoneMAX;   //�����͈͍ő�l�@y����
	static short stickRY_DeadZoneMIN;   //�����͈͍ŏ��l�@y����

	//-----------------------------------------------------------------------
};
