#include "Jangeki_whole.h"
#include"DxLib.h"

#define _USE_MATH_DEFINES      //���w�n�}�N���̎g�p
#include<math.h>

//#define HOMING_TIME 100        //�ǐՎ���


//�R���X�g���N�^
Jangeki_whole::Jangeki_whole(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	angle = M_PI / 2;   //�����̊p�x
	
}

//�f�X�g���N�^
Jangeki_whole::~Jangeki_whole()
{
	
}

//�A�b�v�f�[�g
void Jangeki_whole::Update()
{
	
	double radius = 8;            //���邭��̔��a�i������킩��j
	x += static_cast<float>(cos(angle)) * speed;      //cos(�p�x)�@�ł����̈ړ��ʂ��v�Z
	y += static_cast<float>(sin(angle)) * speed;      //sin(�p�x)�@�ł����̈ړ��ʂ��v�Z

}
