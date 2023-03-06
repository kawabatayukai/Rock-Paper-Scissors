#include "Jangeki_Zigzag.h"
#include "DxLib.h"


//コンストラクタ
Jangeki_Zigzag::Jangeki_Zigzag(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	zigzag = 0.f;
	flg = FALSE;
}

//デストラクタ
Jangeki_Zigzag::~Jangeki_Zigzag()
{

}

//アップデート
void Jangeki_Zigzag::Update()
{
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

	x -= 3.f;
}