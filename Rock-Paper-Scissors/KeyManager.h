#pragma once
#include"DxLib.h"

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

	static XINPUT_STATE GetPadInputState();  //pad���͏��擾

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
	static XINPUT_STATE input_Pad;      //�R���g���[���[�̓��͏��
};


//PAD_INPUT_DOWN�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂Q�L�[)
//PAD_INPUT_LEFT�@	// ���`�F�b�N�}�X�N(���L�[ or �e���L�[�̂S�L�[)
//PAD_INPUT_RIGHT�@	// ���`�F�b�N�}�X�N(�E�L�[ or �e���L�[�̂U�L�[)
//PAD_INPUT_UP�@	// ���`�F�b�N�}�X�N(��L�[ or �e���L�[�̂W�L�[)
//PAD_INPUT_1�@	// 1�{�^���`�F�b�N�}�X�N(�y�L�[)
//PAD_INPUT_2�@	// 2�{�^���`�F�b�N�}�X�N(�w�L�[)
//PAD_INPUT_3�@	// 3�{�^���`�F�b�N�}�X�N(�b�L�[)
//PAD_INPUT_4�@	// 4�{�^���`�F�b�N�}�X�N(�`�L�[)
//PAD_INPUT_5�@	// 5�{�^���`�F�b�N�}�X�N(�r�L�[)
//PAD_INPUT_6�@	// 6�{�^���`�F�b�N�}�X�N(�c�L�[)
//PAD_INPUT_7�@	// 7�{�^���`�F�b�N�}�X�N(�p�L�[)
//PAD_INPUT_8�@	// 8�{�^���`�F�b�N�}�X�N(�v�L�[)
//PAD_INPUT_9�@	// 9�{�^���`�F�b�N�}�X�N(�d�r�b�L�[)
//PAD_INPUT_10�@	// 10�{�^���`�F�b�N�}�X�N(�X�y�[�X�L�[)
