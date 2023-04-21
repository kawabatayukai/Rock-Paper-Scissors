#pragma once
#include"EnemyBase.h"

//�s���p�^�[��04�p
struct Pattern_04 {

	int moveflg; //0:�����Ȃ�,1:����
	float location_x; //�ڎw���Ă�����Wx
	float location_y; //�ڎw���Ă�����Wy
	float waitFlameTime; //�҂�����
	int next_index; //���z��̃p�^�[���̔ԍ�

};

//4�X�e�[�W�@�G�L����
class Enemy_04 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_04(float x, float y, Jan_Type type);

	~Enemy_04();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void Move_Pattern();

	void Change_JanType();           //�����_���ɑ����ω�

	void Special_Action();			//����s��

	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);

private:
	/********************   �W�����v�֌W   ********************/

	//float old_x = 0;          //�O��̈ʒuX
	//float old_y = 0;          //�O��̈ʒuY
	//float y_add = 0;          //��������
	//float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int waitTime = 0;				//�҂����ԗp�ϐ�
	int frame_count = 0;			//����񌂔��˗p
	Pattern_04 moveinfo[4];	    //�s���p�^�[��
	short current = 0;				//���݂̃p�^�[���z��Y��
	float enemy_x = 0;
	float enemy_y = 0;

	int enemy_image[10];			//�摜�p�ϐ�
	float angle;

	int specialTime = 0;
	bool specialFlg = false;
};


