#include "Enemy_02.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include "Jangeki_whole.h"
#include<typeinfo>
#include "Jangeki_Coming.h"
#define _USE_MATH_DEFINES
#include <math.h>

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_02::Enemy_02(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 7.0f;
	dir = 1;
	hp = 100;

	//�����_���ȍ��W�擾
	enemy_x = GetRand(1160) + 100;
	enemy_y = GetRand(600) + 100;

	image = LoadGraph("images/stage02/junp4.png");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_02::~Enemy_02()
{

}


//�X�V
void Enemy_02::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();



	//if (x + (w / 2) == (1280 - 20))
	//{
	//	dir = -1;
	//}
	//else if (x - (w / 2) == (20))
	//{
	//	dir = 1;
	//}

	//x += dir * speed;

	/********************   �W�����v�֌W   ********************/
	
	if (jump_cnt < 1)
	{
		if (GetRand(1) == 1)  //������jump_flg��true�ɂ���
		{
			jump_flg = true;
		}

		if (land_flg == true && jump_flg == true)    //jump_flg���W�����v�̏���
		{
			//g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
			jump_cnt++;
		}
	}
	
	//���ɍs��
	if (jump_cnt >= 0 && direction_flg == false && Stop_flg == false)
	{

		x = x - 5;
		if (x < 100)
		{
			image = LoadGraph("images/stage02/junp2.png");
			jump_cnt = 0;
			direction_flg = true;
			Stop_flg = true;
		}
		
		if (land_flg == true && GetRand(1) == 1)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
		{
			g_add = -30.0f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			
		}
		
		
	}
	//�E�ɍs��
	else if (jump_cnt >= 0 && direction_flg == true&&Stop_flg==false)
	{
		x = x + 5;
		if (x > 1180)
		{
			image = LoadGraph("images/stage02/junp4.png");
			jump_cnt = 0;
			direction_flg = false;
			Stop_flg = true;
		}


		if (land_flg == true && GetRand(1) == 1)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
		{
			g_add = -30.0f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

		}
		
		
	}

	//�ǂɂ�����
	if (Stop_flg == true) {
		waitTime++;
		if (waitTime > 180) {
			waitTime = 0;
			Stop_flg = false;
		}
	}
	if (Stop_flg == false) {
		y_add = (y - old_y) + g_add;  //����̗���������ݒ�

			//�������x�̐���
		if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);


		old_y = y;                    //1�t���[���O�̂����W
		y += y_add;                   //���������������W�ɉ��Z����
		g_add = _GRAVITY;              //�d�͉����x������������

	}

	////HP��70�ȉ��ɂȂ�Ǝ��̍s�����[�v�Ɉڍs
	//if (hp <= 70)
	//{
	//	attack_pattern = 1;    //�U���p�^�[����ύX
	//}

	if (hp <= 0) hp = 0;
	else if (hp <= 50) speed = 5.0f;
	/************************************************************/
}

//�`��
void Enemy_02::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	/*if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);*/

}

//����񌂐����E�X�V
void Enemy_02::Update_Jangeki()
{
	
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//�v���C���[�̍��W���Z�b�g����
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
		float radius = 35.5f;   //���a
		float speed = 2.5f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		////����
		if (frame_count % 120 == 0)
		{
			if (GetRand(0) == 0)
			{
				Jan_360degrees(jan_count, radius, speed, type);
			}
			
		}
		//����
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_whole(x, y, radius, speed, type, player_x, player_y);
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y);
		
		//�v���C���[�̊p�x�֔��˂���W����������
		if (frame_count % 75 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

		//�v���C���[��x���W�ɂ���Ĕ��˂��������ς���(���E)
		
	}
	
}

//360�x����
void Enemy_02::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	////45�x����8����
	
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
	}

	

}
//old_y�̎擾�֐�
int Enemy_02::Get_OldY()
{
	return old_y;
}

//y�̎擾�֐�
int Enemy_02::Get_Y()
{
	return y;
}


//�v���C���[�̍��W���p��
void Enemy_02::ChangeDir(float x)
{
	if (x < 640) dir = -1;
	else dir = 1;
}


