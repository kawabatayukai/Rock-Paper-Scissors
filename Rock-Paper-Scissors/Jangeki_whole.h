#pragma once
#include "Jangeki_Base.h"



//�����
class Jangeki_whole: public Jangeki_Base
{
public:
	//�R���X�g���N�^
	Jangeki_whole(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_whole();

	virtual void Update()override;
	
	
protected:
	double angle;             //�p�x
	int time_counter = 0;     //�ǐՎ��Ԃ��J�E���g
	
};

