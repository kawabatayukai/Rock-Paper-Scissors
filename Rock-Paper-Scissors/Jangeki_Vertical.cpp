#include"DxLib.h"
#include"Jangeki_Vertical.h"

//	//コンストラクタ                 ｘ　　　　ｙ　　　半径　　スピード　　　目指すｙ座標 　　　タイプ
Jangeki_Vertical::Jangeki_Vertical(float x, float y, float r, float speed, float goal_y, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type), goal_y(goal_y) 
{

}

//デストラクタ
Jangeki_Vertical::~Jangeki_Vertical()
{

}

//更新　基底クラスのUpdateを再定義
void Jangeki_Vertical::Update()
{
	//目指す座標と不一致
	if (y != goal_y)
	{
		// 目指す座標が下
		if (y < goal_y)
		{
			y += 1.0f;

			//目標を超えた場合
			if (y <= goal_y && goal_y <= (y + 1.0f) ) y = goal_y;     //目標座標で固定
		}
		else
		{
			//// 目指す座標が上
			//if (y > goal_y)
			{
				y -= 1.0f;

				if ((y-=1.0f) <= goal_y && goal_y <= y)  y = goal_y;     //目標座標で固定
			}
		}
	}
	else
	{
		//目指す座標（ｙ）と一致してから

		x += speed;
		y -= speed_y;
	}
}