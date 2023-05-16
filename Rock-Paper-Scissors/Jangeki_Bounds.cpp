#include"Jangeki_Bounds.h"
#include"DxLib.h"

Jangeki_Bounds::Jangeki_Bounds(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type), move_x(0), move_y(0)
{
	speed_y = speed;

	count = 0;
}

void Jangeki_Bounds::Update()
{
	x += speed;
	y += speed_y;

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

	if (y <= r)
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