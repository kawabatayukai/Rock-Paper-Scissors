#include "Jangeki_Spin.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES      //���w�n�}�N���̎g�p
#include<math.h>
#define HOMING_TIME 100        //�ǐՎ���


Jangeki_Spin::Jangeki_Spin(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)
{
	LR = 0.f;
	LRflg = FALSE;
	UD = 0.f;
	UDflg = FALSE;
	time_counter = 0;
}
Jangeki_Spin::~Jangeki_Spin()
{

}

void Jangeki_Spin::Update()
{
	if (UDflg == FALSE)
	{
		UD += 3.f;

	}
	else if (UDflg == TRUE)
	{
		UD -= 3.f;
	}


	if (UD <= -10)
	{
		UDflg = FALSE;
	}
	else if (UD >= 10)
	{
		UDflg = TRUE;
	}

	y += UD;


	if (LRflg == FALSE)
	{
		LR += 4.f;

	}
	else if (LRflg == TRUE)
	{
		LR -= 4.f;
	}


	if (LR <= -20)
	{
		LRflg = FALSE;
	}
	else if (LR >= 20)
	{
		LRflg = TRUE;
	}

	x -= 3.f;
	x += LR;

	
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