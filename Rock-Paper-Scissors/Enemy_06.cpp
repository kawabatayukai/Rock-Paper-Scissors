#include "Enemy_06.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include"SoundSystem.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_06::Enemy_06(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 5.0f;             //�f�t�H���g���x��5.0f
	dir = -1;                 //-1�Ȃ獶����  +1�Ȃ�E����
	hp = 100;                 //HP��100

	old_type = static_cast<Jan_Type>(2);  //�p�[�����ŏ�����

	//�摜�ǂݍ���
	images[0] = LoadGraph("images/stage06/��NINJA_�ʏ�.png");     //�O�[����
	images[1] = LoadGraph("images/stage06/��NINJA_�ʏ�.png");   //�`���L����
	images[2] = LoadGraph("images/stage06/��NINJA_�ʏ�.png");     //�p�[����

	images[3] = LoadGraph("images/stage06/��NINJA_��.png");     //�O�[����
	images[4] = LoadGraph("images/stage06/��NINJA_��.png");   //�`���L����
	images[5] = LoadGraph("images/stage06/��NINJA_��.png");     //�p�[����

	images[6] = LoadGraph("images/stage06/��NINJA_��3.png");     //�O�[����
	images[7] = LoadGraph("images/stage06/��NINJA_��3.png");   //�`���L����
	images[8] = LoadGraph("images/stage06/��NINJA_��3.png");     //�p�[����

	//���G�t�F�N�g�ǂݍ���
	LoadDivGraph("images/stage06/pipo-btleffect059.png", 10, 10, 1, 120, 120, smokeImage);

	////�W������SE�ǂݍ���
	//attackSE = LoadSoundMem("Sound/stage06/nc263537.wav");

	////�ړ�SE�ǂݍ���
	//dashSE = LoadSoundMem("Sound/stage06/���ʂő���.mp3");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_06::~Enemy_06()
{

}


//�X�V
void Enemy_06::Update()
{
	frame_count++;
	TeleportTime++;
	SpeedUpTime++;
	bef_x = x;
	bef_y = y;

	smoke();

	////SE�Đ�
	//if (y == bef_y && hp > 0)
	//{
	//	if (CheckSoundMem(dashSE) == FALSE)
	//	{
	//		PlaySoundMem(dashSE, DX_PLAYTYPE_BACK, TRUE);
	//	}
	//}
	//else
	//{
	//	StopSoundMem(dashSE);
	//}

	//����񌂍X�V�E����
	Update_Jangeki();

	//HP�\�����}�C�i�X�ɂȂ�Ȃ��悤�ɒ���
	if (hp <= 0)hp = 0;

	if (smokeFlg == false)
	{
		if (TeleportFlg == false)   //�u�Ԉړ��ڐG�t���O�̔���
		{
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
		}
		else if (TeleportFlg == true)
		{
			//����s��2   �v���C���[�̌�����Ɉړ����A�ڋ߂��Ă���
			if (attack_pattern > 0)  //�s�����[�v1�ȊO�̎�
			{
				Teleportation();
			}
			else  //��O����
			{
				TeleportFlg = false;
				TeleportInit = true;
				speed = 5.0f;
				smokeFlg = false;
			}
		}
		else  //��O����
		{
			TeleportFlg = false;
			TeleportInit = true;
			speed = 5.0f;
			smokeFlg = false;
		}

		//500�t���[�����Ƃɏu�Ԉړ��ڐG�t���O��true�ɂ���
		if (TeleportTime == 500 && TeleportFlg == false && (player_x - 250) > 50 && (player_x + 250) < 1230 && speed != 8.0f)
		{
			TeleportFlg = true;
			if (attack_pattern != 0 && hp <= 70)
			{
				smokeFlg = true;
			}
		}
		else if (TeleportTime > 500)
		{
			TeleportTime = 0;
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
}

//�`��
void Enemy_06::Draw() const
{
	if (smokeFlg == true)
	{
		//���A�j���[�V����
		DrawGraph((x - 63), (y - 70), smokeImage[smokeCnt], TRUE);
	}
	else
	{
		//�O�[�����̎��A�Ԃ��L�����摜��\��
		if (GetType() == static_cast<Jan_Type>(0))
		{
			if (y != bef_y && y != 101)
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[6], TRUE, dir == -1 ? 0 : 1);
			}
			else if (x != bef_x)
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[3], TRUE, dir == -1 ? 0 : 1);
			}
			else
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[0], TRUE, dir == -1 ? 0 : 1);
			}
		}

		//�`���L�����̎��A���F���L�����摜��\��
		if (GetType() == static_cast<Jan_Type>(1))
		{
			if (y != bef_y && y != 101)
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[7], TRUE, dir == -1 ? 0 : 1);
			}
			else if (x != bef_x)
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[4], TRUE, dir == -1 ? 0 : 1);
			}
			else
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[1], TRUE, dir == -1 ? 0 : 1);
			}
		}

		//�p�[�����̎��A���L�����摜��\��
		if (GetType() == static_cast<Jan_Type>(2))
		{
			if (y != bef_y && y != 101)
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[8], TRUE, dir == -1 ? 0 : 1);
			}
			else if (x != bef_x)
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[5], TRUE, dir == -1 ? 0 : 1);
			}
			else
			{
				//���S����`��
				DrawRotaGraphF(x, y, 4.2, 0, images[2], TRUE, dir == -1 ? 0 : 1);
			}
		}

		//�e�X�g
		if (hp > 0) DrawFormatString((int)(x - 50), (int)(y - 125), 0xffffff, "HP : %d", hp);
		else DrawString((int)(x - 50), (int)(y - 125), "death!", 0xffffff);

		if (speed == 8.0f)
		{
			DrawString((int)(x - 80), (int)(y - 75), "�X�s�[�h�A�b�v", GetColor(255, 0, 0));
		}
	}

	//����񌂕`��
	Draw_Jangeki();
}

