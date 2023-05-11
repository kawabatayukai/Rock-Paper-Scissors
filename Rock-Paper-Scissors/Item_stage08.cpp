#include"Item_stage08.h"
#include"DxLib.h"

Item_st8::Item_st8(float x, float y, float r) : Jangeki_Base(x, y, r, 0, Jan_Type::NONE)
{

}

Item_st8::~Item_st8()
{

}

void Item_st8::Update()
{

}

void Item_st8::Draw() const
{
	DrawCircle(x, y, r, 0xffffff, TRUE);
}