#include "Enemy_05.h"
#include "DxLib.h"
#include "Player.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#include "Jangeki_Spin.h" 
#include "Jangeki_Homing.h"


//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_05::Enemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type), respawn(false)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;
	Movepattern = 1;
	Movetimer = 0;
	runanimfragL = FALSE;
	runanimfragR = FALSE;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

	Enemy_imageL = LoadGraph("images/stage05/Stage5_Enemy_NoMove_L.png", TRUE);
	Enemy_imageR = LoadGraph("images/stage05/Stage5_Enemy_NoMove_R.png", TRUE);
	Enemy_barrier = LoadGraph("images/stage05/Stage5_EnemyBarrier.png", TRUE);

	LoadDivGraph("images/stage05/Stage5_enemyRun_L.png", 4, 4, 1, 100, 100, Enemy_run_L);
	LoadDivGraph("images/stage05/Stage5_enemyRun_R.png", 4, 4, 1, 100, 100, Enemy_run_R);
	reflection = new Jangeki_Reflection(x, y, h, w, Jan_Type::ROCK);
	reflection->Init_reflectionJangeki();
}

//�f�X�g���N�^
Enemy_05::~Enemy_05()
{

}


//�X�V
void Enemy_05::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();
	reflection->Update_reflection();

	/*if (x + (w / 2) == (1280 - 20))
	{
		dir = -1;
	}
	else if (x - (w / 2) == (20))
	{
		dir = 1;
	}*/

	/*x += dir * speed;*/

	///********************   �W�����v�֌W   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	//{
	//	//g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	g_add = -25.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//}



	if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0)
	{
		mob[0]->Init_Jangeki();
		mob[1]->Init_Jangeki();
		mob[2]->Init_Jangeki();

		Movetimer++;
		//�G�̈ړ�
		switch (Movepattern)
		{
		case 1:		//�^�񒆂̑��
			if (x >= 650 && Movetimer >= 30)
			{
				x -= 5;
				runanimfragL = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 2;
				dir = -1;
				runanimfragL = FALSE;
			}
			if (Movepattern == 2)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60)
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}
			break;

		case 2:		//�E���̑��
			if (x <= 1000 && Movetimer >= 30)
			{
				x += 5;
				runanimfragR = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 3;
				dir = 1;
				runanimfragR = FALSE;
			}
			if (Movepattern == 3)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 40)
			{
				g_add = -15.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}
			break;

		case 3:		//����̑��
			if (x >= 300 && Movetimer >= 30)
			{
				x -= 5;
				runanimfragL = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 4;
				dir = -1;
				runanimfragL = FALSE;
			}
			if (Movepattern == 4)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60 || Movetimer == 120)
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}
			break;

		case 4:		//�^�񒆂̑��
			if (x <= 650 && Movetimer >= 30)
			{
				x += 5;
				runanimfragR = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 5;
				dir = 1;
				runanimfragR = FALSE;
			}
			if (Movepattern == 5)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60)
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}
			break;

		case 5:		//�E���̑��
			if (x >= 300 && Movetimer >= 30)
			{
				x -= 5;
				runanimfragL = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 6;
				dir = -1;
				runanimfragL = FALSE;
			}
			if (Movepattern == 6)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 40)
			{
				g_add = -15.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}
			break;

		case 6:		//�E��̑��
			if (x <= 1000 && Movetimer >= 30)
			{
				x += 5;
				runanimfragR = TRUE;
			}
			else if (Movetimer > 30)
			{
				Movepattern = 7;
				dir = 1;
				runanimfragR = FALSE;
			}
			if (Movepattern == 1)
			{
				Movetimer = 0;
			}
			if (land_flg == true && Movetimer == 60 || Movetimer == 120)
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}
			break;

		case 7:
			//mob[1]->SetHP(-100);

			Movepattern = 1;
			respawn = true;
			Movetimer = 0;
			break;
		}
	}




	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

	animtimer++;
}

//�`��
void Enemy_05::Draw() const
{
	DrawFormatString(600, 600, 0x00ff00, "%f", player_x);
	if (runanimfragL == FALSE && runanimfragR == FALSE)
	{
		//���S����`��
		if (dir == 1) DrawRotaGraphF(x, y, 1, 0, Enemy_imageL, TRUE);
		else if (dir == -1) DrawRotaGraphF(x, y, 1, 0, Enemy_imageR, TRUE);
	}


	//�o���A�`��
	if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0){}
	else DrawRotaGraphF(x, y, 1, 0, Enemy_barrier, TRUE);
	

	//���ɑ���A�j���[�V����
	if (runanimfragL == TRUE) DrawGraph(x - 50, y - 50, Enemy_run_L[animtimer / 15 % 4], TRUE);

	//�E�ɑ���A�j���[�V����
	if (runanimfragR == TRUE) DrawGraph(x - 50, y - 50, Enemy_run_R[animtimer / 15 % 4], TRUE);


	//����񌂕`��
	Draw_Jangeki();
	reflection->Draw_reflectionJangeki();

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);


}

//����񌂐����E�X�V
void Enemy_05::Update_Jangeki()
{
	int jan_count;
	reflection->SetTargetLocation(player_x, player_y);

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
		float speed = 5.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type,player_x,player_y);

		//���˂���񌂐���
		if (reflection->GetFlg() == true)reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed - 2, type, true);
		reflection->falseFlg();
	}
}

void Enemy_05::GetMobEnemy(MobEnemy_05** mobenemy)
{
	mob = mobenemy;
}

bool Enemy_05::respawn_mobenemy()
{
	return respawn;
}

void Enemy_05::SetRespawn(bool flag)
{
	respawn = flag;
}

void Enemy_05::Change_JanType()
{
	switch (GetRand(2))
	{
	case 0:
		SetType(Jan_Type::ROCK);
		break;
	case 1:
		SetType(Jan_Type::SCISSORS);
		break;
	case 2:
		SetType(Jan_Type::PAPER);
		break;
	default:
		break;
	}
}

void Enemy_05::MoveReset()
{
	Movepattern = 1;
	Movetimer = 0;
}