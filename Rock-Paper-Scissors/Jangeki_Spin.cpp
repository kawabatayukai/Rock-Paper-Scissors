#include "Jangeki_Spin.h"
#include "Jangeki_Zigzag.h"
#include "DxLib.h"
#include "Scene_Stage05.h"
#include <math.h>


//コンストラクタ
Jangeki_Spin::Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y)
	:Jangeki_Base(x, y, r, speed, type), player_x(p_x), player_y(p_y)
{
	angle = 0.f;
	rad = atan2f((p_y - y)/100, (p_x - x)/100);
}

//デストラクタ
Jangeki_Spin::~Jangeki_Spin()
{

}

//アップデート
void Jangeki_Spin::Update()
{
	angle += 1.f;

	//プレイヤーの方向に飛ばす
	x += cosf(rad) * speed;
	y += sinf(rad) * speed;

	//回転させる
	x = x + r * cosf(angle);
	y = y + r * sinf(angle);

	//エフェクト
	Update_Effect(7.0);
}