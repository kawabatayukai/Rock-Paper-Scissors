#include "Jangeki_Changespeed.h"
#include "DxLib.h"

//�R���X�g���N�^
Jangeki_Changespeed::Jangeki_Changespeed(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	acceleration = 0.f;
}

//�f�X�g���N�^
Jangeki_Changespeed::~Jangeki_Changespeed()
{

}

//�A�b�v�f�[�g
void Jangeki_Changespeed::Update()
{
	acceleration += 0.2;
	x -=acceleration;
}