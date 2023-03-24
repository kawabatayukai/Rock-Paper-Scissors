#include"DxLib.h"
#include"Jangeki_Vertical.h"

//	//�R���X�g���N�^                 ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�ڎw�������W �@�@�@�^�C�v
Jangeki_Vertical::Jangeki_Vertical(float x, float y, float r, float speed, float goal_y, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type), goal_y(goal_y) 
{

}

//�f�X�g���N�^
Jangeki_Vertical::~Jangeki_Vertical()
{

}

//�X�V�@���N���X��Update���Ē�`
void Jangeki_Vertical::Update()
{
	//�ڎw�����W�ƕs��v
	if (y != goal_y)
	{
		// �ڎw�����W����
		if (y < goal_y)
		{
			y += 1.0f;

			//�ڕW�𒴂����ꍇ
			if (y <= goal_y && goal_y <= (y + 1.0f) ) y = goal_y;     //�ڕW���W�ŌŒ�
		}
		else
		{
			//// �ڎw�����W����
			//if (y > goal_y)
			{
				y -= 1.0f;

				if ((y-=1.0f) <= goal_y && goal_y <= y)  y = goal_y;     //�ڕW���W�ŌŒ�
			}
		}
	}
	else
	{
		//�ڎw�����W�i���j�ƈ�v���Ă���

		x += speed;
		y -= speed_y;
	}
}