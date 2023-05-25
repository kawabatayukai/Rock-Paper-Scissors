#include"Jangeki_Bounds.h"
#include<math.h>
#include"DxLib.h"

Jangeki_Bounds::Jangeki_Bounds(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type), move_x(0), move_y(0)
{
	speed_y = speed;

	count = 0;
}

Jangeki_Bounds::Jangeki_Bounds(float x, float y, float r, float speed,float angle,Jan_Type type, int i)
	:Jangeki_Base(x, y, r, speed, type), move_x(0), move_y(0)
{
	speed_y = speed;

	if (i == 0)
	{
		count = 3;
	}

	//x,y方向のスピードを決める
	this->speed = fabsf(speed) * cosf(static_cast<float>(angle));
	speed_y = fabsf(speed) * sinf(static_cast<float>(angle));
}

void Jangeki_Bounds::Update()
{
	x += speed;
	y -= speed_y;

	if (x <= 20 + r)
	{
		count += 1;
		speed = speed * -1;
	}
	else if (x >= 1280 - 20 - r)
	{
		count += 1;
		speed = speed * -1;
	}

	else if (y <= r)
	{
		count += 1;
		speed_y = speed_y * -1;
	}
	else if (y >= 720 - 20 - r)
	{
		count += 1;
		speed_y = speed_y * -1;
	}

	//エフェクト
	Update_Effect();
}

bool Jangeki_Bounds::CheckScreenOut()
{
	if (count == 5)return true;

	return false;
}