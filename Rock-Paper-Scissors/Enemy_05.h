#pragma once
#include"EnemyBase.h"
#include"MobEnemy_05.h"
#include"Jangeki_reflection.h"

//5�X�e�[�W�@�G�L����
class Enemy_05 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_05(float x, float y, Jan_Type type);

	~Enemy_05();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void GetMobEnemy(MobEnemy_05** mobenemy);

	bool respawn_mobenemy();
	void SetRespawn(bool flag);

	void Change_JanType();

	Jangeki_Reflection* reflection;

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p

	int Enemy_image;		   //�G�摜�p
	int Enemy_jamp_image;	   //�G�W�����v���摜�p
	int Movepattern;			//�����̃p�^�[��
	int Movetimer;				//�����p�̃^�C�}�[

	bool respawn;

	MobEnemy_05** mob;
};


