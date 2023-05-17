#include "Jangeki_Guard.h"
#include"DxLib.h"


//�R���X�g���N�^
Jangeki_Guard::Jangeki_Guard(float x, float y, float r, float speed, Jan_Type type, float d_x, float d_y)
	:Jangeki_Base(x, y, r, speed, type), d_x(d_x), d_y(d_y)
{

}

//�f�X�g���N�^
Jangeki_Guard::~Jangeki_Guard()
{
	
}

//�A�b�v�f�[�g
void Jangeki_Guard::Update()
{
	x = enemy_x + d_x;
	y = enemy_y + d_y;

	static int fcount;

	fcount++;

	if (fcount >= 60)
	{
		speed = 0;
	}

	//�G�t�F�N�g
	Update_Effect();
}

bool Jangeki_Guard::CheckScreenOut()
{
	return false;
}