#include "Jangeki_Zigzag.h"
#include "DxLib.h"


//�R���X�g���N�^
Jangeki_Zigzag::Jangeki_Zigzag(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	zigzag = 0.f;
	flg = FALSE;
}

//�f�X�g���N�^
Jangeki_Zigzag::~Jangeki_Zigzag()
{

}

//�A�b�v�f�[�g
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