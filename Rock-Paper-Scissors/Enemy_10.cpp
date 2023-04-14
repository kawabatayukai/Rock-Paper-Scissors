#include "Enemy_10.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Coming.h"
#include"Jangeki_whole.h"
#include <math.h>
#include <corecrt_math_defines.h>
#include "KeyManager.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_10::Enemy_10(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	form = 1;

	Rimage = LoadGraph("images/stage09/Stage9_1.png");	//����ON
	Limage = LoadGraph("images/stage09/Stage9.png");		//����OFF

	//image = LoadGraph("images/tyokitest.png");
	if (LoadDivGraph("images/�X�e�[�W10�G�̉摜.png", 10, 5, 2, 100, 100, image) == -1);

	Init_Jangeki();       //����񌂂�p��

	/*���˒e*/
	reflection = new Jangeki_Reflection(x, y, w, h, Jan_Type::ROCK);
	reflection->Init_reflectionJangeki();

}

//�f�X�g���N�^
Enemy_10::~Enemy_10()
{

}

/*�G�̓���*/
void  Enemy_10::Move()
{
	static int switchMove = 0; //��Ɨp�ϐ�

	switch (form)
	{
		/***********
		* ���`��
		***********/
	case 1:
		if (hp > 0)
		{
			/*���E�̑���ɃW�����v�ړ��̏���*/
			switch (switchMove)
			{
			case 0:
				if (x > 120) //���ֈړ�
				{
					x--;
					dir = static_cast<int>(DIRECTION::LEFT);   //������ݒ�i���j

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
				enemyChange_Image = 2; //switch���̊��蓖�Ĕԍ�
				break;

			case 1:
				if (x < 1100) //�E�ֈړ�
				{
					x++;
					dir = static_cast<int>(DIRECTION::RIGHT);  //������ݒ�i�E�j

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
				enemyChange_Image = 1; //switch���̊��蓖�Ĕԍ�
				break;
			}
		}
		else
		{
			Interval();
		}
		break;

		/***********
		* ���`��
		***********/
	case 2:
		if (hp > 0)
		{

		}
		break;

	default:
		break;
	}

	//�摜�̑I��ύX
	EnemySwitch();

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

void Enemy_10::Interval()
{
	//�_��
	static int counter;

	if (KeyManager::OnPadClicked(PAD_INPUT_A) == false)
	{
		if (counter++ < 30)
		{
			DrawString(550, 350, "-- Press  A  Button --", 0xffffffff);
		}
		else if (counter > 60)  counter = 0;
	}
	else
	{
		hp = 100;
		x = 1100;
		dir == static_cast<int>(DIRECTION::LEFT);
		form = 2;
	}
}

//�X�V
void Enemy_10::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

	//����񌂍X�V�E����(���˒e)
	reflection->Update_reflection();

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
	DrawRotaGraphF(x, y, 1, 0, image[enemy_Image], TRUE);
	//DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();
	reflection->Draw_reflectionJangeki(); //���˒e�`��

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);
	DrawFormatString(500, 200, 0xffffffff, "%f", x);

}

/*�摜�̕ύX�擾*/
void  Enemy_10::EnemySwitch()
{
	/*�v���C���[�̉摜�ύX*/
	switch (enemyChange_Image)
	{
		/*���E�ړ�*/
	case 1: //�E�ړ�
	   /*     �E����            �ڒn   */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true)
		{
			enemyGetMove = 1;      //�摜���擾
			enemyCount++;          //�t���[���J�E���g�𑝂₷
			EnemyChangeMoveimg();  //�摜�ύX��

			//pCount = 0;             //�����ĂȂ��Ƃ��p
			//enemyChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}       /*  �E����         ��ڒn     */
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false)
		{
			enemy_Image = 4;     //�摜���擾
			break;
		}

	case 2: //���ړ��̎�
	   /*     ������            �ڒn  */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
		{
			enemyGetMove = 6;      //�摜���擾
			enemyCount++;          //�t���[���J�E���g�𑝂₷
			EnemyChangeMoveimg();  //�摜�ύX��

			//pCount = 5;             //�����ĂȂ��Ƃ��p
			//enemyChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}       /*  ������         ��ڒn     */
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false)
		{
			enemy_Image = 9;     //�摜���擾
			break;
		}

		//case 0: //�~�܂��Ă���

		//   /*     ������            �ڒn                                           ������ĂȂ�   */
		//	if (dir == 0 && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) == FALSE)
		//	{
		//		pCount = 0;  //�����ĂȂ��Ƃ��p
		//	}
		//	/*     �E����            �ڒn                                           ������ĂȂ�  */
		//	if (dir == 1 && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) == FALSE)
		//	{
		//		pCount = 5;  //�����ĂȂ��Ƃ��p
		//	}
		//	enemyGetMove = pCount; //�Ō�ɓ��������̉摜
		//	enemyCount++;          //�t���[���̃J�E���g
		//	EnemyChangeMoveimg();  //�摜�ύX��
		//	break;

	default:
		break;
	}
}

