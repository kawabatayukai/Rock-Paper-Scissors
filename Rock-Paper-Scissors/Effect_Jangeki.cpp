#include"DxLib.h"
#include"Effect_Jangeki.h"

//�R���X�g���N�^
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y) : play_x(play_x), play_y(play_y), frame_count(0), index_image(0)
{
	//�摜�ǂݍ���
	LoadDivGraph("images/Effect/test_jan.png", 10, 10, 1, 180, 180, image_effect);
}

//�f�X�g���N�^
Effect_Jangeki::~Effect_Jangeki()
{

}

//�X�V
void Effect_Jangeki::Update()
{
	if (++frame_count % 3 == 0)
	{
		index_image++;
		frame_count = 0;
	}
}

//�`��
void Effect_Jangeki::Draw() const
{
	//�`��\
	if (index_image < 10)
	{
		DrawRotaGraphF(play_x, play_y, 1, 0, image_effect[index_image], TRUE);
	}
}