//����񌂐����E�X�V
void Enemy_06::Update_Jangeki()
{
	//�W���������̃J�E���g
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		//�W�������̍X�V
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
	

	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //���a
		float speed = 3.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		if (smokeFlg == false)
		{
			//�s���p�^�[��1�̎��̒e(speed = 3.0f  frame_count % 80)
			if (attack_pattern == 0)
			{
				//�v���C���[�����Ɍ������Ĕ��˂����W�������̐���
				if (frame_count % 90 == 0) obj_jangeki[jan_count] =
					new Jangeki_Coming(x, y, radius, speed + 1.0f, type, player_x, player_y);
			}

			//�s���p�^�[��2�̎��̒e(speed = 3.0f  frame_count % 80)
			if (attack_pattern == 1)
			{
				//�v���C���[�����Ɍ������Ĕ��˂����W�������̐���
				if (frame_count % 75 == 0) obj_jangeki[jan_count] =
					new Jangeki_Coming(x, y, radius, speed + 1.5f, type, player_x, player_y);
			}

			//�s���p�^�[��3�̎��̒e(speed = 3.0f  frame_count % 80)
			if (attack_pattern == 2)
			{
				//�v���C���[�����Ɍ������Ĕ��˂����W�������̐���
				if (frame_count % 65 == 0) obj_jangeki[jan_count] =
					new Jangeki_Coming(x, y, radius, speed + 2.0f, type, player_x, player_y);
			}
		}
	}
}

