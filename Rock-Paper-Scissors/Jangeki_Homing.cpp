#include"DxLib.h"
#include"Jangeki_Homing.h"

#define _USE_MATH_DEFINES      //���w�n�}�N���̎g�p
#include<math.h>

#define HOMING_TIME 100        //�ǐՎ���


//�R���X�g���N�^
Jangeki_Homing::Jangeki_Homing(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)       // �����N���X�̃R���X�g���N�^���Ă�
{
	angle = M_PI / 2;   //�����̊p�x
}

//�f�X�g���N�^
Jangeki_Homing::~Jangeki_Homing()
{

}

//�X�V�@���N���X��Update���Ē�`
void Jangeki_Homing::Update()
{
	//�ǐՎ��ԓ�
	if (time_counter < HOMING_TIME)
	{
		//���ݐi��ł������
		double now_x = cos(angle);    //����
		double now_y = sin(angle);    //����

		//�{���i�ނׂ�����
		double nxt_x = static_cast<double>(target_x) - x;    //����
		double nxt_y = static_cast<double>(target_y) - y;    //����

		

		double radius = 8;            //���邭��̔��a�i������킩��j

		//�O�ς𗘗p���������^�[�Q�b�g���Ɍ�����
		if (((nxt_x * now_y) - (nxt_y * now_x)) < 0.0)
		{
			angle += M_PI / 180 * radius;
		}
		else
		{
			angle -= M_PI / 180 * radius;
		}

		time_counter++;                                   //�ǐՎ��ԃJ�E���g
	}
	x += static_cast<float>(cos(angle)) * speed;      //cos(�p�x)�@�ł����̈ړ��ʂ��v�Z
	y += static_cast<float>(sin(angle)) * speed;      //sin(�p�x)�@�ł����̈ړ��ʂ��v�Z
}