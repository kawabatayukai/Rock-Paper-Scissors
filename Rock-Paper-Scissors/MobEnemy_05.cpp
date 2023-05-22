#include "MobEnemy_05.h"
#include "DxLib.h"
//#include "Player.h"
#include "Jangeki_Spin.h"
//#include "Enemy_05.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#define _USE_MATH_DEFINES
#include <math.h>
#include"GameData.h"

MobEnemy_05::MobEnemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
, effect_count(0)
{
	hp = 100;

	Mobenemy_image = LoadGraph("images/stage05/Mobenemy_image.png", TRUE);

	Init_Jangeki();       //����񌂂�p��

	//�G�t�F�N�g������
	obj_effect = new Effect_Jangeki * [20];
	for (int i = 0; i < 20; i++) obj_effect[i] = nullptr;
}

MobEnemy_05::~MobEnemy_05()
{
	delete[] obj_effect;
}

void MobEnemy_05::Update()
{
	//����񌂍X�V�E����
	if (this->hp > 0)Update_Jangeki();

}

void MobEnemy_05::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, Mobenemy_image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�G�t�F�N�g
	for (int i = 0; i < 20; i++)
	{
		if (obj_effect[i] == nullptr) break;
		obj_effect[i]->Draw();
	}
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

//�G�t�F�N�g����
void MobEnemy_05::CreateEffect(_CHAR_TYPE character, Jan_Type type)
{
	if (effect_count >= 0 && effect_count < 20)
	{
		obj_effect[effect_count] = new Effect_Jangeki(x, y, type, character);
	}
}

//05��MobEnemy��p
void MobEnemy_05::Effect_MobEnemy(const Player* player)
{
	//�G�̍��W
	float e_x = this->GetX();
	float e_y = this->GetY();

	//�v���C���[�̍��W
	float p_x = player->GetX();
	float p_y = player->GetY();

	//�G�t�F�N�g�𐶐�����z��̗v�f�ԍ�

	//�G�t�F�N�g
	for (effect_count = 0; effect_count < 20; effect_count++)
	{
		if (obj_effect[effect_count] == nullptr) break;
		obj_effect[effect_count]->Update();

		if (obj_effect[effect_count]->GetCharacterType() == _CHAR_TYPE::ENEMY)
			obj_effect[effect_count]->SetCharacterLocation(player->GetX(), player->GetY());

		if (obj_effect[effect_count]->Check_PlayEnd() == true)
		{
			delete obj_effect[effect_count];
			obj_effect[effect_count] = nullptr;

			//�l�߂�
			for (int j = effect_count; j < (20 - 1); j++)
			{
				//���̗v�f�� nullptr �Ȃ炻��ȏ�͏������Ȃ�
				if (obj_effect[j + 1] == nullptr) break;

				obj_effect[j] = obj_effect[j + 1];
				obj_effect[j + 1] = nullptr;
			}
			effect_count--;
		}
	}

	//player�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** p_jan = player->GetJangeki();
	//enemy�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** e_jan = this->GetJangeki();

	//--------------------  enemy����񌂂�player  -------------------------------------
	{
		//enemy����񌂂�player�̓����蔻��
		for (int i = 0; i < JANGEKI_MAX; i++)
		{
			//��v�f�Ȃ�I��
			if (e_jan[i] == nullptr) break;

			//�����蔻��
			if (player->Hit_Jangeki(e_jan[i]) == true)
			{
				//�G�t�F�N�g����
				if (obj_effect[effect_count] == nullptr && effect_count < 20)
				{
					obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y, e_jan[i]->GetType(), _CHAR_TYPE::ENEMY);
					//effect_count++;
				}
			}
		}
	}
	//----------------------------------------------------------------------------------

	//-------------------  enemy����񌂂�player�����  ------------------------------

	for (int p = 0; p < JANGEKI_MAX; p++)
	{
		if (p_jan[p] == nullptr) break;                  //�Ȃ���Δ�����

		//enemy
		for (int e = 0; e < JANGEKI_MAX; e++)
		{
			if (e_jan[e] == nullptr) break;              //�Ȃ���Δ�����

			if (p_jan[p]->Hit_Jangeki(e_jan[e]) == true) //������
			{
				//�������̏ꍇ
				if (p_jan[p]->CheckAdvantage(e_jan[e]) == 2)
				{
					//����񌂊Ԃ̋���
					float dx = e_jan[e]->GetX() - p_jan[p]->GetX();
					float dy = e_jan[e]->GetY() - p_jan[p]->GetY();

					float jan_x = p_jan[p]->GetX() + (dx / 2);
					float jan_y = p_jan[p]->GetY() + (dy / 2);

					obj_effect[effect_count] = new Effect_Jangeki(jan_x, jan_y, e_jan[e]->GetType(), _CHAR_TYPE::NOT_CHARA);
					
					GameData::Add_PierceCount(1); //�ђʉ񐔉��Z
					GameData::Add_Score(100 / 2); //�X�R�A���Z
				}
				else if (p_jan[p]->CheckAdvantage(e_jan[e]) == 1)
				{
					GameData::Add_PierceCount(2); //�ђʉ񐔉��Z
					GameData::Add_Score(100);     //�X�R�A���Z
				}
			}
		}
	}

	//----------------------------------------------------------------------------------

}