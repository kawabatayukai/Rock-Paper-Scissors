#include "Jangeki_Changespeed.h"
#include "DxLib.h"

//コンストラクタ
Jangeki_Changespeed::Jangeki_Changespeed(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	acceleration = 0.f;
}

//デストラクタ
Jangeki_Changespeed::~Jangeki_Changespeed()
{

}

//アップデート
void Jangeki_Changespeed::Update()
{
	acceleration += 0.2;
	x -=acceleration;

	//エフェクト
	Update_Effect(6.0);
}