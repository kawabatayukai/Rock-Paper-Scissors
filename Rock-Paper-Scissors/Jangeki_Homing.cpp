#include"DxLib.h"
#include"Jangeki_Homing.h"

#define _USE_MATH_DEFINES      //数学系マクロの使用
#include<math.h>

#define HOMING_TIME 100        //追跡時間


//コンストラクタ
Jangeki_Homing::Jangeki_Homing(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)       // ←基底クラスのコンストラクタを呼ぶ
{
	angle = M_PI / 2;   //初期の角度
}

//デストラクタ
Jangeki_Homing::~Jangeki_Homing()
{

}

//更新　基底クラスのUpdateを再定義
void Jangeki_Homing::Update()
{
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