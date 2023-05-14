#pragma once
#include"Jangeki_Base.h"

//
class Jangeki_Bounds : public Jangeki_Base
{
public:
	//コンストラクタ  ｘ　　　　ｙ　　　半径　　スピード　　　タイプ
	Jangeki_Bounds(float x, float y, float r, float speed, Jan_Type type);

	~Jangeki_Bounds() {};

	virtual void Update() override;              //更新　オーバーライド（再定義）

	bool CheckScreenOut() override;

private:
	double angle;             //角度

	float move_x; //移動量
	float move_y; //移動量

	int count;
};