#pragma once
#include"Jangeki_Base.h"

//
class Jangeki_Bounds : public Jangeki_Base
{
public:
	//�R���X�g���N�^  ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�^�C�v
	Jangeki_Bounds(float x, float y, float r, float speed, Jan_Type type);

	~Jangeki_Bounds() {};

	virtual void Update() override;              //�X�V�@�I�[�o�[���C�h�i�Ē�`�j

	bool CheckScreenOut() override;

private:
	double angle;             //�p�x

	float move_x; //�ړ���
	float move_y; //�ړ���

	int count;
};