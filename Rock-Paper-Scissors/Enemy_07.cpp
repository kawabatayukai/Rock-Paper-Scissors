#include "Enemy_07.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include<typeinfo>

#define _USE_MATH_DEFINES
#include<math.h>

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_07::Enemy_07(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 3.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

	//�p�^�[���icsv�Ɂj
	moveinfo[0] = { 1,620.f,0.f,1 };
	moveinfo[1] = { 1,1030.f,0.f,0 };

}

//�f�X�g���N�^
Enemy_07::~Enemy_07()
{

}


//�X�V
void Enemy_07::Update()
{
	Move_Pattern();

	//����񌂍X�V�E����
	Update_Jangeki();


	/********************   �W�����v�֌W   ********************/

	if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	{
		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;             //�d�͉����x������������

	/**********************************************************/
}

//�`��
void Enemy_07::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//����񌂐����E�X�V
void Enemy_07::Update_Jangeki()
{
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//�z�[�~���O����񌂂ł���΃v���C���[�̍��W���Z�b�g����
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);

		//��ʊO�ō폜����
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ���� ���ˁE���� ���� ***********************/
	frame_count++;

	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 25.5f;   //���a
		float speed = 6.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//����
		if (frame_count % 120 == 0)
		{
			if (GetRand(1) == 0)
			{
				Jan_360degrees(jan_count, radius, speed, type);
			}
			else
			{
				obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
			}
		}
	}

}

//�s���p�^�[���ɉ������s��
void Enemy_07::Move_Pattern()
{
	//�ړ���
	float move_x = x;
	float move_y = y;

	//�ڕW���W�Ɗ��S��v�ix���W�����j
	if (x == moveinfo[current].location_x)
	{
		current = moveinfo[current].next_index;   //���̃p�^�[����
	}

	//x���W���ڕW�ƕs��v
	if (x != moveinfo[current].location_x)
	{
		//�ڕW�̕����傫���i�ڕW�͉E�����j
		if (x < moveinfo[current].location_x)
		{
			move_x += speed;      //�E�ړ��i���̒l�j

			//�ڕW�𒴂����ꍇ
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{
				move_x = moveinfo[current].location_x;     //�ڕW���W�ŌŒ�
			}
		}
		else
		{
			move_x -= speed; //���ړ��i���̒l�j

			//�ڕW�𒴂����ꍇ
			if (move_x <= moveinfo[current].location_x && moveinfo[current].location_x <= x)
			{
				move_x =  moveinfo[current].location_x;     //�ڕW���W�ŌŒ�
			}
		}
	}

	//�ړ��𔽉f
	x = move_x;
	y = move_y;
}

//360�x���ˁi�K�E�j
void Enemy_07::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	//45�x����8����
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
	}
}