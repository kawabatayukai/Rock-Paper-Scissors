#include "Enemy_09.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Scene_Stage09.h"
#include"Jangeki_Homing.h"
#include"Jangeki_whole.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "SoundSystem.h"
#include"GameData.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_09::Enemy_09(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 7.0f;
	dir = 1;
	hp = 100;


	Rimage = LoadGraph("images/stage09/Stage9_1.png");	//����ON
	image = LoadGraph("images/stage09/Stage9.png");		//����OFF

	LoadDivGraph("images/stage09/teleport2.png", 15, 15, 1, 120, 150, img_teleport);
	LoadDivGraph("images/stage09/teleport22.png", 15, 15, 1, 120, 150, img_teleport2);

	LoadDivGraph("images/stage09/ref3.png", 15, 5, 3, 200, 200, refanim);


	//����񌂂�p��
	Init_Jangeki();
	reflection = new Jangeki_Reflection(x, y, w, h, Jan_Type::ROCK);
	reflection->Init_reflectionJangeki();

	SE_Teleport = LoadSoundMem("Sound/stage09/teleport.mp3");
	SE_Reflection = LoadSoundMem("Sound/stage09/reflection.mp3");

}

//�f�X�g���N�^
Enemy_09::~Enemy_09()
{

}


//�X�V
void Enemy_09::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();
	reflection->Update_reflection();

	if (Spflg == false)MoveEnmey_09();
	else  SpecialMoveEnmey();


}

//�`��
void Enemy_09::Draw() const
{

	//���S����`��
	if (animflg == false)
	{
		if (rflg == false)DrawRotaGraphF(x, y, 1, 0, Rimage, TRUE);
		if (rflg == true)DrawRotaGraphF(x, y, 1, 0, image, TRUE);
	}

	if (animflg == true)
	{
		if (anim_count == 0) DrawGraph(before_x - 65, before_y - 50, img_teleport[animtimer / 3 % 15], TRUE);
		else DrawGraph(x - 50, y - 50, img_teleport2[animtimer / 2 % 15], TRUE);
	}

	if (ranimflg == true)
	{
		DrawGraph(x - 100, y - 100, refanim[animtimer / 3 % 15], TRUE);
	}

	//����񌂕`��
	Draw_Jangeki();
	reflection->Draw_reflectionJangeki();

	//�e�X�g
	/*if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);*/


}

//����񌂐����E�X�V
void Enemy_09::Update_Jangeki()
{

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		//�z�[�~���O����񌂂ł���΃v���C���[�̍��W���Z�b�g����
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);
		reflection->SetTargetLocation(player_x, player_y);
		obj_jangeki[jan_count]->Update();
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
		float speed = 5.5f;     //�X�s�[�h

		//if (GetHP() <= 51)speed=4.5f;

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));
		/*if(GetHP()!=1)
		{
			if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
		}*/

		//�A�j���[�V�����Đ����łȂ���ΐ���
		if (animflg == false)
		{
			if (frame_count % janFrame == 0)
			{
				if (Spflg == false)
				{
					obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
					count++;
				}
				else
				{
					Jan_360degrees();
					count = 0;		 //���Z�b�g
					SPcount++;
				}
				if (count == 5)		//�܉�ڂœ���e����
				{
					Jan_40degrees();
					count = 0;		 //���Z�b�g
				}

			}

			if (ranimflg == true)
			{
				animtimer++;

				if (animtimer / 3 % 15 == 14)
				{
					animtimer = 0;
					ranimflg = false;
					Ranimflg = false;
				}

				//�Đ����ɂ�����Ə��߂���Đ�
				if (Ranimflg == true)
				{
					animtimer = 0;
					Ranimflg = false;

				}

				//���˂���񌂐���
				if (reflection->GetFlg() == true)
				{
					if (CheckSoundMem(SE_Reflection) == 0)PlaySoundMem(SE_Reflection, DX_PLAYTYPE_BACK);
					reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed - 0.3, type, true);
					reflection->falseFlg();
				}
			}
		}
	}
}


