#pragma once
#include"Enemy_Cannon.h"
#include"EnemyBase.h"
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

	int frame_count = 0;       //����񌂔��˗p

	int Enemy_image;
};
