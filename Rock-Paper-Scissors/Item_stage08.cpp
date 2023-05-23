#include"Item_stage08.h"
#include"DxLib.h"

Item_st8::Item_st8(float x, float y, float r) : Jangeki_Base(x, y, r, 0, Jan_Type::NONE)
{
	image = LoadGraph("images/stage08/stage08_Item.png");
}

Item_st8::~Item_st8()
{

}

void Item_st8::Update()
{

}

void Item_st8::Draw() const
{
	//Šg‘å—¦
	double rate = (static_cast<double>(r) * 2) / 100;

	DrawRotaGraph(x, y, rate, 0, image, TRUE);
}
