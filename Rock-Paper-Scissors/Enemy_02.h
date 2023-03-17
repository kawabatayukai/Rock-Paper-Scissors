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

	void Move_Pattern();
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
	int  Stop_cnt =0;            //�W�����v�J�E���g
	bool direction_flg = false;   //���E���]�t���O      ������:true   
	/**********************************************************/
	int waitTime = 5;			//�҂����ԗp�ϐ�
	int frame_count = 0;       //����񌂔��˗p
	Pattern_02 moveinfo[20]; //�s���p�^�[��20��
	short current = 0; //���݂̃p�^�[���z��Y��
	
};


