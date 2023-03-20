#pragma once
#include "Jangeki_Base.h"

class Jangeki_Spin : public Jangeki_Base
{
private:
	float angle;
	float player_x;
	float player_y;
	float rad;

public:
	//コンストラクタ
	Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y);
	~Jangeki_Spin();

	virtual void Update()override;
};


