#pragma once
#include"EnemyBase.h"

//3�X�e�[�W�@�G�L����
class Enemy_03 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_03(float x, float y, Jan_Type type);

	~Enemy_03();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p
};


