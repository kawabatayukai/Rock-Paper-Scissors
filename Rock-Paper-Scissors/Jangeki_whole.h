#pragma once
#include "Jangeki_Base.h"



//�����
class Jangeki_whole: public Jangeki_Base
{
public:
	//�R���X�g���N�^
	Jangeki_whole(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y);
	~Jangeki_whole();

	virtual void Update()override;
	
	
protected:
	float zigzag;
	bool flg;
	float player_x;
	float player_y;
	float rad;
	
};

