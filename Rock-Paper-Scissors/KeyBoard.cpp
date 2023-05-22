#include "KeyBoard.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"SortSave.h"
#include"SortSaveTime.h"

namespace KEY_CONSTANTS
{
	const int CUR_INIT_X = 145;   //�J�[�\�������ʒu��
	const int CUR_INIT_Y = 315;   //�J�[�\�������ʒu��

	const int CUR_NL_W = 60;      //�J�[�\�����m�[�}��
	const int CUR_NL_H = 60;      //�J�[�\�����m�[�}��

	const int KEY_DISTANCE = 10;  //�L�[�Ԃ̋���(�J�[�\��������)

	const int INPUTSPACE_X = 350; //���O���͗���
	const int INPUTSPACE_Y = 160; //���O���͗���

	const int INPUT_INTERVAL = 10;//�A�����͐���

	//���͕���   �i���ۂɕ\������Ă���L�[�{�[�h�Ɠ����z�u�j
	const char AllStr[5][14] = 
	{
		"ABCDEFGHIJKLM",
		"NOPQRSTUVWXYZ",
		"abcdefghijklm",
		"nopqrstuvwxyz",
		"0123456789!?%"
	};

	//���͂��Ȃ����ɕ\������镶����
	const std::string No_Input("Please Your Name");
}

int KeyBoard::font_input = 0;

//�R���X�g���N�^
KeyBoard::KeyBoard() :isStartKey(true), frame(0), frame_CL(0), KeyType(_KEY_TYPE::NORMAL), num_x(0), num_y(0)
{
	if (font_input == 0) font_input = CreateFontToHandle("���C���I", 50, 10, DX_FONTTYPE_ANTIALIASING);
	
	//�J��A��������Ă�����
	if (KeyManager::OnPadPressed(PAD_INPUT_A)) isStartKey = false;

	//--------------------- image -------------------------
	image_back = LoadGraph("images/Story/starback.png");              //�w�i
	image_key = LoadGraph("images/KeyBoard/Keyboard_AlNum03.png");    //�L�[�{�[�h
	LoadDivGraph("images/KeyBoard/Cursor_normal.png", 2, 2, 1, 60, 60, image_cur_NL);    //�m�[�}���J�[�\��
	LoadDivGraph("images/KeyBoard/Cursor_Cancel.png", 2, 2, 1, 80, 130, image_cur_CL);   //�L�����Z��
	LoadDivGraph("images/KeyBoard/Cursor_Done.png", 2, 2, 1, 80, 200, image_cur_DN);     //�m��
	image_button[0] = LoadGraph("images/KeyBoard/Bbutton.png");       //"B"
	image_button[1] = LoadGraph("images/KeyBoard/start.png");         //"START"
	image_inputSpace = LoadGraph("images/KeyBoard/Input_Frame.png");  //���O���͗�

	//--------------------- sound -------------------------
	se_normalkey = LoadSoundMem("Sound/KeyBoard/key_normalpush.wav");
	se_cancelkey = LoadSoundMem("Sound/KeyBoard/key_cancel.wav");
	se_donekey = LoadSoundMem("Sound/KeyBoard/key_ok.wav");
}

KeyBoard::~KeyBoard()
{
}

