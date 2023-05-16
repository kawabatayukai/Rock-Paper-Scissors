#include "Jangeki_Spin.h"
#include "Jangeki_Zigzag.h"
#include "DxLib.h"
#include "Scene_Stage05.h"
#include <math.h>


//�R���X�g���N�^
Jangeki_Spin::Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y)
	:Jangeki_Base(x, y, r, speed, type), player_x(p_x), player_y(p_y)
{
	angle = 0.f;
	rad = atan2f((p_y - y)/100, (p_x - x)/100);
}

//�f�X�g���N�^
Jangeki_Spin::~Jangeki_Spin()
{

}

//�A�b�v�f�[�g
void Jangeki_Spin::Update()
{
	angle += 1.f;

	//�v���C���[�̕����ɔ�΂�
	x += cosf(rad) * speed;
	y += sinf(rad) * speed;

	//��]������
	x = x + r * cosf(angle);
	y = y + r * sinf(angle);

	//�G�t�F�N�g
	Update_Effect(7.0);
}