//�s�����[�v1
void Enemy_06::AttackPattern_1()
{
	//4��W�����v����܂ł̊Ԉȉ��̏���(�W�����v)���J��Ԃ�
	if (jump_cnt < 2)         
	{
		if (GetRand(3) == 3)  //������jump_flg��true�ɂ���
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();
	}

	//���n���Ă��玟�̍s�����J�n
	if (jump_cnt == 2 && land_flg == true)
	{
		jump_cnt++;
	}

	//4��ȏ�W�����v�����ۂ̏���
	if (jump_cnt >= 3 && dir == -1)        //���������Ă��鎞�̏���
	{
		x -= speed;      //1�t���[���̊Ԃɍ��֐i�ދ���

		/********** ������W�ŃW�����v **********/

		if (x > 380 && x < 386)
		{
			jump_flg = true;
		}
		else if (x > 650 && x < 656)
		{
			jump_flg = true;
		}
		else if (x > 900 && x < 906)
		{
			jump_flg = true;
		}
		else if (x > 1140 && x < 1146)
		{
			jump_flg = true;
		}

		/****************************************/

		low_jump();     //��W�����v

		//�ڒn���Ă��邩�ǂ����ňړ����x����   �ڒn��(true)    : speed = 3.0f
		//                                       ��ڒn��(false) : speed = 7.0f
		if (land_flg == true)
		{
			speed = 3.0f;
		}
		else if(land_flg == false)
		{
			speed = 7.0f;
		}

		//�ڕW���W�ɓ����������̃`�F�b�N
		if (x < 115)
		{
			jump_cnt = 0;          //�W�����v�񐔂̃��Z�b�g
			dir = 1;               //�����Ă�������̔��]
			ChangeCnt++;           //�����ω��܂ł̃J�E���g
		}
	}
	else if (jump_cnt >= 3 && dir == 1)    //�E�������Ă��鎞�̏���
	{
		x += speed;      //1�t���[���̊ԂɉE�֐i�ދ���

		/********** ������W�ŃW�����v **********/

		if (x > 124 && x < 130)
		{
			jump_flg = true;
		}
		else if (x > 414 && x < 420)
		{
			jump_flg = true;
		}
		else if (x > 664 && x < 670)
		{
			jump_flg = true;
		}
		else if (x > 904 && x < 910)
		{
			jump_flg = true;
		}

		/****************************************/

		low_jump();     //��W�����v

		//�ڒn���Ă��邩�ǂ����ňړ����x����   �ڒn��(true)    : speed = 3.0f
		//                                       ��ڒn��(false) : speed = 7.0f
		if (land_flg == true)
		{
			speed = 3.0f;
		}
		else if (land_flg == false)
		{
			speed = 7.0f;
		}

		if (x > 1180)   //�ڕW���W�ɓ����������̃`�F�b�N
		{
			jump_cnt = 0;           //�W�����v�񐔂̃��Z�b�g
			dir = -1;               //�����Ă�������̔��]
			ChangeCnt++;            //�����ω��܂ł̃J�E���g
		}
	}

	//�G�̑����ω�����
	if (ChangeCnt > 4)
	{
		while (GetType() == old_type)
		{
			SetType(static_cast<Jan_Type>(GetRand(2)));
		}
		old_type = GetType();
		ChangeCnt = 0;
	}

	//HP��70�ȉ��ɂȂ�Ǝ��̍s�����[�v�Ɉڍs
	if (hp <= 70)
	{
		smokeFlg = true;
	}
}

//�s�����[�v2
void Enemy_06::AttackPattern_2()
{
	//�U���p�^�[��2��������
	if (attack2_Flg == true)
	{
		x = 1149;                  //�u�Ԉړ����x���W
		y = 480;                   //�u�Ԉړ����y���W
		speed = 5.0f;              //�X�s�[�h�̏�����
		floor = 5;                 //���݂̏��ʒu�̏�����(5)
		dir = -1;                  //�����̏�����(������)
		attack2_Flg = false;       //�����������t���O��false�ɂ���
		jump_cnt = 0;              //�W�����v�J�E���g�̏�����
		smokeFlg = true;
	}

	//�����Ƃ̏���
	switch (floor)
	{
	case 1:
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x >= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 141)
		{
			floor = 1;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 645)
		{
			floor = 3;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 1149)
		{
			floor = 5;
			dir = -1;
			jump_Direction();
		}

		break;

	case 5:
		if (dir == -1)
		{
			x -= speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;
	}



	//�G�̑����ω�����
	if (ChangeCnt > 6)
	{
		while (GetType() == old_type)
		{
			SetType(static_cast<Jan_Type>(GetRand(2)));
		}
		old_type = GetType();
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
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}
		
		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x >= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 2:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 141)
		{
			floor = 1;
			dir = 1;
			jump_Direction();
		}
		if (x >= 645)
		{
			floor = 3;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 3:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 393)
		{
			floor = 2;
			decision_Direction();
			jump_Direction();
		}
		if (x >= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;

	case 4:
		if (dir == -1)
		{
			x -= speed;
		}
		if (dir == 1)
		{
			x += speed;
		}

		if (y == 650)
		{
			jump_flg = true;
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
			x -= speed;
		}

		if (y == 100)
		{
			jump_flg = false;
		}

		if (y == 500)
		{
			jump_flg = true;
		}

		if (y == 650)
		{
			jump_flg = false;
		}

		//�W�����v����
		jump();

		//�w����W�ɓ���������switch�J��
		if (x <= 897)
		{
			floor = 4;
			decision_Direction();
			jump_Direction();
		}

		break;
	}

	if (speed == 8.0f)
	{
		//�G�̑����ω�����
		if (ChangeCnt > 0)
		{
			while (GetType() == old_type)
			{
				SetType(static_cast<Jan_Type>(GetRand(2)));
			}
			old_type = GetType();
			ChangeCnt = 0;
		}
	}
	else
	{
		//�G�̑����ω�����
		if (ChangeCnt > 4)
		{
			while (GetType() == old_type)
			{
				SetType(static_cast<Jan_Type>(GetRand(2)));
			}
			old_type = GetType();
			ChangeCnt = 0;
		}
	}

	//���b�o�߂Ō��̑��x & �U���p�^�[���֑J��
	if (SpeedUpTime % 600 == 0)
	{
		speed = 5.0f;
		if (hp > 70)
		{
			attack_pattern = 0;
			jump_cnt = 0;
			dir = 1;
			x = 1200;
			y = 360;
		}
		else if (hp > 40)
		{
			attack_pattern = 1;
		}
	}
}

