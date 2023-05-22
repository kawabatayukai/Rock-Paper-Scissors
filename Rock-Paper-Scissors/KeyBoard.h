#pragma once
#include<iostream>

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();

	void Update();
	void Draw() const;

	//A�{�^���������ꂽ���̏���  ���͂��I���� 1 ���Ԃ��Ă���
	int KeyBoard_PushA();       //keyflg�@ ��"�����ꂽ�u��"�L�[

	//���͏��\��
	void DrawInputInfo() const;

private:

	//�L�[�̎��
	enum class _KEY_TYPE
	{
		NORMAL,     // A�`B,a�`b,1�`9
		CANCEL,     //�u�~�v(�ЂƂ���)
		DONE,       //�uOK�v(�m��)
	};
	_KEY_TYPE KeyType;     //�L�[�̎��

	int num_x;             //�L�[�z��x�Ԗ�
	int num_y;             //�L�[�z��y�Ԗ�

	int frame;             //�t���[�����J�E���g(���E�㉺�ړ��A�����͒����p)
	int frame_CL;          //�t���[�����J�E���g(�ꕶ���폜�A�����͒����p)

	std::string input_str;          //���͕�����
	static int font_input;          //���͕\���p�t�H���g

	bool isStartKey;                //�J��A��������Ă����Ԗh�~
	bool isPushA = false;           //A�{�^����������Ă��邩(�摜�ω��p)

	//--------------------- image -------------------------
	int image_back;        //�w�i
	int image_key;         //�L�[�{�[�h
	int image_cur_NL[2];   //�m�[�}���J�[�\��
	int image_cur_CL[2];   //�L�����Z���J�[�\��
	int image_cur_DN[2];   //�m��J�[�\��
	int image_button[2];   //START,B�{�^��
	int image_inputSpace;  //���͗�

	//--------------------- sound -------------------------
	int se_normalkey;      //�m�[�}��
	int se_cancelkey;      //�ꕶ���폜
	int se_donekey;        //OK
};