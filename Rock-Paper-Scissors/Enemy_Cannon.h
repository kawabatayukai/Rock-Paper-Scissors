#pragma once
#include"Enemy_Cannon.h"
#include"EnemyBase.h"
#include"Scene_Stage08.h"

//8�X�e�[�W�@�G�L����
class Enemy_Cannon : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_Cannon(float x, float y, Jan_Type type);

	~Enemy_Cannon();                     //�f�X�g���N�^

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

	int Enemy_image;
};





