#include "jangeki_Coming.h"
#include "DxLib.h"
#include "Scene_Stage04.h"
#include <math.h>


//コンストラクタ
Jangeki_Coming::Jangeki_Coming(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y)
	:Jangeki_Base(x, y, r, speed, type), player_x(p_x), player_y(p_y)
{
	rad = atan2f(p_y - y, p_x - x);
}

//デストラクタ
Jangeki_Coming::~Jangeki_Coming()
{

}

//アップデート
void Jangeki_Coming::Update()
{
	x += cosf(rad) * speed;
	y += sinf(rad) * speed;
}