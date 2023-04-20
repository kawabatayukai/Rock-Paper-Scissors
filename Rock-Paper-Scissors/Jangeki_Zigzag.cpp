#include "Jangeki_Zigzag.h"
#include "DxLib.h"
#include "Scene_Stage05.h"
#include <math.h>


//�R���X�g���N�^
Jangeki_Zigzag::Jangeki_Zigzag(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y)
	:Jangeki_Base(x, y, r, speed, type), player_x(p_x), player_y(p_y)
{
	zigzag = 0.f;
	flg = FALSE;
	rad = atan2f(p_y - y, p_x - x);
}

//�f�X�g���N�^
Jangeki_Zigzag::~Jangeki_Zigzag()
{

}

//�A�b�v�f�[�g
void Jangeki_Zigzag::Update()
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

	//�G�t�F�N�g
	Update_Effect(7.0);
}