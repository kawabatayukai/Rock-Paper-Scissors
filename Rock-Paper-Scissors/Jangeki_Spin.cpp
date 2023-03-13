#include "Jangeki_Spin.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES      //数学系マクロの使用
#include<math.h>
#define HOMING_TIME 100        //追跡時間


Jangeki_Spin::Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	LR = 0.f;
	LRflg = FALSE;
	UD = 0.f;
	UDflg = FALSE;
	time_counter = 0;
}
Jangeki_Spin::~Jangeki_Spin()
{

}

void Jangeki_Spin::Update()
{
	if (UDflg == FALSE)
	{
		UD += 3.f;

	}
	else if (UDflg == TRUE)
	{
		UD -= 3.f;
	}


	if (UD <= -10)
	{
		UDflg = FALSE;
	}
	else if (UD >= 10)
	{
		UDflg = TRUE;
	}

	y += UD;


	if (LRflg == FALSE)
	{
		LR += 4.f;

	}
	else if (LRflg == TRUE)
	{
		LR -= 4.f;
	}


	if (LR <= -20)
	{
		LRflg = FALSE;
	}
	else if (LR >= 20)
	{
		LRflg = TRUE;
	}

	x -= 3.f;
	x += LR;

	
		//追跡時間内
	if (time_counter < HOMING_TIME)
	{
		//現在進んでいる方向
		double now_x = cos(angle);    //ｘ軸
		double now_y = sin(angle);    //ｙ軸

		//本来進むべき方向
		double nxt_x = static_cast<double>(target_x) - x;    //ｘ軸
		double nxt_y = static_cast<double>(target_y) - y;    //ｙ軸



		double radius = 8;            //くるくるの半径（見たらわかる）

		//外積を利用し向きをターゲット側に向ける
		if (((nxt_x * now_y) - (nxt_y * now_x)) < 0.0)
		{
			angle += M_PI / 180 * radius;
		}
		else
		{
			angle -= M_PI / 180 * radius;
		}

		time_counter++;                                   //追跡時間カウント
	}
	x += static_cast<float>(cos(angle)) * speed;      //cos(角度)　でｘ軸の移動量を計算
	y += static_cast<float>(sin(angle)) * speed;      //sin(角度)　でｙ軸の移動量を計算
}