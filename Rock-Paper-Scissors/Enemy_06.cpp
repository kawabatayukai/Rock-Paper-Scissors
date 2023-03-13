#include "Enemy_06.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_06::Enemy_06(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 200;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_06::~Enemy_06()
{

}


//�X�V
void Enemy_06::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

	if (hp <= 0)hp = 0;

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

	if (attack_pattern == 0)      //�U���p�^�[��1
	{
		if (jump_cnt < 3)         //4��W�����v����܂ł̊Ԉȉ��̏������J��Ԃ�
		{
			if (GetRand(3) == 3)  //������jump_flg��true�ɂ���
			{
				jump_flg = true;
			}

			if (land_flg == true && jump_flg == true)    //jump_flg���W�����v�̏���
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
				jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
				jump_cnt++;        //�W�����v�񐔂̃J�E���g
			}
		}

		//4��ȏ�W�����v�����ۂ̏���
		if (jump_cnt >= 3 && direction_flg == false)        //���������Ă��鎞�̏���
		{

			x = x - 7;      //1�t���[���̊Ԃɍ��֐i�ދ���
			if (x < 100)    //�ڕW���W�ɓ����������̃`�F�b�N
			{
				jump_cnt = 0;          //�W�����v�񐔂̃��Z�b�g
				direction_flg = true;  //�����Ă�������̔��]
			}
		}
		else if (jump_cnt >= 3 && direction_flg == true)    //�E�������Ă��鎞�̏���
		{
			x = x + 7;      //1�t���[���̊ԂɉE�֐i�ދ���
			if (x > 1180)   //�ڕW���W�ɓ����������̃`�F�b�N
			{
				jump_cnt = 0;           //�W�����v�񐔂̃��Z�b�g
				direction_flg = false;  //�����Ă�������̔��]
			}
		}

		if (hp <= 150)
		{
			attack_pattern = 1;
			jump_cnt = 0;
			jump_flg = false;
		}
	}
	
	if (attack_pattern == 1)
	{
		if (teleport_Flg == true && direction_flg == false)
		{
			x = 1180;
			y = 450;
			direction_flg = true;
			teleport_Flg = false;
		}
		else if (teleport_Flg == true && direction_flg == true)
		{
			x = 100;
			y = 450;
			direction_flg = false;
			teleport_Flg = false;
		}

		if (direction_flg == true)
		{
			x = x - 5;

			if (GetRand(1) == 1)  //������jump_flg��true�ɂ���
			{
				jump_flg = true;
			}

			if (jump_flg == true && land_flg == true)
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
				jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
			}
		}
		else if (direction_flg == false)
		{
			if (x <= 300)
			{
				x = x + 5;
			}

			if (GetRand(1) == 1)  //������jump_flg��true�ɂ���
			{
				jump_flg = true;
			}

			if (jump_flg == true && land_flg == true)
			{
				g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
				land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
				jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
			}
		}
		
		//if (GetRand(30) == 3)  //������jump_flg��true�ɂ���
		//{
		//	jump_flg = true;
		//}

		//if (jump_flg == true && land_flg == true)    //jump_flg���W�����v�̏���
		//{
		//	g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
		//	jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
		//}
		//		
		////4��ȏ�W�����v�����ۂ̏���
		//if (direction_flg == false)        //���������Ă��鎞�̏���
		//{
		//	x = x - 20;      //1�t���[���̊Ԃɍ��֐i�ދ���
		//	if (x < 100)    //�ڕW���W�ɓ����������̃`�F�b�N
		//	{
		//		direction_flg = true;  //�����Ă�������̔��]
		//	}
		//}
		//else if (direction_flg == true)    //�E�������Ă��鎞�̏���
		//{
		//	x = x + 20;      //1�t���[���̊ԂɉE�֐i�ދ���
		//	if (x > 1180)   //�ڕW���W�ɓ����������̃`�F�b�N
		//	{
		//		direction_flg = false;  //�����Ă�������̔��]
		//	}
		//}


		if (hp <= 100)
		{
			/*attack_pattern = 2;*/
		}
	}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

}

//�`��
void Enemy_06::Draw() const
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
void Enemy_06::Update_Jangeki()
{
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

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
		float speed = -8.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}

//old_y�̎擾�֐�
int Enemy_06::Get_OldY()
{
	return old_y;
}

//y�̎擾�֐�
int Enemy_06::Get_Y()
{
	return y;
}