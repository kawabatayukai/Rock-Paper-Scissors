#include "Scene_InputName.h"
#include"Scene_Ranking.h"
#include <DxLib.h>
#include "KeyManager.h"

//#define ALPHA_MAX 26      //�A���t�@�x�b�g����
//#define OUT_WIDTH 45      //��ʍ��[�`�L�[�{�[�h�܂ł̕�
//#define OUT_HEIGHT 200    //��ʏ�[�`�L�[�{�[�h�܂ł̍���
//#define SPACE 10          //�L�[�Ԃ̃X�y�[�X
//#define KEY_WIDTH 40      //�m�[�}���L�[�̕�
//const int CurStdX = OUT_WIDTH + SPACE + 5;    //�J�[�\����X���W�    (�u5�v�̓J�[�\���̕� �j
//const int CurStdY = OUT_HEIGHT + SPACE + 5;   //�J�[�\����Y���W�

#define CENTER_X 320      //��  720�@�p�ō�����L�[�{�[�h�𖳗���蒆�S�Ɏ����Ă���
#define CENTER_Y 120      //����480�@�@�@�@�@�@�@�@�@�@�s�v�Ȏ��� CENTER_X,Y ��0�ɂ��Ă�������
#define ALPHA_MAX 26      //�A���t�@�x�b�g����
#define OUT_WIDTH 45 + CENTER_X     //��ʍ��[�`�L�[�{�[�h�܂ł̕�
#define OUT_HEIGHT 200 + CENTER_Y    //��ʏ�[�`�L�[�{�[�h�܂ł̍���
#define SPACE 10          //�L�[�Ԃ̃X�y�[�X
#define KEY_WIDTH 40      //�m�[�}���L�[�̕�
const int CurStdX = OUT_WIDTH + SPACE + 5;    //�J�[�\����X���W�    (�u5�v�̓J�[�\���̕� �j
const int CurStdY = OUT_HEIGHT + SPACE + 5;   //�J�[�\����Y���W�

//���͕���    ���킩��₷�����邽�ߔ����i���ۂɕ\������Ă���L�[�{�[�h�Ɠ����z�u�j
const char AllStr[5][ALPHA_MAX / 2 + 1] = {
	"ABCDEFGHIJKLM",
	"NOPQRSTUVWXYZ",
	"abcdefghijklm",
	"nopqrstuvwxyz",
	"0123456789"
};

int a = 0;

Scene_InputName::Scene_InputName()
{
	KeyBoardInit();
	LoadKeyBoardImgaes();
}

//�X�V
void  Scene_InputName::Update()
{
	// �t�H���g�T�C�Y�̐ݒ�
	//SetFontSize(20);

	// ���O���͎w��������̕`��
	//DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	//DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);
	
	// ���O�̓���
	//DrawString(150, 310, "> ", 0xFFFFFF);
	//DrawBox(160, 305, 300, 335, 0x000055, TRUE);
	
	//�����L���O���͏���
	//if (KeyInputSingleCharString(170, 310, 10, name, FALSE) == 1)
	//{
	//	sortSave.setName(9, name);
	//	sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
	//	sortSave.SortRanking();		// �����L���O���בւ�
	//	sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
	//	a = 1;
	//}
	
}
//�`��
void  Scene_InputName::Draw() const
{
	// �t�H���g�T�C�Y�̐ݒ�
	//SetFontSize(20);
	
	// ���O���͎w��������̕`��
	//DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	//DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);
	
	// ���O�̓���
	//DrawString(150, 310, "> ", 0xFFFFFF);
	//DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	KeyBoard_Draw();
}

//��������
void Scene_InputName::KeyBoardInit()
{
	//�J�[�\���̏����ʒu��"A"
	movekeyX = 0;             //������0�Ԗ�
	movekeyY = 0;             //������1�Ԗ�

	//�J�[�\���̏����ʒu�́uA�v�Ȃ̂Ńm�[�}��
	CURSOR_NOW = CURSOR_TYPE::NORMAL;

	//���͕�����@������
	for (int i = 0; i < 10; i++)
	{
		name[i] = 0;
	}
	name[10] = '\0';     //�z��̈�ԍŌ��"\0"(�I�[�̖ڈ�)�����Ă���
	input_Pos = -1;           //
	pushFlag = FALSE;         //�ŏ���A�{�^���͉�����Ă��Ȃ�
}

