#pragma once
#include "Jangeki_Base.h"

//�X�s�[�h���ω�����W������
class Jangeki_Changespeed : public Jangeki_Base
{
private:
	float acceleration;

public:
	//�R���X�g���N�^
	Jangeki_Changespeed(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_Changespeed();

	virtual void Update()override;
};

