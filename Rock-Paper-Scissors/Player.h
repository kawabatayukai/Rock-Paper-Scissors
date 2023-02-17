#pragma once
#include "CharaBase.h"

//�v���C���[�N���X�@CharaBase���p��
class Player : public CharaBase
{
public:
	//�R���X�g���N�^
	Player(float x, float y);
	Player(const Player& player);

	~Player();                       //�f�X�g���N�^

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

	int image = 0;  //�摜�p

	Jan_Type select_JanType;  //�I������"��"

	double jan_angle = 0;     //����񌂂̊p�x

	int image_JanType[3];     //�I������񌂉摜
};