//�摜�ǂݍ���
int Scene_InputName::LoadKeyBoardImgaes()
{
	//�w�i
	if ((backimage = LoadGraph("images/KeyBoard/back04.png")) == -1) return -1;
	//�L�[�{�[�h
	if ((keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png")) == -1) return -1;
	//�����ǂݍ��݁@��������/�����ĂȂ� ���A�������摜
	//�m�[�}���J�[�\��
	if ((LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
	//�u�~�v�J�[�\��
	if ((LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
	//�uOK�v�J�[�\��
	if ((LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;
	return 0;
}

//���ʉ��ǂݍ���
//int Scene_InputName::LoadSounds()
//{

//}

//�`��
void Scene_InputName::KeyBoard_Draw()const
{
	//�w�i
	DrawGraph(0, 0, backimage, FALSE);

	//�L�[�{�[�h
	DrawGraph(45 + CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);

	// �m�[�}��(A�`Z,a�`z,0�`9)�E�u�~�v�E�u�n�j�v�ɂ���ĉ摜�ω��@ switch���ő���
	// �@�@�@�@�@�@�@�@�����E�����Ȃ��ɂ���ĉ摜�ω��@�@�@�@�@�@�@ �摜�z��� PushFlg �ő���
	//�摜�z��� 0�Ԗ� �́u�����Ă��Ȃ��v�J�[�\���@�@1�Ԗڂ� �u�����Ă���v�J�[�\��
	switch (CURSOR_NOW)
	{
	case CURSOR_TYPE::NORMAL:    //�m�[�}���J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[pushFlag], TRUE);
		break;
	case CURSOR_TYPE::CANCEL:    //�u�~�v�J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[pushFlag], TRUE);
		break;
	case CURSOR_TYPE::DONE:      //�uOK�v�J�[�\��
		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[pushFlag], TRUE);
		break;
	default:
		break;
	}
	//���͒��̕�����\��
	DrawInputInfo();
}

//�X�V
void Scene_InputName::KeyBoard_Update()
{
	//�t���[�����J�E���g
	frame++;

	//�� �E
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		if (CursorControl() == true)
		{
			movekeyX++;     //�^�C�~���O���� + �ړ�
		}
		if (movekeyX > 12) movekeyX = 0;   //�E�[�ȏ�ō��[��
		CURSOR_NOW = CURSOR_TYPE::NORMAL;  //���݂̃L�[�̓m�[�}��
	}
	//�� ��
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		if (CursorControl() == true)
		{
			movekeyX--;     //�^�C�~���O���� + �ړ�
		}
		if (movekeyX < 0) movekeyX = 12;     //���[�ȏ�ŉE�[��
		CURSOR_NOW = CURSOR_TYPE::NORMAL;    //���݂̃L�[�̓m�[�}��
	}
	//�� ��
	if (KeyManager::OnPadPressed(PAD_INPUT_UP))
	{
		if (CursorControl() == true)
		{
			movekeyY--;     //�^�C�~���O���� + �ړ�
		}
		if (movekeyY <= 0) movekeyY = 0;     //��[�ŃX�g�b�v
		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
	}
	//�� ��
	if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
	{
		if (CursorControl() == true)
		{
			movekeyY++;     //�^�C�~���O���� + �ړ�
		}
		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
	}
	//�u�~�v�{�^��   �ua�`z�v�i��艺 ���� �u9�v�L�[���E��
	if (movekeyY == 4 && movekeyX >= 10)
	{
		movekeyX = 10;                       //�{�^���̈ʒu
		CURSOR_NOW = CURSOR_TYPE::CANCEL;         //���݂̃L�[�̓L�����Z���u�~�v
	}
	//�uOK�v�{�^��   �L�[�{�[�h�ŉ��i��艺
	if (movekeyY >= 5)
	{
		movekeyX = 4;                        //�{�^���̈ʒu
		movekeyY = 5;
		CURSOR_NOW = CURSOR_TYPE::DONE;           //���݂̃L�[��DONE�uOK�v
	}
}

//�J�[�\���̈ړ��E�{�^���̒������𒲐�
bool Scene_InputName::CursorControl()
{
	int timing = 8;
	if (frame % timing == 0) return true;
	//frame = 0;
	return false;
}

//A�{�^���������ꂽ���̏���  ���͂��I���� 1 ���Ԃ��Ă���
int Scene_InputName::KeyBoard_PushA(char* name)       //keyflg�@ ��"�����ꂽ�u��"�L�[
{
	//�@A�{�^���������Ă����
	if (KeyManager::OnPadPressed(PAD_INPUT_A))
	{
		//�������ł̘A�����͂̃^�C�~���O�𒲐��iPC�̂悤�ȁj
		if (CursorControl() == true)
		{
			// "A�`Z","a�`z","1�`9"�̏�ŉ����ꂽ
			if (CURSOR_NOW == CURSOR_TYPE::NORMAL)
			{
				pushFlag = true;        //������Ă����
				++input_Pos;            //���͈ʒu����E��

				//�����10����   �i�z���0�`9�j
				if (input_Pos > 9) input_Pos = 9;

				//�����z��ɓ���
				name[input_Pos] = AllStr[movekeyY][movekeyX];
			}
			else if (CURSOR_NOW == CURSOR_TYPE::CANCEL)                  //�u�~�v�L�[�̏�ŉ����ꂽ�@�ꕶ���폜
			{
				pushFlag = true;        //������Ă����

				//�ꕶ���ł����͂���Ă���Έꕶ������
				if (name[input_Pos] != 0) name[input_Pos] = 0; //0 �͉������͂���Ă��Ȃ����
				input_Pos--;            //���͈ʒu�������

				//���͈ʒu�͍Œ�-1�܂�
				if (input_Pos < -1) input_Pos = -1;
			}
			else if (CURSOR_NOW == CURSOR_TYPE::DONE)                  //�uOK�v�L�[�̏�ŉ����ꂽ�@�m��
			{
				//�ꕶ�������͂���Ă��Ȃ��ꍇ�͊m��ł��Ȃ�
				if (name[input_Pos] != 0)
				{
					//�ꕶ���ł����̓A��
					name[input_Pos + 1] = '\0';       //�Ō�̕����̈�E��'\0'

					//�����L���O�ɃZ�b�g
					DrawString(0, 0, "Ranking", 0xffffff);

					sortSave.setName(9, name);
					sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
					sortSave.SortRanking();		// �����L���O���בւ�
					sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�

					return 1;   //�I��
				}
				else
				{
					//�_������I�@�@�Ȍ��ʉ�
				}
			}
		}
	}
	else
	{
		pushFlag = false;          //������Ă��Ȃ���
	}
	return 0;
}

//���͏��\��
void Scene_InputName::DrawInputInfo()const
{
	if (name[0] == 0)
	{
		//SetDrawBlendMode
		SetFontSize(20);
		DrawString(200 + CENTER_X, 75 + CENTER_Y, "�E �E ���O����� �E �E", 0xffffff);
	}
	for (int i = 0; name[i] != '\0'; i++)
	{
		SetFontSize(30);
		DrawFormatString((220 + 20 * i) + CENTER_X, 70 + CENTER_Y, 0xffffff, " %c", name[i]);
	}
}

//�V�[���̕ύX����
AbstractScene* Scene_InputName::ChangeScene()
{
	if (KeyBoard_PushA(name) != 1)
	{
		KeyBoard_Update();
	}
	else
	{
		//Scene_sortSave();
		return new Scene_Ranking();

	}
	return this;
}





//��������
//void Scene_InputName::KeyBoardInit()
//{
//	//�ړ���
//	movekeyX = 0;
//	movekeyY = 0;
//	//�J�[�\���̏����ʒu�́uA�v
//	PUSH_NOW = KEY_TYPE::NORMAL;
//	//���͕�����@������
//	for (int i = 0; i < 10; i++)
//	{
//		InputName[i] = 0;
//	}
//	InputName[9] = '\0';
//	namePos = -1;
//	//�폜�E�m��t���O
//	PushFlg = FALSE;
//}
////�摜�ǂݍ���
//int Scene_InputName::LoadImgae()
//{
//	//�w�i
//	if ((backimage = LoadGraph("images/KeyBoard/back02.png")) == -1) return -1;
//	//�L�[�{�[�h
//	if ((keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png")) == -1) return -1;
//	//�����ǂݍ��݁@�����ꂽ/�����ĂȂ� ���A�������摜
//	//�m�[�}���J�[�\��
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
//	//�u�~�v�J�[�\��
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
//	//�uOK�v�J�[�\��
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;
//}
////���ʉ��ǂݍ���
//int Scene_InputName::LoadSounds()
//{
//	//if ((SE_push = LoadSoundMem("BGM/SE_Key_push.wav")) == -1) return -1;
//	//if ((SE_cancel = LoadSoundMem("BGM/SE_Key_cancel.wav")) == -1) return -1;
//	//if ((SE_ok = LoadSoundMem("BGM/SE_Key_ok.wav")) == -1) return -1;
//
//	return 0;
//}
////�`��
//void Scene_InputName::DrawKeyBoard()
//{
//	//�w�i
//	DrawGraph(0, 0, backimage, FALSE);
//	//�L�[�{�[�h
//	DrawGraph(45, OUT_HEIGHT, keyboardimage, TRUE);
//	//test
//	//DrawTestInfo();
//	DrawInputInfo();
//	// �m�[�}��(A�`Z,a�`z,0�`9)�E�u�~�v�E�u�n�j�v�ɂ���ĉ摜�ω��@ switch���ő���
//	// �@�@�@�@�@�@�@�@�����E�����Ȃ��ɂ���ĉ摜�ω��@�@�@�@�@�@�@ �摜�z��� PushFlg �ő���
//	switch (PUSH_NOW)
//	{
//	case KEY_TYPE::NORMAL:    //�m�[�}���J�[�\��
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[PushFlg], TRUE);
//		break;
//	case KEY_TYPE::CANCEL:    //�u�~�v�J�[�\��
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[PushFlg], TRUE);
//		break;
//	case KEY_TYPE::DONE:      //�uOK�v�J�[�\��
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[PushFlg], TRUE);
//		break;
//	default:
//		break;
//	}
//}
////�ړ�
//void Scene_InputName::KeyBoardControl(int NowKey)
//{
//	//�t���[�����J�E���g
//	frame++;
//	//�� �E
//	if (NowKey & PAD_INPUT_RIGHT)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyX++;     //�^�C�~���O���� + �ړ�
//		}
//		if (movekeyX >= 12) movekeyX = 12;   //�E�[�ŃX�g�b�v
//		PUSH_NOW = KEY_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
//	}
//	//�� ��
//	if (NowKey & PAD_INPUT_LEFT)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyX--;     //�^�C�~���O���� + �ړ�
//		}
//		if (movekeyX <= 0) movekeyX = 0;     //���[�ŃX�g�b�v
//		PUSH_NOW = KEY_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
//	}
//	//�� ��
//	if (NowKey & PAD_INPUT_UP)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyY--;     //�^�C�~���O���� + �ړ�
//		}
//		if (movekeyY <= 0) movekeyY = 0;     //��[�ŃX�g�b�v
//		PUSH_NOW = KEY_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
//	}
//	//�� ��
//	if (NowKey & PAD_INPUT_DOWN)
//	{
//		if (InputControl() == 0)
//		{
//			movekeyY++;     //�^�C�~���O���� + �ړ�
//		}
//		PUSH_NOW = KEY_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
//	}
//	//�u�~�v�{�^��   �ua�`z�v�i��艺 ���� �u9�v�L�[���E��
//	if (movekeyY == 4 && movekeyX >= 10)
//	{
//		movekeyX = 10;                       //�{�^���̈ʒu
//		PUSH_NOW = KEY_TYPE::CANCEL;         //���݂̃L�[�̓L�����Z���u�~�v
//	}
//	//�uOK�v�{�^��   �L�[�{�[�h�ŉ��i��艺
//	if (movekeyY >= 5)
//	{
//		movekeyX = 4;                        //�{�^���̈ʒu
//		movekeyY = 5;
//		PUSH_NOW = KEY_TYPE::DONE;           //���݂̃L�[��DONE�uOK�v
//	}
//	//B�{�^���Ŋm��
//	//testPush_B_Key2(NowKey);
//}
////A�{�^���������ꂽ���̏����@������ranking�Ŏg���܂�
//void Scene_InputName::Push_A_Key(int NowKey, int* GameState, int Score)
//{
//	//"�������u��"�𔻒�
//	static int push_B;
//	if (NowKey & PAD_INPUT_A)
//	{
//		push_B++;
//		if (PUSH_NOW == KEY_TYPE::NORMAL)
//		{
//			//"�������u��"�̂ݓ���
//			if (push_B >= 1 && push_B < 8)
//			{
//				//B�����ꂽ��t���O�@TRUE
//				PushFlg = TRUE;
//				//���̓^�C�~���O
//				if (InputControl() == 0)
//				{
//					//SE
//					PlaySoundMem(SE_push, DX_PLAYTYPE_BACK);
//					++namePos;
//					//�����9����
//					if (namePos >= 8) namePos = 8;
//					//�z��ɓ���
//					InputName[namePos] = AllStr[movekeyY][movekeyX];
//				}
//			}
//		}
//		else if (PUSH_NOW == KEY_TYPE::CANCEL) //�u�~�v�L�[��ŉ����Ĉꕶ���폜
//		{
//			//B�����ꂽ��t���O�@TRUE
//			PushFlg = TRUE;
//			//���̓^�C�~���O
//			if (InputControl() == 0)
//			{
//				PlaySoundMem(SE_cancel, DX_PLAYTYPE_BACK);
//				InputName[namePos] = 0;
//				//�O�����ȉ��ɂ͂Ȃ�Ȃ�
//				if (namePos >= 0) namePos--;
//			}
//		}
//		else if (PUSH_NOW == KEY_TYPE::DONE)   //�uOK�v�L�[��ŉ����Ċm��i�����L���O�ϐ��ɑ���j
//		{
//			//A�����ꂽ��t���O�@TRUE
//			PushFlg = TRUE;
//			//���̓^�C�~���O
//			if (InputControl() == 0)
//			{
//				//�����͂ł̊m��͕s��
//				if (InputName[0] != '\0')
//				{
//					//SE
//					PlaySoundMem(SE_ok, DX_PLAYTYPE_BACK);
//					InputName[namePos + 1] = '\0';
//					//�����L���O�ϐ��� name�EScore ���� --> ��ʑJ��
//					//ranking.SetRanking(InputName, GameState, Score);
//				}
//				{
//					//SE �����͎��̓J�`�J�`�Ȃ�܂�
//					PlaySoundMem(SE_push, DX_PLAYTYPE_BACK);
//				}
//			}
//		}
//	}
//	else
//	{
//		if (push_B > 0) push_B = -1;
//		else push_B = 0;
//		PushFlg = FALSE;
//	}
//}
////���͏��\��
//void Scene_InputName::DrawInputInfo()
//{
//	if (InputName[0] == 0)
//	{
//		//SetDrawBlendMode
//		SetFontSize(20);
//		DrawString(200, 125, "�E �E ���O����� �E �E", 0xffffff);
//	}
//	for (int i = 0; InputName[i] != '\0'; i++)
//	{
//		SetFontSize(30);
//		DrawFormatString(220 + 20 * i, 120, 0xffffff, " %c", InputName[i]);
//	}
//}
////�R���g���[���[����
//int Scene_InputName::InputControl()
//{
//	int timing = 8;
//	return frame % timing;
//}
////��test�p���@�e����\��
//void Scene_InputName::DrawTestInfo()
//{
//	//InputName�`�F�b�N
//	//if (InputName[0] == 0) InputName[0] = '|';
//	for (int i = 0; InputName[i] != '\0'; i++)
//	{
//		SetFontSize(20);
//		DrawString(0, 0, "NAME : ", 0xffffff);
//		DrawFormatString(80 + 15 * i, 0, 0xffffff, "%c", InputName[i]);
//	}
//	//PushFlg�`�F�b�N
//	DrawFormatString(0, 30, 0xffffff, "Push : %s", PushFlg == FALSE ? "������ĂȂ�" : "������Ă�");
//}