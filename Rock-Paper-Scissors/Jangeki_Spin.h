#pragma once
#include "Jangeki_Base.h"
class Jangeki_Spin :
    public Jangeki_Base
{
private:
	float UD;			//�㉺
	bool UDflg;
	float LR;			//���E
	bool LRflg;
	double angle;             //�p�x
	int time_counter;

public:
	//�R���X�g���N�^
	Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_Spin();

	virtual void Update()override;
};

