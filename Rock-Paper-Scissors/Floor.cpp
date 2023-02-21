#include"DxLib.h"
#include"Floor.h"

//�R���X�g���N�^
Floor::Floor(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{
	
}

//�R���X�g���N�^  �i�F���w��j
Floor::Floor(int x , int y, int w, int h, int color)
	: x(x), y(y), w(w), h(h), color(color)
{

}

////�R���X�g���N�^  �i�摜�̎g�p�j
Floor::Floor(const char* image_handle,int x, int y, int w, int h)
	: x(x), y(y), w(w), h(h)
{
	//�R���X�g���N�^�ŉ摜�ւ̃p�X�����炤
	if (image_handle != nullptr) image = LoadGraph(image_handle);
}

//�`��
void Floor::Draw() const
{
	//�摜�����鎞
	if (image != 0)
	{
		DrawGraph(x, y, image, TRUE);  //�摜�ŕ`��
	}
	else
	{
		//��
		DrawBox(x, y, (x + w), (y + h), color, TRUE);
	}

}