#include"DxLib.h"
#include"Floor.h"

//�R���X�g���N�^
Floor::Floor(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{
}

//�`��
void Floor::Draw() const
{
	//��
	DrawBox(x, y, (x + w), (y + h), 0xffffff, TRUE);
}