#pragma once
#include "Jangeki_Base.h"

//スピードが変化するジャン撃
class Jangeki_Coming : public Jangeki_Base
{
private:
	float player_x;
	float player_y;
	float rad;

public:
	//コンストラクタ
	Jangeki_Coming(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y);
	~Jangeki_Coming();

	virtual void Update()override;
};