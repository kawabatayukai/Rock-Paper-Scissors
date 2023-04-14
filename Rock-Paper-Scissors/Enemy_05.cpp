#include "Enemy_05.h"
#include "DxLib.h"
#include "Player.h"
#include "Jangeki_Base.h"
#include "Jangeki_Changespeed.h"
#include "Jangeki_Zigzag.h" 
#include "Jangeki_Spin.h" 


//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_05::Enemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;
	Movepattern = 1;
	Movetimer = 0;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

	Enemy_image = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png", TRUE);
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

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	//{
	//	//g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	g_add = -25.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//}

	Movetimer++;

	//�G�̈ړ�
	//switch (Movepattern)
	//{
	//case 1:		//�^�񒆂̑��
	//	if (x >= 650 && Movetimer >= 30)
	//	{
	//		x -= 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 2;
	//	}
	//	if (Movepattern == 2)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60)
	//	{
	//		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//	}
	//	break;

	//case 2:		//�E���̑��
	//	if (x <= 1000 && Movetimer >= 30)
	//	{
	//		x += 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 3;
	//	}
	//	if (Movepattern == 3)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 40)
	//	{
	//		g_add = -15.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//	}
	//	break;

	//case 3:		//����̑��
	//	if (x >= 300 && Movetimer >= 30)
	//	{
	//		x -= 5;

	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 4;
	//	}
	//	if (Movepattern == 4)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60 || Movetimer == 120)
	//	{
	//		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//	}
	//	break;

	//case 4:		//�^�񒆂̑��
	//	if (x <= 650 && Movetimer >= 30)
	//	{
	//		x += 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 5;
	//	}
	//	if (Movepattern == 5)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60)
	//	{
	//		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//	}
	//	break;

	//case 5:		//�E���̑��
	//	if (x >= 300 && Movetimer >= 30)
	//	{
	//		x -= 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 6;
	//	}
	//	if (Movepattern == 6)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 40)
	//	{
	//		g_add = -15.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//	}
	//	break;

	//case 6:		//�E��̑��
	//	if (x <= 1000 && Movetimer >= 30)
	//	{
	//		x += 5;
	//	}
	//	else if (Movetimer > 30)
	//	{
	//		Movepattern = 1;
	//	}
	//	if (Movepattern == 1)
	//	{
	//		Movetimer = 0;
	//	}
	//	if (land_flg == true && Movetimer == 60|| Movetimer == 120)
	//	{
	//		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//	}
	//	break;
	//}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

}

//�`��
void Enemy_05::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, Enemy_image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//����񌂐����E�X�V
void Enemy_05::Update_Jangeki()
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
		float radius = 35.5f;   //���a
		float speed = 5.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type,player_x,player_y);

	}
}