//����s��1   speed = 8.0f
void Enemy_06::SpeedUp()
{
	attack_pattern = 2;
	speed = 8.0f;
	SpeedUpTime = 0;
	TeleportFlg = false;
	TeleportInit = true;
}

//����s��2   �v���C���[�̌�����Ɉړ����A�ڋ߂��Ă���
void Enemy_06::Teleportation()
{
	if (TeleportInit == true && smokeFlg == false)
	{
		if (player_dir == 0)
		{
			dir = -1;
			x = player_x + 250;
			y = 650.0f;
		}

		if (player_dir == 1)
		{
			dir = 1;
			x = player_x - 250;
			y = 650.0f;
		}

		speed = 1.5f;
		TeleportInit = false;
		smokeFlg = true;
	}
	
	speed += 0.2f;

	if (dir == -1)
	{
		x -= speed;
	}
	
	if (dir == 1)
	{
		x += speed;
	}

	if (x < 190 && dir == -1)
	{
		TeleportFlg = false;
		TeleportInit = true;
		TeleportTime = 0;
		speed = 5.0f;
		dir = 1;
		floor = 1;
	}

	if (x > 1080 && dir == 1)
	{
		TeleportFlg = false;
		TeleportInit = true;
		TeleportTime = 0;
		speed = 5.0f;
		dir = -1;
		floor = 5;
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
		SoundSystem::PlaySE(SE::PLAYER_JUMP);
		g_add = -19.9f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
		jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g

		if (attack_pattern == 0)
		{
			jump_cnt++;        //�W�����v�񐔂̃J�E���g
		}

		if (attack_pattern >= 1)
		{
			ChangeCnt++;       //�����ω��܂ł̃J�E���g
		}
	}
}

//�Ⴂ�W�����v
void Enemy_06::low_jump()
{
	//�W�����v����
	if (jump_flg == true && land_flg == true)
	{
		SoundSystem::PlaySE(SE::PLAYER_JUMP);
		g_add = -8.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
		jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
	}
}

//���G�t�F�N�g�֐�
void Enemy_06::smoke()
{
	if (smokeCnt < 10 && frame_count % 2 == 0 && smokeFlg == true)
	{
		if (smokeCnt == 0)
		{
			//BGM�Đ�
			SoundSystem::PlaySE(SE::ENEMY06_SMOKE);
		}
		smokeCnt++;
	}
	else if(smokeCnt > 9 && frame_count % 2 == 0 && smokeFlg == true)
	{
		smokeFlg = false;
		smokeCnt = 0;
		if (hp <= 70 && attack_pattern == 0)
		{
			attack_pattern = 1;    //�U���p�^�[����ύX
			attack2_Flg = true;    //�U���p�^�[��2���������t���O��true�ɂ���
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

//���G�t�F�N�g�̃t���O�̎擾
int Enemy_06::Get_smokeflg()
{
	return smokeFlg;
}