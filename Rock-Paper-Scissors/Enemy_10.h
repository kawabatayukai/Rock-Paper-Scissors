#pragma once
#include"EnemyBase.h"
#include"Jangeki_reflection.h"
#include"Jangeki_Base.h"
#include"Player.h"
//#include "Scene_Stage10.h"

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

	/*�摜�̕ύX�擾*/
	void EnemySwitch();

	/*�摜�̓���ύX*/
	void EnemyChangeMoveimg();

	int Get_Enemy10Form();

	void Interval();

	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);

	void HP();

	bool Getflg();
	void Tflg();
	void Fflg();

	Jangeki_Reflection* reflection;

	//Scene_Stage10* obj_floor;

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

	int form;

	int image[10]; //�摜

	int Rimage;
	int Limage;

	int jangeki_Set; //����񌂃Z�b�g�p�ϐ�

	int jan_count;

	int enemy_Image; //�摜�̔z��ێ�

	int enemyGetMove;   //�ړ��ێ�

	int enemyCount; //�摜�̃t���[���J�E���g

	int enemyChange_Image; //�摜�ύX

	int pCount; //�Ō�̉摜

	bool rflg = false; //���˗p

	int locationNum; /*�J��Ԃ��ړ��p�̍��W�̔ԍ�������*/

	int current = 0; /*�����p�ԍ��̕ϐ�*/

	int waitCount = 0; /*��؎���*/

	//�����i���E�̂݁j
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
	};

	/*�G�F�ړ�, �ړI�n, NEXT, �҂�����, �U�����@�̔z��*/
	MoveInformation10 MoveInfo[10] = {};

	/*�G�F�ړ������E�U���̕��@�A�p�^�[���̃t�@�C���ǂݍ���*/
	void InputCSV(const char* passCSV);
};


