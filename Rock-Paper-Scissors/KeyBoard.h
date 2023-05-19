#pragma once
#include<iostream>


//�L�[�̎��
enum class _CURSOR_TYPE
{
	NONE = 0,   // ����0�i�Ȃɂ�������Ă��Ȃ��j
	NORMAL,     // A�`B,a�`b,1�`9
	CANCEL,     //�u�~�v(�ЂƂ���)
	DONE,       //�uOK�v(�m��)

	MISS = 99
};

class KeyBoard
{
public:
	KeyBoard();
	~KeyBoard();

	void Update();
	void Draw() const;

	//�J�[�\���̈ړ��E�{�^���̒������𒲐�
	bool CursorControl();

	//A�{�^���������ꂽ���̏���  ���͂��I���� 1 ���Ԃ��Ă���
	int KeyBoard_PushA();       //keyflg�@ ��"�����ꂽ�u��"�L�[

	//���͏��\��
	void DrawInputInfo() const;

private:
	int backimage;        //�w�i�摜
	int keyboardimage;    //�L�[�{�[�h�摜
	int Cursorimage[2];   //�m�[�}���J�[�\���摜  0 : �ʏ펞�@�@1 : �����ꂽ�Ƃ�
	int Cancelimage[2];   //  �u�~�v�J�[�\���摜
	int OKimage[2];       //  �uOK�v�J�[�\���摜

	bool isPushA = false;           //A���@������Ă���/������ĂȂ� �t���O    TRUE:������Ă���@FALSE:������Ă��Ȃ�
	int frame = 0;                  //�t���[�����J�E���g
	int movekeyX = 0;               //�ړ���   (�L�[�{�[�h�Z�Ԗ�)
	int movekeyY = 0;
	_CURSOR_TYPE CURSOR_NOW;        //���݂̃J�[�\��
	std::string input_str;          //���͕�����
	static int font_input;          //���͕\���p�t�H���g
};