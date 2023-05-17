#include "Janken_Star.h"
#include "DxLib.h"
#include<math.h>

Janken_Star::Janken_Star(const float& x, const float& y, const float& targetX, const float& targetY)
	:x(x), y(y), speed(13.0f), rate(0.0)
{
	image = LoadGraph("images/Janken/star.png");
	angle = atan2f(targetY - y, targetX - x);
	type = GetRand(100) + 120;
}

Janken_Star::~Janken_Star()
{
}

void Janken_Star::Update()
{
	x += cosf(angle) * speed;
	y += sinf(angle) * speed;

	if (type > 110) rate += 0.1;
	else rate -= 0.1;
}

void Janken_Star::Draw() const
{

	SetDrawBlendMode(DX_BLENDMODE_ADD, type);
	SetDrawBright(255, 165, 0);
	DrawRotaGraph(x, y, 1.2, rate, image, TRUE);
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);
	DrawRotaGraph(x, y, 1.0, rate, image, TRUE);
}

bool Janken_Star::CheckScreenOut()
{
	if (x < -50 || x > 1330 || y < -50 || y > 780) return true;
	return false;
}
