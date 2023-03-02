#pragma once
#include"EnemyBase.h"

//�s���p�^�[��07�p
struct Pattern_07
{
	int moveflag;       //0:�����Ȃ��@1:����
	float location_x;   //�ڕW���W��
	float location_y;   //�ڕW���W��


	int next_index;     //���̔z��(�p�^�[��)�ԍ�
};

//7�X�e�[�W�@�G�L����
class Enemy_07 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_07(float x, float y, Jan_Type type);

	~Enemy_07();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void Move_Pattern();             //�s���p�^�[���ɉ������s��

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p

	Pattern_07 moveinfo[20];   //�s���p�^�[��
	short current = 0;         //���݂̃p�^�[���z��Y��
};