void Enemy_09::Jan_360degrees()
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

			if (Rand() == SPcount)
			{
				Spflg = false;
				SPcount = 0;
			}
		}
	}
}

int Enemy_09::Rand()
{
	int ran = GetRand(2);

	if (ran == 0)return 2;
	if (ran == 1)return 3;
	if (ran == 2)return 4;
}

void Enemy_09::Jan_40degrees()
{
	if (Spflg == false)
	{
		//�������邶��񌂂̔��a
		float radius = 35.5f;
		if (GetHP() <= 51)radius = 45.f;

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		for (int i = jan_count; i < (jan_count + 8); i++)
		{

			if (GetHP() <= 51)type = static_cast<Jan_Type>(GetRand(2));
			double angle = static_cast<double>((270.0 * i) * (M_PI / 120));

			obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);

		}
	}
}

void Enemy_09::MoveEnmey_09()
{
	interval++;
	if (GetHP() <= 51)teleport = 200;

	if (GetHP() == 1)teleport = 500;

	if (interval % teleport == 0) {

		animflg = true;
		ranimflg = false;

		if (CheckSoundMem(SE_Teleport) == 0)PlaySoundMem(SE_Teleport, DX_PLAYTYPE_BACK);


		before_x = x;
		before_y = y;

		switch (GetRand(7))
		{
			//����
		case 0:
			x = 160;
			y = 480;
			break;
		case 1:
			x = 360;
			y = 305;
			break;
		case 2:
			x = 160;
			y = 130;
			break;
			//�E��
		case 3:
			x = 1110;
			y = 480;
			break;
		case 4:
			x = 910;
			y = 305;
			break;
		case 5:
			x = 1110;
			y = 130;
			break;
			//�^��
		case 6:
			x = 620;
			y = 400;
			break;
		case 7:
			x = 620;
			y = 80;
			break;
		}
	}

	if (animflg == true)
	{

		animtimer++;

		if (animtimer / 3 % 15 == 14) {

			if (anim_count == 0)
			{
				animtimer = 0;
				anim_count = 1;
			}
			else
			{
				animtimer = 0;
				animflg = false;
				anim_count = 0;
			}

		}
	}
}

void Enemy_09::SpecialMoveEnmey()
{
	interval++;
	int Rand = 0;
	int i = 0;


	if (Spflg == true) {
		if (interval % 30 == 0) {

			animflg = true;
			ranimflg = false;

			if (CheckSoundMem(SE_Teleport) == 0)PlaySoundMem(SE_Teleport, DX_PLAYTYPE_BACK);

			before_x = x;
			before_y = y;

			switch (GetRand(7))
			{
				//����
			case 0:
				x = 160;
				y = 480;
				break;
			case 1:
				x = 360;
				y = 305;
				break;
			case 2:
				x = 160;
				y = 130;
				break;
				//�E��
			case 3:
				x = 1110;
				y = 480;
				break;
			case 4:
				x = 910;
				y = 305;
				break;
			case 5:
				x = 1110;
				y = 130;
				break;
				//�^��
			case 6:
				x = 620;
				y = 420;
				break;
			case 7:
				x = 620;
				y = 110;
				break;
			}
		}
		if (animflg == true)
		{
			animtimer++;

			if (animtimer / 1 % 15 == 14)
			{
				animtimer = 0;
				animflg = false;
			}
		}
	}
}

void Enemy_09::frameUP()
{
	if (janFrame > 25)
	{
		janFrame = janFrame - 10;
	}
}

void Enemy_09::frameDown()
{
	if (janFrame < 65)
	{
		janFrame = janFrame + 10;
	}

}

void Enemy_09::HP(bool isHard)
{
	if (isHard == false)
	{
		if (hp <= 0)
		{
			hp = 1;
		}
	}
	else return;
}

bool Enemy_09::Getflg()
{
	return rflg;
}
void Enemy_09::Tflg()
{
	rflg = true;
}
void Enemy_09::Fflg()
{
	rflg = false;
}
