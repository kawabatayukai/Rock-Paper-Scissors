#include "MobEnemy_05.h"
#include "DxLib.h"
#include "Player.h"
#include "Jangeki_Spin.h"
//#include "Enemy_05.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#define _USE_MATH_DEFINES
#include <math.h>

MobEnemy_05::MobEnemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	hp = 100;

	Mobenemy_image = LoadGraph("images/stage05/Mobenemy_image.png", TRUE);

	Init_Jangeki();       //����񌂂�p��


}

MobEnemy_05::~MobEnemy_05()
{

}

void MobEnemy_05::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();
}

void MobEnemy_05::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, Mobenemy_image, TRUE);

	//����񌂕`��
	Draw_Jangeki();
	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);
}

void MobEnemy_05::Update_Jangeki()
{

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
		float radius = 35.5f;   //���a
		float speed = 2.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		switch (GetRand(1))
		{
		case 0:
			if (frame_count % 240 == 0) obj_jangeki[jan_count] = new Jangeki_Zigzag(x, y, radius, speed, type, player_x, player_y);
			break;

		case 1:
			if (frame_count % 240 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type, player_x, player_y);
			break;
		}

		losetimer++;

		if (Jan_loseflg == true)
		{
			if (frame_count % 60 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type, player_x, player_y);
		}
		if (losetimer > 180)
		{
			Jan_loseflg = false;
		}
	}
}

void MobEnemy_05::Janken_lose()
{
	hp = 100;

	Jan_360degrees();

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		DeleteJangeki(jan_count);
		jan_count--;
	}
	Jan_loseflg = true;
	losetimer = 0;
}

void MobEnemy_05::Janken_win()
{
	hp = hp / 2;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		DeleteJangeki(jan_count);
		jan_count--;
	}

}

void MobEnemy_05::Jan_360degrees()
{
	if (Spflg == true)
	{
		//�������邶��񌂂̔��a
		float radius = 40.f;

		for (int i = jan_count; i < (jan_count + 14); i++)
		{
			//�����_���ȑ����𐶐�
			Jan_Type type = static_cast<Jan_Type>(GetRand(2));
			double angle = static_cast<double>((30.0 * i) * (M_PI / 70));

			obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);

			if (GetRand(2) == SPcount)
			{
				Spflg = false;
				SPcount = 0;
			}
		}
	}
}
