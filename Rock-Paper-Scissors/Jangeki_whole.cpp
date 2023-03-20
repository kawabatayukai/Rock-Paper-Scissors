#include "Jangeki_whole.h"
#include"DxLib.h"
#include<math.h>
#include "Scene_Stage02.h"

//コンストラクタ
Jangeki_whole::Jangeki_whole(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y)
	:Jangeki_Base(x, y, r, speed, type)
{
	zigzag = 0.f;
	flg = FALSE;
	rad = atan2f(p_y - y, p_x - x);
	
}

//デストラクタ
Jangeki_whole::~Jangeki_whole()
{
	
}

//アップデート
void Jangeki_whole::Update()
{
	x += cosf(rad) * speed;
	y += sinf(rad) * speed;

	if (flg == FALSE)
	{
		zigzag += 3.f;

	}
	else if (flg == TRUE)
	{
		zigzag -= 3.f;
	}


	if (zigzag <= -10)
	{
		flg = FALSE;
	}
	else if (zigzag >= 10)
	{
		flg = TRUE;
	}

	y += zigzag;

}
