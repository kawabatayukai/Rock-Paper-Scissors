#pragma once
#include "Jangeki_Base.h"

//�X�s�[�h���ω�����W������
class Jangeki_Zigzag : public Jangeki_Base
{
private:
	float zigzag;
	bool flg;

public:
	//�R���X�g���N�^
	Jangeki_Zigzag(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_Zigzag();

	virtual void Update()override;
};
