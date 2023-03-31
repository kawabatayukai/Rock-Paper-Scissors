#pragma once
#include"Jangeki_Base.h"

//縦方向に並びたいじゃん撃
class Jangeki_Vertical : public Jangeki_Base
{
public:
	//コンストラクタ  ｘ　　　　ｙ　　　半径　　スピード　　　目指すｙ座標 　　　タイプ
	Jangeki_Vertical(float x, float y, float r, float speed, float goal_y, Jan_Type type);

	~Jangeki_Vertical();

	virtual void Update() override;              //更新　オーバーライド（再定義）


private:
	/* 座標系、スピード　などの変数は
		  基底クラス Jangeki_Base に protected の状態であります   */

	float goal_y;
};