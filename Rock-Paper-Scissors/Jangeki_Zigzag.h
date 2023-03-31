#pragma once
#include "Jangeki_Base.h"

class Jangeki_Zigzag : public Jangeki_Base
{
private:
	float zigzag;
	bool flg;
	float player_x;
	float player_y;
	float rad;

public:
	//コンストラクタ
	Jangeki_Zigzag(float x, float y, float r, float speed, Jan_Type type,float p_x, float p_y);
	~Jangeki_Zigzag();

	virtual void Update()override;
};