/*�摜�̓���ύX*/
void  Enemy_10::EnemyChangeMoveimg()
{
	static int std = 0; //�摜�̊

	/*�摜�̕ێ�*/
	switch (enemyGetMove)
	{
		/*�E�ړ�*/
	case 1: //1�̉摜
		if (enemy_Image != 2 && enemy_Image != 3)
		{
			enemy_Image = 1;
			std = 1; //�Z�b�g����
		}
		break;
	case 2: //2�̉摜
		if (enemy_Image != 1 && enemy_Image != 3)
		{
			enemy_Image = 2;
			std = 2; //�Z�b�g����
		}
		break;
	case 3: //3�̉摜
		if (enemy_Image != 1 && enemy_Image != 2)
		{
			enemy_Image = 3;
			std = 3; //�Z�b�g����
		}
		break;

		/*���ړ�*/
	case 6: //6�̉摜
		if (enemy_Image != 7 && enemy_Image != 8)
		{
			enemy_Image = 6;
			std = 6; //�Z�b�g����
		}
		break;
	case 7: //7�̉摜
		if (enemy_Image != 6 && enemy_Image != 8)
		{
			enemy_Image = 7;
			std = 7; //�Z�b�g����
		}
		break;
	case 8: //8�̉摜
		if (enemy_Image != 6 && enemy_Image != 7)
		{
			enemy_Image = 8;
			std = 8; //�Z�b�g����
		}
		break;

		/*�W�����v*/
	case 4: //4�̉摜
		enemy_Image = 4;
		std = 0; //�Z�b�g����
		break;
	case 9: //9�̉摜
		enemy_Image = 9;
		std = 0; //�Z�b�g����
		break;

		/*�~�܂��Ă���*/
	//case 0: //0�̉摜
	//	enemy_Image = 0;
	//	std = 0; //�Z�b�g����
	//	break;
	//case 5: //5�̉摜
	//	enemy_Image = 5;
	//	std = 0; //�Z�b�g����
	//	break;
	default:
		break;
	}

	/*�����Ă���悤�ɉ摜�ύX*/
	if (enemyCount % 10 == 0) //5�t���[�����̏���
	{
		/*�E�ړ�*/
		if (dir == static_cast<int>(DIRECTION::RIGHT)) {
			if (std == 1 && 2 > enemy_Image) // �摜 1
			{
				enemy_Image = 2;
				std = 2;
			}
			else if (std == 2 && 3 > enemy_Image) // �摜 2
			{
				enemy_Image = 3;
				std = 3;
			}
			else if (std == 3 && 2 < enemy_Image) //�摜 3
			{
				enemy_Image = 2;
				std = 4;
			}
			else if (std == 4 && 1 < enemy_Image) // �摜 2
			{
				enemy_Image = 1;
				std = 1;
			}
			enemyCount = 0;
		}
		/*���ړ�*/
		if (dir == static_cast<int>(DIRECTION::LEFT)) {
			if (std == 6 && 7 > enemy_Image) // �摜 6
			{
				enemy_Image = 7;
				std = 7;
			}
			else if (std == 7 && 8 > enemy_Image) // �摜 7
			{
				enemy_Image = 8;
				std = 8;
			}
			else if (std == 8 && 7 < enemy_Image) // �摜 8
			{
				enemy_Image = 7;
				std = 9;
			}
			else if (std == 9 && 6 < enemy_Image) // �摜 7
			{
				enemy_Image = 6;
				std = 6;
			}
			enemyCount = 0;
		}
	}
	//enemy_Image = enemy_Image + dir * 4;
	//
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

		if (hp > 0) //HP�����鎞
			switch (form)
			{
				/***********
				* ���`��
				***********/
			case 1:
				/*********************** ���� ����( �ʏ�e ) ���� ***********************/

				//            �������x
				//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type); //�^���e

				/************************************************************************/

				/*********************** ���� ����( �ǐՒe ) ���� ***********************/

				//            �������x
				//if (frame_count % 50 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type); //�ǐՒe 

				/************************************************************************/

				/*********************** ���� ����( �v���C���[�����ʏ�e ) ���� ***********************/

				//            �������x
				if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

				/************************************************************************/

				/*********************** ���� ����( ���S�~�^�g�U�e ) ���� ***********************/

				/*if (frame_count % 120 == 0)
				{
					Jan_360degrees(jan_count, radius, speed, type); //360�x����
				}*/
				//            �������x
				//if (frame_count % 10 == 0) obj_jangeki[jan_count] = new Jangeki_whole(x, y, radius, speed, type);

				/************************************************************************/

				/*********************** ���� ����( ���˒e ) ���� ***********************/

				//���˂���񌂐���
				//if (reflection->GetFlg() == true)reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed, type, true);
				//reflection->falseFlg();

				/************************************************************************/
				break;

				/***********
				* ���`��
				***********/
			case 2:
				/*********************** ���� ����( �ʏ�e ) ���� ***********************/

			//            �������x
			//if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type); //�^���e

			/************************************************************************/

			/*********************** ���� ����( �ǐՒe ) ���� ***********************/

			//            �������x
			//if (frame_count % 150 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type); //�ǐՒe 

			/************************************************************************/

			/*********************** ���� ����( �v���C���[�����ʏ�e ) ���� ***********************/

			//            �������x
			//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

			/************************************************************************/

			/*********************** ���� ����( ���S�~�^�g�U�e ) ���� ***********************/

				if (frame_count % 200 == 0)
				{
					Jan_360degrees(jan_count, radius, speed, type); //360�x����
				}
				//            �������x
				//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_whole(x, y, radius, speed, type);

				/************************************************************************/
				break;

				/*********************** ���� ����( ���˒e ) ���� ***********************/

				//���˂���񌂐���
					//if (reflection->GetFlg() == true)reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed, type, true);
					//reflection->falseFlg();

				/************************************************************************/
				break;

			default:
				break;
			}


	}
}

int Enemy_10::Get_Enemy10Form()
{
	return form;
}

//360�x����
void Enemy_10::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	//45�x����8����
	//if (hp <= 50)
	//{
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
	}

	//}
}

bool Enemy_10::Getflg()
{
	return rflg;
}
void Enemy_10::Tflg()
{
	rflg = true;
}
void Enemy_10::Fflg()
{
	rflg = false;
}
void Enemy_10::HP()
{
	if (hp <= 0)
	{
		hp = 1;
	}
}