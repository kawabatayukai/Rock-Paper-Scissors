#pragma once
#include"EnemyBase.h"

//�s���p�^�[��03�p
struct Pattern_03 {

	int moveflg; //0:����,1:�����Ȃ�
	float location_x; //�ڎw���Ă�����Wx
	float location_y; //�ڎw���Ă�����Wy
	int next_index; //���z��̃p�^�[���̔ԍ�
	int enemywaitTime;//�G�l�~�[�̑҂�����
	int jumpflg; //�W�����v���邩���Ȃ���

};

//3�X�e�[�W�@�G�L����
class Enemy_03 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_03(float x, float y, Jan_Type type);

	~Enemy_03();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;    //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void Move_Pattern();//�����̃p�^�[��

	int GetWaitTime()const;//�҂����Ԃ̎擾

	void ChangeDir(float enemy_x);//�����̐؂�ւ�

	float Get_OldY() const { return old_y; } //Y���W�̎擾


private:
	/********************   �W�����v�֌W   ********************/

	//float old_x = 0; 

	//�O��̈ʒuX
	float old_x = 0;    //�O��̈ʒuX
	float old_y = 0;	//�O��̈ʒuY
	float y_add = 0;     //��������  
	float g_add = 1.0f;//�d�͉����x
	


	/**********************************************************/
	int frame_count ;       //����񌂔��˗p

	int waitcount ;//�҂����ԃJ�E���g

	Pattern_03 moveinfo[40]; //�s���p�^�[��50��
	short current ; //���݂̃p�^�[���z��Y��

	int enemyimage[3];      //�G�摜�z��
};


