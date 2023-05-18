#pragma once
#include "Jangeki_Base.h"

class Jangeki_Guard :
    public Jangeki_Base
{
private:
	float d_x;
	float d_y;

public:
	//コンストラクタ
	Jangeki_Guard(float x, float y, float r, float speed, Jan_Type type, float d_x, float d_y);
	~Jangeki_Guard();

	virtual void Update()override;

	bool CheckScreenOut() override;

};

