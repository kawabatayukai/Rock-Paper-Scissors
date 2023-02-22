#pragma once
#include"EnemyBase.h"

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

	int back_image;
private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p
};


