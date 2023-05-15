#pragma once
#include"Jangeki_Base.h"

//����񂯂�̏��
enum class Jan_State
{
	BEFORE,      //����񂯂�O(�������Ă��Ȃ�)
	PROGRESS,    //����񂯂񒆁E�E
	AFTER,       //����񂯂�I���i���ʂ��擾�\�j

	START,       //�X�^�[�g�i���������u�Ԃ̉��o�j
	END,         //�I���i�I��������o�j
};

// �ڐG���̂���񂯂�  ���s�����߂�N���X
class Janken
{
public:
	//�R���X�g���N�^   �G�̏o��������炤
	Janken(Jan_Type enemy_jan, const int stage_num = 0);

	~Janken();            //�f�X�g���N�^

	void Update();        //�X�V
	void Draw() const;    //�`��

	Jan_Result GetResult() const { return result; }  //����񂯂�̌��ʂ�Ԃ�

	//(�������̎��p) �K�v�ȕϐ�������������
	void OneMore_Init();

private:

	//B�i�O�[�j,Y�i�`���L�j,X�i�p�[�j�̂����ꂩ�������ꂽ�u�ԁAtrue��Ԃ�
	bool Check_AnyButton();

	//"�ڐG������񂯂�"����
	//   Check_AnyButton() �ŉ����ꂽ�{�^���� enemy�i�����j�̏��s���ʂ�Ԃ� (�����ꂽ�{�^���ڐ�)
	Jan_Result Get_JankenResult();

private:
	bool button_B = false;   //B�{�^����������Ă��邩
	bool button_Y = false;   //Y�{�^����������Ă��邩
	bool button_X = false;   //X�{�^����������Ă��邩

	Jan_Type enemy_jan;      //�G�̏o����@�R���X�g���N�^�ł��炤
	Jan_Type player_jan;     //�v���C���[�̏o����  Check_AnyButton()�ŉ����ꂽ�{�^��

	Jan_Result result;       // ����񂯂�̌��ʂ��i�[����

	int time = 0;            //�J�E���^�[
	int p_image_x;           //�v���C���[�`�悘���W
	int e_image_x;           //�G�`�悘���W


//---------------------------------------------------------------
	int image[3];            //�摜
	int image_back;          //����񂯂񒆔w�i
	int image_back_light;    //����񂯂�"VS"

	int image_hand;          //����񂯂����
	int image_player;        //�v���C���[����񂯂�
	int image_enemy;         //�G����񂯂�

	int image_all_enemy[11]; //�S�X�e�[�W�̉摜
	int image_all_back[11];  //�S�X�e�[�W�̔w�i
	int stage_num;           //�Ăяo�����̃X�e�[�W�ԍ�

	int font_result;         //����(WIN or LOSE or ONEMORE) �p�t�H���g 
	int font_other;          //�u����񂯂�..�v,�u�ۂ�v�ȂǗp�t�H���g

	//�F
	int blue;
	int red;
	int brack;
	int white;
	int green;
};
