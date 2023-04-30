#include"DxLib.h"
#include"Effect_Jangeki.h"

//�R���X�g���N�^
Effect_Jangeki::Effect_Jangeki(float play_x, float play_y)
	: play_x(play_x), play_y(play_y)
	, frame_count(0), index_effect(0), index_max(0), image_effect(nullptr), finish_effect(false)
{
	//�ő吔�Z�b�g
	index_max = 10;
	image_effect = new int[index_max];

	//�����ǂݍ���
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
		//�Ō�܂ōĐ�
		if (++index_effect > index_max) finish_effect = true;
	}
}

//�`��
void Effect_Jangeki::Draw() const
{
	DrawRotaGraph(play_x, play_y, 1, 0, image_effect[index_effect], TRUE);
}

//�Đ��I�� true
bool Effect_Jangeki::Check_PlayEnd()
{
	return finish_effect;
}

