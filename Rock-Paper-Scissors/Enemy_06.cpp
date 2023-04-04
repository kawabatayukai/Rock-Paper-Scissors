#include "Enemy_06.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_06::Enemy_06(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = -1;                 //-1�Ȃ獶����  +1�Ȃ�E����
	hp = 100;

	images[0] = LoadGraph("images/gu-test.png");
	images[1] = LoadGraph("images/tyokitest.png");
	images[2] = LoadGraph("images/pa-test.png");

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

	//�U���p�^�[��1
	if (attack_pattern == 0)
	{
		AttackPattern_1();
	}
	
	//�U���p�^�[��2
	if (attack_pattern == 1)
	{
		AttackPattern_2();
	}

	//�U���p�^�[��3
	if (attack_pattern == 2)
	{
		AttackPattern_3();
	}

	/********************   �W�����v�֌W   ********************/

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
	//�O�[�����̎��A�Ԃ��L�����摜��\��
	if (GetType() == static_cast<Jan_Type>(0))
	{
		//���S����`��
		DrawRotaGraphF(x, y, 1, 0, images[0], TRUE, dir == -1 ? 0 : 1);
	}

	//�`���L�����̎��A���F���L�����摜��\��
	if (GetType() == static_cast<Jan_Type>(1))
	{
		//���S����`��
		DrawRotaGraphF(x, y, 1, 0, images[1], TRUE, dir == -1 ? 0 : 1);
	}

	//�p�[�����̎��A���L�����摜��\��
	if (GetType() == static_cast<Jan_Type>(2))
	{
		//���S����`��
		DrawRotaGraphF(x, y, 1, 0, images[2], TRUE, dir == -1 ? 0 : 1);
	}

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
		float speed = 3.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//�s���p�^�[��1�̎��̒e(speed = 3.0f  frame_count % 80)
		if (attack_pattern == 0)
		{
			//�v���C���[�����Ɍ������Ĕ��˂����W�������̐���
			if (frame_count % 80 == 0) obj_jangeki[jan_count] = 
				new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
		}

		//�s���p�^�[��2�̎��̒e(speed = 3.0f  frame_count % 80)
		if (attack_pattern == 1)
		{
			//�v���C���[�����Ɍ������Ĕ��˂����W�������̐���
			if (frame_count % 80 == 0) obj_jangeki[jan_count] =
				new Jangeki_Coming(x, y, radius, speed + 1.0f, type, player_x, player_y);
		}

		//�s���p�^�[��3�̎��̒e(speed = 3.0f  frame_count % 80)
		if (attack_pattern == 2)
		{
			//�v���C���[�����Ɍ������Ĕ��˂����W�������̐���
			if (frame_count % 70 == 0) obj_jangeki[jan_count] =
				new Jangeki_Coming(x, y, radius, speed + 1.0f, type, player_x, player_y);
		}
	}
}

//�s�����[�v1
void Enemy_06::AttackPattern_1()
{
	//4��W�����v����܂ł̊Ԉȉ��̏���(�W�����v)���J��Ԃ�
	if (jump_cnt < 3)         
	{
		if (GetRand(3) == 3)  //������jump_flg��true�ɂ���
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();
	}

	//4��ȏ�W�����v�����ۂ̏���
	if (jump_cnt >= 3 && dir == -1)        //���������Ă��鎞�̏���
	{

		x = x - 5;      //1�t���[���̊Ԃɍ��֐i�ދ���
		if (x < 100)    //�ڕW���W�ɓ����������̃`�F�b�N
		{
			jump_cnt = 0;          //�W�����v�񐔂̃��Z�b�g
			dir = 1;  //�����Ă�������̔��]
			ChangeCnt++;
		}
	}
	else if (jump_cnt >= 3 && dir == 1)    //�E�������Ă��鎞�̏���
	{
		x = x + 5;      //1�t���[���̊ԂɉE�֐i�ދ���
		if (x > 1180)   //�ڕW���W�ɓ����������̃`�F�b�N
		{
			jump_cnt = 0;           //�W�����v�񐔂̃��Z�b�g
			dir = -1;  //�����Ă�������̔��]
			ChangeCnt++;
		}
	}

	//�G�̑����ω�����
	if (ChangeCnt > 4)
	{
		SetType(static_cast<Jan_Type>(GetRand(2)));
		ChangeCnt = 0;
	}

	//HP��70�ȉ��ɂȂ�Ǝ��̍s�����[�v�Ɉڍs
	if (hp <= 70)
	{
		attack_pattern = 1;    //�U���p�^�[����ύX
		teleport_Flg = true;   //�u�Ԉړ��t���O��true�ɂ���
		//jump_cnt = 0;          //�W�����v�J�E���g������
		//jump_flg = false;      //�W�����v�t���O������
	}
}

