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

	void decision_Direction();       //�����𗐐��Ō��߂�֐�
	void jump_Direction();           //�W�����v���邩�𗐐��Ō��߂�֐�
	void jump();                     //�W�����v
	void low_jump();                 //�Ⴂ�W�����v
	void smoke();                    //���G�t�F�N�g�֐�

	float Get_OldY();                   //old_y�̎擾�֐�
	float Get_Y();                      //y�̎擾
	int   Get_smokeflg();               //���G�t�F�N�g�̃t���O�̎擾
	float GetSpeed();                   //�X�s�[�h�擾

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
	bool attack1_InitFlg = false; //�U���p�^�[��1�̏������t���O
	bool attack2_Flg = true;      //�U���p�^�[��2�J�n�O�t���O  ������:true       �������I��:false
	bool P1_side = false;         //�p�^�[��2���̈ʒu�t���O      ����:true             �E��:false
	int  floor = 5;
	int  ChangeCnt = 0;           //�G�̑����ω��܂ł̃J�E���g�p�ϐ�

	int  SpeedUpTime = 0;         //SpeedUp���̃J�E���g

	bool TeleportFlg = false;     //�u�Ԉړ��ڐG�����t���O     �u�Ԉړ��ڐG:true    ����ȊO:false
	bool TeleportInit = true;     //�u�Ԉړ��ڐG�����������t���O     ������:true  �������I��:false
	int  TeleportTime = 0;        //�u�Ԉړ��J�n�܂ł̃J�E���g

	bool smokeFlg = true;         //���G�t�F�N�g�̃t���O
	int  smokeImage[10];          //���摜
	int  smokeCnt = 0;            //���p�J�E���g�ϐ�

	/**********************************************************/

	int frame_count = 0;          //����񌂔��˗p
	int images[12];                //�G�摜
	float bef_x = 0;              //�O���x���W(�摜�\���p)
	float bef_y = 0;              //�O���y���W(�摜�\���p)
	Jan_Type old_type;            //�O��̓G�W�����P������
};