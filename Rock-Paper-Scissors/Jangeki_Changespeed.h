#pragma once
#include "Jangeki_Base.h"

//スピードが変化するジャン撃
class Jangeki_Changespeed : public Jangeki_Base
{
private:
	float acceleration;

public:
	//コンストラクタ
	Jangeki_Changespeed(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_Changespeed();

	virtual void Update()override;
};

