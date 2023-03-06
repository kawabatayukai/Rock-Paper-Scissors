#pragma once
#include "Jangeki_Base.h"

//スピードが変化するジャン撃
class Jangeki_Zigzag : public Jangeki_Base
{
private:
	float zigzag;
	bool flg;

public:
	//コンストラクタ
	Jangeki_Zigzag(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_Zigzag();

	virtual void Update()override;
};
