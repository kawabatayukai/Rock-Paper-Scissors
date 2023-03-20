#pragma once
#include "Jangeki_Base.h"



//じゃん撃
class Jangeki_whole: public Jangeki_Base
{
public:
	//コンストラクタ
	Jangeki_whole(float x, float y, float r, float speed, Jan_Type type);
	~Jangeki_whole();

	virtual void Update()override;
	
	
protected:
	double angle;             //角度
	int time_counter = 0;     //追跡時間をカウント
	
};

