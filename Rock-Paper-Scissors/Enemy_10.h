#pragma once
#include"EnemyBase.h"

const static float V = 1.f;

/*�G�F�ړ��E�����̏��*/
struct MoveInformation10
{
	int pattern;               /*���@�E�p�^�[��*/

	//T_Location TargetLocation; /*�ړI�n*/
	//
	float x;                   /*�ړI�n X���W*/
	float y;                   /*�ړI�n Y���W*/

	int next;                  /*����(�z��)����*/

	int waitTimeFlame;         /*(�҂��Ȃ�)����*/

	int attackPattern;         /*�U�����@*/
};

//10�X�e�[�W�@�G�L����
class Enemy_10 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_10(float x, float y, Jan_Type type);

	~Enemy_10();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	/*�G�̓���*/
	void Move();

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p

	float v = V;
	float a = 0.6f;

	/*�G�F�ړ�, �ړI�n, NEXT, �҂�����, �U�����@�̔z��*/
	MoveInformation10 MoveInfo[10] = {};
};


