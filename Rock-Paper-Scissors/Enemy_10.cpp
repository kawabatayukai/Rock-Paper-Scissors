#include "Enemy_10.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_10::Enemy_10(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_10::~Enemy_10()
{

}

int switchMove = 0; //��Ɨp�ϐ�

/*�G�̓���*/
void  Enemy_10::Move()
{
	/*���E�̑���ɃW�����v�ړ��̏���*/
	switch (switchMove)
	{
	case 0:
		if (x > 120) //���ֈړ�
		{
			x--;

			if (land_flg == true && x < 990 && x > 200) //�W�����v
			{
				g_add = -25.0f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}

			if (land_flg == false) //�W�����v���̉���
			{
				if (v < 15) //�������
				{
					v += a;
				}
				x -= v;
			}
		}
		else
		{
			switchMove = 1; //���̏�����
		}
		break;

	case 1:
		if (x < 1100) //�E�ֈړ�
		{
			x++;

			if (land_flg == true && x > 200 && x < 1000) //�W�����v
			{
				g_add = -25.0f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			}

			if (land_flg == false) //�W�����v���̉���
			{
				if (v < 15) //�������
				{
					v += a;
				}
				x += v;
			}
		}
		else
		{
			switchMove = 0; //���̏�����
		}
		break;
	}

	/*�G���ڂ̑����ω�*/
	//e_type = Jan_Type::PAPER;

	/********************   �W�����v�֌W   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	//{
		//g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		//land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/
}

//�X�V
void Enemy_10::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

	Move();

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
	//	g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//}
	//
	//y_add = (y - old_y) + g_add;  //����̗���������ݒ�
	//
	////�������x�̐���
	//if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);
	//
	//old_y = y;                    //1�t���[���O�̂����W
	//y += y_add;                   //���������������W�ɉ��Z����
	//g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

}

//�`��
void Enemy_10::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);
	DrawFormatString(500, 200, 0xffffffff, "%f", x);

}

//����񌂐����E�X�V
void Enemy_10::Update_Jangeki()
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
		float speed = /* - */3.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		/*********************** ���� ����( �ʏ�e ) ���� ***********************/

		//            �������x
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type); //�ʏ�e

		/************************************************************************/

		/*********************** ���� ����( �ǐՒe ) ���� ***********************/

		//            �������x
		if (frame_count % 50 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type); //�ǐՒe 

		/************************************************************************/
	}
}