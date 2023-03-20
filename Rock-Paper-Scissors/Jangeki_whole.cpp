#include "Jangeki_whole.h"
#include"DxLib.h"

#define _USE_MATH_DEFINES      //数学系マクロの使用
#include<math.h>

//#define HOMING_TIME 100        //追跡時間


//コンストラクタ
Jangeki_whole::Jangeki_whole(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	angle = M_PI / 2;   //初期の角度
	
}

//デストラクタ
Jangeki_whole::~Jangeki_whole()
{
	
}

//アップデート
void Jangeki_whole::Update()
{
	
	double radius = 8;            //くるくるの半径（見たらわかる）
	x += static_cast<float>(cos(angle)) * speed;      //cos(角度)　でｘ軸の移動量を計算
	y += static_cast<float>(sin(angle)) * speed;      //sin(角度)　でｙ軸の移動量を計算

}
