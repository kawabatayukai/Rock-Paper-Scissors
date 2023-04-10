#pragma once
#include"EnemyBase.h"

//�s���p�^�[��02�p
struct Pattern_02 {

	int moveflg; //0:�����Ȃ�,1:����
	float location_x; //�ڎw���Ă�����Wx
	float location_y; //�ڎw���Ă�����Wy
	float waitFlameTime; //�҂�����
	int next_index; //���z��̃p�^�[���̔ԍ�

};

//2�X�e�[�W�@�G�L����
class Enemy_02 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_02(float x, float y, Jan_Type type);

	~Enemy_02();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	int Get_OldY();                   //old_y�̎擾�֐�
	int Get_Y();                      //y�̎擾

	bool Spflg = true;  //����s���t���O

	void frameUP();
	void frameDown();

	void SetSpecialTime(int Time);

	void AttackPattern_1();
	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);
	void ChangeDir(float x);//�����̐؂�ւ�
	//void ChangeDir(float x);
private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY

	float y_add = 0;          //��������
	float x_add = 1;
	float x_sdd = 1;
	float x_zdd = 1;

	float g_add = 1.0f;       //�d�͉����x
	float g_sdd = 1.0f;
	float g_zdd = 1.0f;

	
	
	bool jump_flg = false;        //�W�����v�p�t���O�@�@�W�����v������:true   �W�����v���Ȃ�:false
	bool Stop_flg = false;        //�W�����v�p�t���O�@�@�W�����v������:true   �W�����v���Ȃ�:false
	int  jump_cnt =0;            //�W�����v�J�E���g
	bool direction_flg = false;   //���E���]�t���O      ������:true   
	/**********************************************************/
	int waitTime = 5;			//�҂����ԗp�ϐ�
	int frame_count = 0;       //����񌂔��˗p
	short current = 0; //���݂̃p�^�[���z��Y��
	int  attack_pattern = 0;      //�U���p�^�[���ϐ�
	float enemy_x, enemy_y;		//���W�擾�p�ϐ�
	int janFrame = 75;
	int SpecialTime = 0;
	int jan_count;
	Pattern_02 moveinfo[2];	    //�s���p�^�[��
};


