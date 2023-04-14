//#include "Scene_InputName.h"
//#include"Scene_Ranking.h"
//#include <DxLib.h>
//#include "KeyManager.h"
//#include"SortSave.h"
//
//#define CENTER_X 320      //��  720�@�p�ō�����L�[�{�[�h�𖳗���蒆�S�Ɏ����Ă���
//#define CENTER_Y 120      //����480�@�@�@�@�@�@�@�@�@�@�s�v�Ȏ��� CENTER_X,Y ��0�ɂ��Ă�������
//#define ALPHA_MAX 26      //�A���t�@�x�b�g����
//#define OUT_WIDTH 45 + CENTER_X     //��ʍ��[�`�L�[�{�[�h�܂ł̕�
//#define OUT_HEIGHT 200 + CENTER_Y    //��ʏ�[�`�L�[�{�[�h�܂ł̍���
//#define SPACE 10          //�L�[�Ԃ̃X�y�[�X
//#define KEY_WIDTH 40      //�m�[�}���L�[�̕�
//const int CurStdX = OUT_WIDTH + SPACE + 5;    //�J�[�\����X���W�    (�u5�v�̓J�[�\���̕� �j
//const int CurStdY = OUT_HEIGHT + SPACE + 5;   //�J�[�\����Y���W�
//
////���͕���    ���킩��₷�����邽�ߔ����i���ۂɕ\������Ă���L�[�{�[�h�Ɠ����z�u�j
//const char AllStr[5][ALPHA_MAX / 2 + 1] = {
//	"ABCDEFGHIJKLM",
//	"NOPQRSTUVWXYZ",
//	"abcdefghijklm",
//	"nopqrstuvwxyz",
//	"0123456789"
//};
//
//Scene_InputName::Scene_InputName()
//{
//	KeyBoardInit();
//	LoadKeyBoardImgaes();
//}
//
///*�R���X�g���N�^*/
////virtual ~Scene_InputName() {};
//
//char name[11];
//
////�X�V
//void Scene_InputName::Update()
//{
//
//}
//
////�`��
//void Scene_InputName::Draw()const
//{
//	KeyBoard_Draw();
//}
//
////��������
//void Scene_InputName::KeyBoardInit()
//{
//	//�J�[�\���̏����ʒu��"A"
//	movekeyX = 0;             //������0�Ԗ�
//	movekeyY = 0;             //������1�Ԗ�
//
//	//�J�[�\���̏����ʒu�́uA�v�Ȃ̂Ńm�[�}��
//	CURSOR_NOW = CURSOR_TYPE::NORMAL;
//
//	//���͕�����@������
//	for (int i = 0; i < 10; i++)
//	{
//		InputName[i] = 0;
//	}
//	InputName[10] = '\0';     //�z��̈�ԍŌ��"\0"(�I�[�̖ڈ�)�����Ă���
//	input_Pos = -1;           //
//	pushFlag = FALSE;         //�ŏ���A�{�^���͉�����Ă��Ȃ�
//}
//
////�摜�ǂݍ���
//int Scene_InputName::LoadKeyBoardImgaes()
//{
//	//�w�i
//	if ((backimage = LoadGraph("images/KeyBoard/back02.png")) == -1) return -1;
//	//�L�[�{�[�h
//	if ((keyboardimage = LoadGraph("images/KeyBoard/OPEN_Board4.png")) == -1) return -1;
//	//�����ǂݍ��݁@��������/�����ĂȂ� ���A�������摜
//	//�m�[�}���J�[�\��
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Normal.png", 2, 2, 1, 40, 40, Cursorimage)) == -1) return -1;
//	//�u�~�v�J�[�\��
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Cancel.png", 2, 2, 1, 70, 40, Cancelimage)) == -1) return -1;
//	//�uOK�v�J�[�\��
//	if ((LoadDivGraph("images/KeyBoard/N_Link_Space.png", 2, 2, 1, 200, 40, OKimage)) == -1) return -1;
//	return 0;
//}
//
////���ʉ��ǂݍ���
////int Scene_InputName::LoadSounds()
////{
//
////}
//
////�`��
//void Scene_InputName::KeyBoard_Draw()const
//{
//	//�w�i
//	DrawGraph(320, 120, backimage, FALSE);
//
//	//�L�[�{�[�h
//	DrawGraph(45 + CENTER_X, OUT_HEIGHT, keyboardimage, TRUE);
//
//	// �m�[�}��(A�`Z,a�`z,0�`9)�E�u�~�v�E�u�n�j�v�ɂ���ĉ摜�ω��@ switch���ő���
//	// �@�@�@�@�@�@�@�@�����E�����Ȃ��ɂ���ĉ摜�ω��@�@�@�@�@�@�@ �摜�z��� PushFlg �ő���
//	//�摜�z��� 0�Ԗ� �́u�����Ă��Ȃ��v�J�[�\���@�@1�Ԗڂ� �u�����Ă���v�J�[�\��
//	switch (CURSOR_NOW)
//	{
//	case CURSOR_TYPE::NORMAL:    //�m�[�}���J�[�\��
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, Cursorimage[pushFlag], TRUE);
//		break;
//	case CURSOR_TYPE::CANCEL:    //�u�~�v�J�[�\��
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX + 20, CurStdY + KEY_WIDTH * movekeyY, Cancelimage[pushFlag], TRUE);
//		break;
//	case CURSOR_TYPE::DONE:      //�uOK�v�J�[�\��
//		DrawGraph(CurStdX + KEY_WIDTH * movekeyX, CurStdY + KEY_WIDTH * movekeyY, OKimage[pushFlag], TRUE);
//		break;
//	default:
//		break;
//	}
//	//���͒��̕�����\��
//	DrawInputInfo();
//}
//
////�X�V
//void Scene_InputName::KeyBoard_Update()
//{
//	//�t���[�����J�E���g
//	frame++;
//
//	//�� �E
//	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyX++;     //�^�C�~���O���� + �ړ�
//		}
//		if (movekeyX > 12) movekeyX = 0;   //�E�[�ȏ�ō��[��
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;  //���݂̃L�[�̓m�[�}��
//	}
//	//�� ��
//	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyX--;     //�^�C�~���O���� + �ړ�
//		}
//		if (movekeyX < 0) movekeyX = 12;     //���[�ȏ�ŉE�[��
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;    //���݂̃L�[�̓m�[�}��
//	}
//	//�� ��
//	if (KeyManager::OnPadPressed(PAD_INPUT_UP))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyY--;     //�^�C�~���O���� + �ړ�
//		}
//		if (movekeyY <= 0) movekeyY = 0;     //��[�ŃX�g�b�v
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
//	}
//	//�� ��
//	if (KeyManager::OnPadPressed(PAD_INPUT_DOWN))
//	{
//		if (CursorControl() == true)
//		{
//			movekeyY++;     //�^�C�~���O���� + �ړ�
//		}
//		CURSOR_NOW = CURSOR_TYPE::NORMAL;         //���݂̃L�[�̓m�[�}��
//	}
//	//�u�~�v�{�^��   �ua�`z�v�i��艺 ���� �u9�v�L�[���E��
//	if (movekeyY == 4 && movekeyX >= 10)
//	{
//		movekeyX = 10;                       //�{�^���̈ʒu
//		CURSOR_NOW = CURSOR_TYPE::CANCEL;         //���݂̃L�[�̓L�����Z���u�~�v
//	}
//	//�uOK�v�{�^��   �L�[�{�[�h�ŉ��i��艺
//	if (movekeyY >= 5)
//	{
//		movekeyX = 4;                        //�{�^���̈ʒu
//		movekeyY = 5;
//		CURSOR_NOW = CURSOR_TYPE::DONE;           //���݂̃L�[��DONE�uOK�v
//	}
//}
//
////�J�[�\���̈ړ��E�{�^���̒������𒲐�
//bool Scene_InputName::CursorControl()
//{
//	int timing = 8;
//	if (frame % timing == 0) return true;
//	//frame = 0;
//	return false;
//}
//
////A�{�^���������ꂽ���̏���  ���͂��I���� 1 ���Ԃ��Ă���
//int Scene_InputName::KeyBoard_PushA(char* name)       //keyflg�@ ��"�����ꂽ�u��"�L�[
//{
//	//�@A�{�^���������Ă����
//	if (KeyManager::OnPadPressed(PAD_INPUT_A))
//	{
//		//�������ł̘A�����͂̃^�C�~���O�𒲐��iPC�̂悤�ȁj
//		if (CursorControl() == true)
//		{
//			// "A�`Z","a�`z","1�`9"�̏�ŉ����ꂽ
//			if (CURSOR_NOW == CURSOR_TYPE::NORMAL)
//			{
//				pushFlag = true;        //������Ă����
//				++input_Pos;            //���͈ʒu����E��
//
//				//�����10����   �i�z���0�`9�j
//				if (input_Pos > 9) input_Pos = 9;
//
//				//�����z��ɓ���
//				InputName[input_Pos] = AllStr[movekeyY][movekeyX];
//			}
//			else if (CURSOR_NOW == CURSOR_TYPE::CANCEL)                  //�u�~�v�L�[�̏�ŉ����ꂽ�@�ꕶ���폜
//			{
//				pushFlag = true;        //������Ă����
//
//				//�ꕶ���ł����͂���Ă���Έꕶ������
//				if (InputName[input_Pos] != 0) InputName[input_Pos] = 0; //0 �͉������͂���Ă��Ȃ����
//				input_Pos--;            //���͈ʒu�������
//
//				//���͈ʒu�͍Œ�-1�܂�
//				if (input_Pos < -1) input_Pos = -1;
//			}
//			else if (CURSOR_NOW == CURSOR_TYPE::DONE)                  //�uOK�v�L�[�̏�ŉ����ꂽ�@�m��
//			{
//				//�ꕶ�������͂���Ă��Ȃ��ꍇ�͊m��ł��Ȃ�
//				if (InputName[input_Pos] != 0)
//				{
//					//�ꕶ���ł����̓A��
//					InputName[input_Pos + 1] = '\0';       //�Ō�̕����̈�E��'\0'
//
//					//�����L���O�ɃZ�b�g
//					DrawString(0, 0, "Ranking", 0xffffff);
//
//					return 1;   //�I��
//				}
//				else
//				{
//					//�_������I�@�@�Ȍ��ʉ�
//				}
//			}
//		}
//	}
//	else
//	{
//		pushFlag = false;          //������Ă��Ȃ���
//	}
//	return 0;
//}
//
////���͏��\��
//void Scene_InputName::DrawInputInfo()const
//{
//	if (InputName[0] == 0)
//	{
//		//SetDrawBlendMode
//		SetFontSize(20);
//		DrawString(200 + CENTER_X, 125 + CENTER_Y, "�E �E ���O����� �E �E", 0xffffff);
//	}
//	for (int i = 0; InputName[i] != '\0'; i++)
//	{
//		SetFontSize(30);
//		DrawFormatString((220 + 20 * i) + CENTER_X, 120 + CENTER_Y, 0xffffff, " %c", InputName[i]);
//	}
//}
//
////�V�[���̕ύX����
//AbstractScene* Scene_InputName::ChangeScene()
//{
//	//if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
//	if (KeyBoard_PushA(name) != 1)
//	{
//		KeyBoard_Update();
//	}
//	else
//	{
//		return dynamic_cast<AbstractScene*>(new SortSave(name));
//
//	}
//	return this;
//}
//
//int Scene_InputName::GetName()
//{
//	for (int j = 0; '\0' != InputName[j]; j++)
//	{
//		return InputName[j];
//	}
//}