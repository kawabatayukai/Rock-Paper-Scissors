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

private:
	/********************   �W�����v�֌W   ********************/

	//float old_x = 0;          //�O��̈ʒuX
	//float old_y = 0;          //�O��̈ʒuY
	//float y_add = 0;          //��������
	//float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int waitTime;				//�҂����ԗp�ϐ�
	int frame_count;			//����񌂔��˗p
	Pattern_04 moveinfo[20];	//�s���p�^�[��20��
	short current;				//���݂̃p�^�[���z��Y��
};


