#pragma once
#include "Jangeki_Base.h"
class Jangeki_Spin :
    public Jangeki_Base
{
private:
	float UD;			//上下
	bool UDflg;
	float LR;			//左右
	bool LRflg;
	double angle;             //角度
	int time_counter;

public:
	//コンストラクタ
	Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_Spin();

	virtual void Update()override;
};

