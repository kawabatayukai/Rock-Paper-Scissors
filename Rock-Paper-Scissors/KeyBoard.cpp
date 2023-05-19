#include "KeyBoard.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"SortSave.h"
#include"SortSaveTime.h"

#define KEY_CENTER_X 320      //��  720�@�p�ō�����L�[�{�[�h�𖳗���蒆�S�Ɏ����Ă���
#define KEY_CENTER_Y 120      //����480�@�@�@�@�@�@�@�@�@�@�s�v�Ȏ��� CENTER_X,Y ��0�ɂ��Ă�������

#define ALPHA_MAX 26      //�A���t�@�x�b�g����

#define OUT_WIDTH 45 + KEY_CENTER_X     //��ʍ��[�`�L�[�{�[�h�܂ł̕�
#define OUT_HEIGHT 200 + KEY_CENTER_Y    //��ʏ�[�`�L�[�{�[�h�܂ł̍���
#define SPACE 10          //�L�[�Ԃ̃X�y�[�X
#define KEY_WIDTH 40      //�m�[�}���L�[�̕�
const int CurStdX = OUT_WIDTH + SPACE + 5;    //�J�[�\����X���W�    (�u5�v�̓J�[�\���̕� �j
const int CurStdY = OUT_HEIGHT + SPACE + 5;   //�J�[�\����Y���W�

namespace ALL_KEYS
{
	//���͕���   �i���ۂɕ\������Ă���L�[�{�[�h�Ɠ����z�u�j
	const char AllStr[5][ALPHA_MAX / 2 + 1] = {
		"ABCDEFGHIJKLM",
		"NOPQRSTUVWXYZ",
		"abcdefghijklm",
		"nopqrstuvwxyz",
		"0123456789"
	};
}

int KeyBoard::font_input = 0;

//�R���X�g���N�^
KeyBoard::KeyBoard() : movekeyX(0), movekeyY(0), CURSOR_NOW(_CURSOR_TYPE::NORMAL)
{
	keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png");
	LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage);
	//�u�~�v�J�[�\��
	LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage);
	//�uOK�v�J�[�\��
	LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage);

	if (font_input == 0) font_input = CreateFontToHandle("���C���I", 20, 3, DX_FONTTYPE_ANTIALIASING);\
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	frame++;  //�t���[���J�E���g

	//�E
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		if (CursorControl() == true) movekeyX++;    //�^�C�~���O���� + �ړ�
		if (movekeyX > 12) movekeyX = 0;            //�E�[�ȏ�ō��[��  
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //���݂̃L�[�̓m�[�}��
	}
	//��
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		if (CursorControl() == true) movekeyX--;    //�^�C�~���O���� + �ړ�
		if (movekeyX < 0) movekeyX = 12;            //�E�[�ȏ�ō��[��  
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //���݂̃L�[�̓m�[�}��
	}
	//��
	if (KeyManager::OnPadPressed(PAD_INPUT_UP))
	{
		if (CursorControl() == true) movekeyY--;    //�^�C�~���O���� + �ړ�
		if (movekeyY <= 0) movekeyY = 0;            //�E�[�ȏ�ō��[��  
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //���݂̃L�[�̓m�[�}��
	}
	//��
	if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		if (CursorControl() == true) movekeyY++;    //�^�C�~���O���� + �ړ�
		CURSOR_NOW = _CURSOR_TYPE::NORMAL;          //���݂̃L�[�̓m�[�}��
	}

	//�u�~�v�{�^��   �ua�`z�v�i��艺 ���� �u9�v�L�[���E��
	if (movekeyY == 4 && movekeyX >= 10)
	{
		movekeyX = 10;                             //�{�^���̈ʒu
		CURSOR_NOW = _CURSOR_TYPE::CANCEL;         //���݂̃L�[�̓L�����Z���u�~�v
	}
	//�uOK�v�{�^��   �L�[�{�[�h�ŉ��i��艺
	if (movekeyY >= 5)
	{
		movekeyX = 4;                              //�{�^���̈ʒu
		movekeyY = 5;

		CURSOR_NOW = _CURSOR_TYPE::DONE;           //���݂̃L�[��DONE�uOK�v
	}
}

void KeyBoard::Draw() const
{
	//�w�i
	DrawGraph(0, 0, backimage, FALSE);
	//�L�[�{�[�h
	DrawGraph(45 + KEY_CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);


	// �m�[�}��(A�`Z,a�`z,0�`9)�E�u�~�v�E�u�n�j�v�ɂ���ĉ摜�ω��@ switch���ő���
	// �@�@�@�@�@�@�@�@�����E�����Ȃ��ɂ���ĉ摜�ω��@�@�@�@�@�@�@ �摜�z��� PushFlg �ő���

	//�摜�z��� 0�Ԗ� �́u�����Ă��Ȃ��v�J�[�\���@�@1�Ԗڂ� �u�����Ă���v�J�[�\��

	switch (CURSOR_NOW)
	{
	case _CURSOR_TYPE::NORMAL:    //�m�[�}���J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[isPushA], TRUE);
		break;

	case _CURSOR_TYPE::CANCEL:    //�u�~�v�J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[isPushA], TRUE);
		break;

	case _CURSOR_TYPE::DONE:      //�uOK�v�J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[isPushA], TRUE);
		break;

	default:
		break;
	}
}

bool KeyBoard::CursorControl()
{
	int timing = 8;
	if (frame % timing == 0) return true;
	return false;
}

int KeyBoard::KeyBoard_PushA()
{
	using namespace ALL_KEYS;

	if (KeyManager::OnPadPressed(PAD_INPUT_A))
	{
		if (CursorControl() == true)
		{
			// "A�`Z","a�`z","1�`9"�̏�ŉ����ꂽ
			if (CURSOR_NOW == _CURSOR_TYPE::NORMAL)
			{
				isPushA = true;

				//10�����܂�
				if (input_str.size() < 10)
				{
					input_str.push_back(AllStr[movekeyY][movekeyX]);
				}
			}
			else if (CURSOR_NOW == _CURSOR_TYPE::CANCEL)
			{
				isPushA = true;
				//�ꕶ���ł����͂���Ă���Έꕶ������
				if (input_str.empty() != true) input_str.pop_back();
			}
			else if (CURSOR_NOW == _CURSOR_TYPE::DONE)
			{
				//�ꕶ�������͂���Ă��Ȃ��ꍇ�͊m��ł��Ȃ�
				if (input_str.empty() != true)
				{
					char* name = const_cast<char*>(input_str.c_str());
					sortSave.setName(9, name);
					sortSaveTime.setName(9, name);

					return 1;
				}
				else
				{
					//�m��s��
				}
			}
		}
	}
	else
	{
		isPushA = false;
	}

	return 0;
}

void KeyBoard::DrawInputInfo() const
{
	if (input_str.empty() == true)
	{
		DrawStringToHandle(200 + KEY_CENTER_X, 125 + KEY_CENTER_Y, "Please Your Name", 0xffffff, font_input);
	}
	else
	{
		int str_w = GetDrawStringWidthToHandle(input_str.c_str(), input_str.length(), font_input);

		DrawStringToHandle(640 - (str_w / 2), 125 + KEY_CENTER_Y, input_str.c_str(), 0xffffff, font_input);
	}
}