//�s�����[�v2
void Enemy_06::AttackPattern_2()
{
	//�U���p�^�[��2��������
	if (teleport_Flg == true)
	{
		x = 1149;
		y = 450;
		floor = 5;
		dir = -1;
		teleport_Flg = false;
		jump_cnt = 0;
	}

	//�����Ƃ̏���
	switch (floor)
	{
	case 1:
		if (dir == 1)
		{
			x += 5;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x >= 393)
		{
			floor = 2;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= 5;
		}
		if (dir == 1)
		{
			x += 5;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 141)
		{
			floor = 1;
			jump_cnt = 0;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= 5;
		}
		if (dir == 1)
		{
			x += 5;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 393)
		{
			floor = 2;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= 5;
		}
		if (dir == 1)
		{
			x += 5;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 645)
		{
			floor = 3;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 1149)
		{
			floor = 5;
			jump_cnt = 0;
			dir = -1;
			jump_Direction();
		}

		break;

	case 5:
		if (dir == -1)
		{
			x -= 5;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
			jump_cnt++;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 897)
		{
			floor = 4;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;
	}



	//�G�̑����ω�����
	if (ChangeCnt > 7)
	{
		SetType(static_cast<Jan_Type>(GetRand(2)));
		ChangeCnt = 0;
	}

	//HP��40�ȉ��ɂȂ�Ǝ��̍s�����[�v�Ɉڍs
	if (hp <= 40)
	{
		attack_pattern = 2;
	}
}

//�s�����[�v3
void Enemy_06::AttackPattern_3()
{
	//�����Ƃ̏���
	switch (floor)
	{
	case 1:
		if (dir == 1)
		{
			x += 8;
		}
		
		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x >= 393)
		{
			floor = 2;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= 8;
		}
		if (dir == 1)
		{
			x += 8;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 141)
		{
			floor = 1;
			jump_cnt = 0;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= 8;
		}
		if (dir == 1)
		{
			x += 8;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 393)
		{
			floor = 2;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= 8;
		}
		if (dir == 1)
		{
			x += 8;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 645)
		{
			floor = 3;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 1149)
		{
			floor = 5;
			jump_cnt = 0;
			dir = -1;
			jump_Direction();
		}

		break;

	case 5:
		if (dir == -1)
		{
			x -= 8;
		}

		if (y == 450 && jump_cnt == 0)
		{
			jump_flg = true;
			jump_cnt++;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 897)
		{
			floor = 4;
			jump_cnt = 0;
			decision_Direction();
			jump_Direction();
		}

		break;
	}



	//�G�̑����ω�����
	if (ChangeCnt > 5)
	{
		SetType(static_cast<Jan_Type>(GetRand(2)));
		ChangeCnt = 0;
	}
}

//���s�����[�v2(�ۑ��p)
void Enemy_06::AttackPattern_00()
{
	//if (teleport_Flg == true && dir == -1)
	//{
	//	x = 1180;
	//	y = 450;
	//	dir = -1;
	//	teleport_Flg = false;
	//	P1_side = false;
	//	jump_cnt = 0;
	//}
	//else if (teleport_Flg == true && dir == 1)
	//{
	//	x = 100;
	//	y = 450;
	//	dir = 1;
	//	teleport_Flg = false;
	//	P1_side = true;
	//	jump_cnt = 0;
	//}



	//if (P1_side == false)
	//{
	//	//���̑���փW�����v
	//	if (x >= 930 && dir == 1)
	//	{
	//		x = x - 6;
	//	}
	//	else if (x <= 1180 && dir == 1)
	//	{
	//		dir = -1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//�E�̑���փW�����v
	//	if (x <= 1180 && dir == -1)
	//	{
	//		x = x + 6;
	//	}
	//	else if (x >= 930 && dir == -1)
	//	{
	//		dir = 1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//�u�Ԉړ�
	//	if (jump_cnt == 5)
	//	{
	//		teleport_Flg = true;
	//		dir = 1;
	//		ChangeCnt++;
	//	}

	//	//�W�����v����
	//	jump();
	//}

	//else if (P1_side == true)
	//{
	//	//�E�̑���փW�����v
	//	if (x <= 350 && dir == -1)
	//	{
	//		x = x + 6;
	//	}
	//	else if (x >= 100 && dir == -1)
	//	{
	//		dir = 1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//���̑���փW�����v
	//	if (x >= 100 && dir == 1)
	//	{
	//		x = x - 5;
	//	}
	//	else if (x <= 350 && dir == 1)
	//	{
	//		dir = -1;
	//		jump_flg = true;
	//		jump_cnt++;
	//	}

	//	//�u�Ԉړ�
	//	if (jump_cnt == 5)
	//	{
	//		teleport_Flg = true;
	//		dir = -1;
	//		ChangeCnt++;
	//	}

	//	//�W�����v����
	//	jump();
	//}
}

//�W�����v
void Enemy_06::jump()
{
	//�W�����v����
	if (jump_flg == true && land_flg == true)
	{
		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
		jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g

		if (attack_pattern == 0)
		{
			jump_cnt++;        //�W�����v�񐔂̃J�E���g
		}

		if (attack_pattern == 2)
		{
			ChangeCnt++;       //�����ω��܂ł̃J�E���g
		}
	}
}

//�����𗐐��Ō��߂�֐�
void Enemy_06::decision_Direction()
{
	if (GetRand(1) == 1)
	{
		dir = -1;
	}
	else
	{
		dir = 1;
	}
}

//�W�����v���邩�𗐐��Ō��߂�֐�
void Enemy_06::jump_Direction()
{
	if (GetRand(1) == 1)
	{
		jump_flg = true;
	}
}

//old_y�̎擾�֐�
float Enemy_06::Get_OldY()
{
	return old_y;
}

//y�̎擾�֐�
float Enemy_06::Get_Y()
{
	return y;
}