void KeyBoard::Update()
{
	using namespace KEY_CONSTANTS;

	//�J��A��������Ă����Ԃ𖳌���
	if (isStartKey == false && KeyManager::OnPadReleased(PAD_INPUT_A)) isStartKey = true;

	//��
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		//��u�̓��͂ƒ��������͂ɑΉ�����
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_LEFT))
		{
			num_x--;
			if (num_x < 0) num_x = 13;   //�E�[��

			KeyType = _KEY_TYPE::NORMAL; //�m�[�}��
		}

		//�m�[�}���L�[�ȊO�̃L�[����
		if (num_x == 13 && num_y == 1) num_y = 0;
		if (num_x == 13 && num_y >= 3) num_y = 2;
	}
	//�E
	else if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		//��u�̓��͂ƒ��������͂ɑΉ�����
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_RIGHT))
		{
			num_x++;
			if (num_x > 13) num_x = 0;   //���[��

			KeyType = _KEY_TYPE::NORMAL; //�m�[�}��
		}

		//�m�[�}���L�[�ȊO�̃L�[����
		if (num_x == 13 && num_y == 1) num_y = 0;
		if (num_x == 13 && num_y >= 3) num_y = 2;
	}
	//��
	else if (KeyManager::OnPadPressed(PAD_INPUT_UP))
	{
		//��u�̓��͂ƒ��������͂ɑΉ�����
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_UP))
		{
			num_y--;
			if (num_y < 0) num_y = 4;    //���[��

			KeyType = _KEY_TYPE::NORMAL; //�m�[�}��
		}

		//�m�[�}���L�[�ȊO�̃L�[����
		if (num_x == 13 && num_y >= 2) num_y = 2;
		else if (num_x == 13 && num_y == 1) num_y = 0;
	}
	//��
	else if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		//��u�̓��͂ƒ��������͂ɑΉ�����
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_DOWN))
		{
			num_y++;
			if (num_y > 4) num_y = 0;   //��[��

			KeyType = _KEY_TYPE::NORMAL; //�m�[�}��
		}

		//�m�[�}���L�[�ȊO�̃L�[����
		if (num_x == 13 && num_y == 0 || num_x == 13 && num_y == 1) num_y = 2;
		else if (num_x == 13 && num_y == 2 || num_x == 13 && num_y == 3) num_y = 0;
	}
	else {};

	//�L�����Z���L�[
	if (num_x == 13 && num_y == 0 || num_x == 13 && num_y == 1) KeyType = _KEY_TYPE::CANCEL;
	//�m��L�[
	if (num_x == 13 && num_y >= 2) KeyType = _KEY_TYPE::DONE;

	//�������Ƃ�
	if (KeyManager::OnPadReleased(PAD_INPUT_LEFT))  frame = 0;
	if (KeyManager::OnPadReleased(PAD_INPUT_RIGHT)) frame = 0;
	if (KeyManager::OnPadReleased(PAD_INPUT_UP))    frame = 0;
	if (KeyManager::OnPadReleased(PAD_INPUT_DOWN))  frame = 0;
}

void KeyBoard::Draw() const
{
	using namespace KEY_CONSTANTS;

	//�w�i
	DrawGraph(0, 0, image_back, FALSE);
	//�L�[�{�[�h
	DrawGraph(0,0, image_key, TRUE);
	//" (B) "
	DrawGraph(1110, 325, image_button[0], TRUE);
	//" (START) "
	DrawGraph(1080, 465, image_button[1], TRUE);
	//���O����
	DrawGraph(INPUTSPACE_X, INPUTSPACE_Y, image_inputSpace, TRUE);

	//�J�[�\�����W
	int draw_x = 0;
	int draw_y = 0;
	//�J�[�\���摜
	const int* draw_image = image_cur_NL;

	//�L�[�̎�ނŕ`��ʒu�𒲐�
	switch (KeyType)
	{
	case KeyBoard::_KEY_TYPE::NORMAL:
		draw_x = CUR_INIT_X + (num_x * (CUR_NL_W + KEY_DISTANCE));
		draw_y = CUR_INIT_Y + (num_y * (CUR_NL_H + KEY_DISTANCE));
		break;

	case KeyBoard::_KEY_TYPE::CANCEL:
		draw_x = CUR_INIT_X + (num_x * (CUR_NL_W + KEY_DISTANCE));
		draw_y = CUR_INIT_Y;
		draw_image = image_cur_CL;
		break;

	case KeyBoard::_KEY_TYPE::DONE:
		draw_x = CUR_INIT_X + (num_x * (CUR_NL_W + KEY_DISTANCE));
		draw_y = 455;
		draw_image = image_cur_DN;
		break;

	default:
		break;
	}

	//�J�[�\��
	DrawGraph(draw_x, draw_y, draw_image[isPushA], TRUE);
}

