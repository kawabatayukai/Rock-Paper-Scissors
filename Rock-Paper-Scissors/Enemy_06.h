#pragma once
#include"EnemyBase.h"

//6�X�e�[�W�@�G�L����
class Enemy_06 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_06(float x, float y, Jan_Type type);

	~Enemy_06();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void AttackPattern_1();          //�s�����[�v1
	void AttackPattern_2();          //�s�����[�v2
	void AttackPattern_3();          //�s�����[�v3
	void SpeedUp();                  //����s��1   speed = 8.0f
	void Teleportation();            //����s��2   �v���C���[�̌�����Ɉړ����A�ڋ߂��Ă���

	void AttackPattern_00();         //���s�����[�v2(�ۑ��p)

	void decision_Direction();       //�����𗐐��Ō��߂�֐�
	void jump_Direction();           //�W�����v���邩�𗐐��Ō��߂�֐�
	void jump();                     //�W�����v
	void low_jump();                 //�Ⴂ�W�����v

	float Get_OldY();                   //old_y�̎擾�֐�
	float Get_Y();                      //y�̎擾

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;              //�O��̈ʒuX
	float old_y = 0;              //�O��̈ʒuY
	float y_add = 0;              //��������
	float g_add = 1.0f;           //�d�͉����x

	/********************  �s���p�^�[���֌W  ******************/

	int  attack_pattern = 0;      //�U���p�^�[���ϐ�
	bool jump_flg = false;        //�W�����v�p�t���O�@�@       �W�����v������:true   �W�����v���Ȃ�:false
	int  jump_cnt = 0;            //�W�����v�J�E���g
	bool teleport_Flg = true;     //�u�Ԉړ��t���O              �u�Ԉړ�����:true     �u�Ԉړ����Ȃ�:false
	bool P1_side = false;         //�p�^�[��2���̈ʒu�t���O     ����:true             �E��:false
	int  floor = 5;
	int  ChangeCnt = 0;           //�G�̑����ω��܂ł̃J�E���g�p�ϐ�

	/**********************************************************/

	int frame_count = 0;          //����񌂔��˗p
	int images[3];                //�G�摜
	Jan_Type old_type;            //�O��̓G�W�����P������
};


