//#pragma once
//#include "AbstractScene.h"
//
////�L�[�̎��
//enum class CURSOR_TYPE
//{
//	NONE = 0,   // ����0�i�Ȃɂ�������Ă��Ȃ��j
//	NORMAL,     // A�`B,a�`b,1�`9
//	CANCEL,     //�u�~�v(�ЂƂ���)
//	DONE,       //�uOK�v(�m��)
//	MISS = 99
//};
//
//class Scene_InputName : public AbstractScene
//{
//public:
//	Scene_InputName();
//
//	/*�R���X�g���N�^*/
//	virtual ~Scene_InputName() {};
//
//	char name[11];
//
//	//�X�V
//	void Update()override;
//
//	//�`��
//	void Draw()const override;
//
//	//�V�[���̕ύX����
//	AbstractScene* ChangeScene()override;
//
//	//��������
//	void KeyBoardInit();
//
//	//�摜�ǂݍ���
//	int LoadKeyBoardImgaes();
//
//	//���ʉ��ǂݍ���
//	//int LoadSounds();
//	 
//	//�`��
//	void KeyBoard_Draw()const;
//
//	//�X�V
//	void KeyBoard_Update();
//	//�J�[�\���̈ړ��E�{�^���̒������𒲐�
//	bool CursorControl();
//
//	//A�{�^���������ꂽ���̏���  ���͂��I���� 1 ���Ԃ��Ă���
//	int KeyBoard_PushA(char* name);       //keyflg�@ ��"�����ꂽ�u��"�L�[
//
//	//���͏��\��
//	void DrawInputInfo()const;
//
//	int GetName();
//
//private:
//
//	/************* �ϐ� *************/
//	int backimage = 0;            //�w�i�摜
//	int keyboardimage = 0;        //�L�[�{�[�h�摜
//	int Cursorimage[2] = { 0 };   //�m�[�}���J�[�\���摜  0 : �ʏ펞�@�@1 : �����ꂽ�Ƃ�
//	int Cancelimage[2] = { 0 };   //  �u�~�v�J�[�\���摜
//	int OKimage[2] = { 0 };       //  �uOK�v�J�[�\���摜
//	///////////////////////////////////////////////////////////////////////////////////////
//	bool pushFlag = false;           //A���@������Ă���/������ĂȂ� �t���O    TRUE:������Ă���@FALSE:������Ă��Ȃ�
//	int frame = 0;                   //�t���[�����J�E���g
//	//�ړ���   (�L�[�{�[�h�Z�Ԗ�)
//	int movekeyX = 0;
//	int movekeyY = 0;
//	CURSOR_TYPE CURSOR_NOW = CURSOR_TYPE::NORMAL;  //���݂̃J�[�\��
//	char InputName[11];              //���͂�������������z�� 0�`9�ɕ���(10�������)�@10�Ԗڂɂ� \0 �ł�
//	int input_Pos;                   //���͒��̔z��́Z�Ԗ�
//	/********************************/
//};
//