int KeyBoard::KeyBoard_PushA()
{
	using namespace KEY_CONSTANTS;

	// A�{�^�������ꒆ�@���@�J��A�h�~
	if (KeyManager::OnPadPressed(PAD_INPUT_A) && isStartKey == true)
	{
		//������͈̂��̂�
		switch (KeyType)
		{
		case KeyBoard::_KEY_TYPE::NORMAL:

			//10�����܂� ���͂ł���̂�1��
			if (isPushA == false && input_str.size() < 10)
			{
				input_str.push_back(KEY_CONSTANTS::AllStr[num_y][num_x]);
				PlaySoundMem(se_normalkey, DX_PLAYTYPE_BACK);
			}
			break;


		case KeyBoard::_KEY_TYPE::CANCEL:

			//��u�̓��͂ƒ��������͂ɑΉ�����
			if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_A))
			{
				//�ꕶ���ł����͂���Ă���Έꕶ������
				if (input_str.empty() != true) 
				{
					input_str.pop_back();
					PlaySoundMem(se_cancelkey, DX_PLAYTYPE_BACK);
				}
			}
			break;

		case KeyBoard::_KEY_TYPE::DONE:

			//�ꕶ�������͂���Ă��Ȃ��ꍇ�͊m��ł��Ȃ�
			if (input_str.empty() != true)
			{
				char* name = const_cast<char*>(input_str.c_str());
				sortSave.setName(9, name);
				sortSaveTime.setName(9, name);
				if (CheckSoundMem(se_donekey) == 0) PlaySoundMem(se_donekey, DX_PLAYTYPE_BACK);

				return 1;
			}
			else
			{
				//�m��s��
			}
			break;

		default:
			break;
		}
		isPushA = true;
	}
	else
	{
		isPushA = false;
	}

	//B�{�^���ł��ꕶ��������
	if (KeyManager::OnPadPressed(PAD_INPUT_B))
	{
		if (++frame % INPUT_INTERVAL == 0 || KeyManager::OnPadClicked(PAD_INPUT_B))
		{
			if (input_str.empty() != true)
			{
				input_str.pop_back();
				PlaySoundMem(se_cancelkey, DX_PLAYTYPE_BACK);
			}
		}
		
	}
	//�������Ƃ�
	if (KeyManager::OnPadReleased(PAD_INPUT_B)) frame_CL = 0;
	
	//START�{�^���ł��m��ł���
	if (KeyManager::OnPadClicked(PAD_INPUT_8))
	{
		//�ꕶ�������͂���Ă��Ȃ��ꍇ�͊m��ł��Ȃ�
		if (input_str.empty() != true)
		{
			char* name = const_cast<char*>(input_str.c_str());
			sortSave.setName(9, name);
			sortSaveTime.setName(9, name);
			if (CheckSoundMem(se_donekey) == 0) PlaySoundMem(se_donekey, DX_PLAYTYPE_BACK);

			return 1;
		}
		else
		{
			//�m��s��
		}
	}

	return 0;
}

//���͕�����\��
void KeyBoard::DrawInputInfo() const
{
	using namespace KEY_CONSTANTS;

	//���͂Ȃ�
	if (input_str.empty() == true)
	{
		int str_w = GetDrawStringWidthToHandle(No_Input.c_str(), No_Input.length(), font_input);

		DrawStringToHandle((640 - (str_w / 2)), INPUTSPACE_Y + 15, "Please Your Name", 0xffffff, font_input);
	}
	else
	{
		int str_w = GetDrawStringWidthToHandle(input_str.c_str(), input_str.length(), font_input);

		DrawStringToHandle(640 - (str_w / 2), INPUTSPACE_Y + 15, input_str.c_str(), 0xffffff, font_input);
	}
}
