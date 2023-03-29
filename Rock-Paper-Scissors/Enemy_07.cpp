#include "Enemy_07.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Vertical.h"
#include<typeinfo>

#define _USE_MATH_DEFINES
#include<math.h>

//�萔�@
namespace _CONSTANTS_07
{
	const float RING_LEFT  = 250.0f;    //�����O���[
	const float RING_RIGHT = 1030.0f;   //�����O�E�[
	const float RING_HEIGHT = 590.0f;   //�����O�̍���

	const float RING_CENTER = 640.0f;   //�����O�̒��S

	const float CORNER_LEFT  = 235.0f;  //���R�[�i�[�g�b�v (���S�����W)
	const float CORNER_RIGHT = 1045.0f; //�E�R�[�i�[�g�b�v (���S�����W)
	const float CORNER_Y = 440.0f;      //�R�[�i�[�̍����i���ʁj

	// "����"�͉�ʍ����珇�� 1,2,3,....�Ɣԍ�������
	const float FLOOR_NO_01 = 95.0f;    //����P (���S�����W)
	const float FLOOR_NO_02 = 490.0f;   //����Q (���S�����W)
	const float FLOOR_NO_03 = 790.0f;   //����R (���S�����W)
	const float FLOOR_NO_04 = 1185.0f;  //����S (���S�����W)

	const float FLOOR_NO_01_04_Y = 230.0f;  // ����P�C�S�̂����W
	const float FLOOR_NO_02_03_Y = 110.0f;  // ����Q�C�R�̂����W

	const float OUT_RING_LEFT = 120.0f;     //��O��
	const float OUT_RING_RIGHT = 1160.0f;   //��O�E

	//�e�X�g�\���p
	char state_str [][20] = { "ON_RING","ON_FLOOR","ON_FLOOR_LURK","OUT_RING","DO_NOT" };   
	char action_str[][20] = { "NO_ACT","LEFT_TO_RIGHT","RIGHT_TO_LEFT"
		                     ,"CLIMB_CORNER_LEFT", "CLIMB_CORNER_RIGHT"
		                     ,"CROSS_FLOOR_LEFT","CROSS_FLOOR_RIGHT"
	                         ,"DIVE_OUT_LEFT","DIVE_OUT_RIGHT"};
}

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_07::Enemy_07(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type), init_speed(4.0f), jan_count(0), draw_angle(0.0)
, Player_State(PLAYER_STATE::DO_NOT), Now_Action(ACT_TYPE::NO_ACT), Pre_Action(ACT_TYPE::NO_ACT)
{
	speed = 4.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_07::~Enemy_07()
{
	
}


//�X�V
void Enemy_07::Update()
{
	//Move_Pattern();
	Move_Controller();

	//����񌂍X�V�E����
	Update_Jangeki();


	/********************   �W�����v�֌W   ********************/

	//if (land_flg == true)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	//{
	//	g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;             //�d�͉����x������������

	/**********************************************************/
}

//�`��
void Enemy_07::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, draw_angle, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	//if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	//else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

	LPCTSTR string = _CONSTANTS_07::state_str[static_cast<int>(Player_State)];
	LPCTSTR string_act = _CONSTANTS_07::action_str[static_cast<int>(Now_Action)];
	LPCTSTR string_pre = _CONSTANTS_07::action_str[static_cast<int>(Pre_Action)];

	DrawString(23, 580, string, 0x00ff00);
	DrawString(23, 610, string_act, 0x00ff00);
	DrawString(23, 640, string_pre, 0x00ff00);
}

//����񌂐����E�X�V
void Enemy_07::Update_Jangeki()
{
	//int jan_count;

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
	//�z��̋�v�f                                                     �@����񌂔��� ON
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 25.5f;   //���a
		float speed = 6.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		////����
		//if (0)
		//{
		//	switch (GetRand(2))
		//	{
		//	case 0:
		//		Jan_360degrees(jan_count, radius, speed, type);
		//		break;

		//	case 1:
		//		obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
		//		break;

		//	case 2:
		//		Jan_Vertical(jan_count, radius, speed, type);
		//		break;

		//	default:
		//		break;

		//	obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
		//	}

		//}

	}

}

//�W�����v�i�W�����v�́j
void Enemy_07::Jump_Enemy(float g_add)
{
	//�}�C�i�X�l�łȂ���Ώ������Ȃ�
	if (g_add > 0) return;

	//�ڒn���Ă����
	if (land_flg == true)
	{
		this->g_add = g_add;    //�d�͉����x���}�C�i�X�l�Ɂ@
		land_flg = false;       //�n�ʂɂ��Ă��Ȃ�
	}
}

//�����_���ɑ����ω�
void Enemy_07::Change_JanType()
{
	//���݂̑����ƈقȂ�2�����̂��������_��
	switch (this -> e_type)
	{
	case Jan_Type::ROCK:

		e_type = GetRand(1) == 1 ? Jan_Type::PAPER : Jan_Type::SCISSORS;
		break;

	case Jan_Type::SCISSORS:

		e_type = GetRand(1) == 1 ? Jan_Type::PAPER : Jan_Type::ROCK;
		break;

	case Jan_Type::PAPER:

		e_type = GetRand(1) == 1 ? Jan_Type::ROCK : Jan_Type::SCISSORS;
		break;

	default:
		break;
	}

	return;
}

/*--------------------------------------------------------------------------------------*/

//�s������
void Enemy_07::Move_Controller()
{
	//�ڕW���W
	float target_x = 0;
	float target_y = 0;

	//�ړ���
	float move_x = x;
	float move_y = y;

	//�v���C���[�̏�Ԃɂ���čs�������߂�
	switch (Player_State)
	{
	case PLAYER_STATE::ON_RING:       //�����O��

		Move_ON_RING(target_x, target_y);
		break;

	case PLAYER_STATE::ON_FLOOR:      //�����

		Move_ON_FLOOR(target_x, target_y);
		break;

	case PLAYER_STATE::ON_FLOOR_LURK: //������3�b�ȏ�

		Move_ON_FLOOR_LURK(target_x, target_y);
		break;

	case PLAYER_STATE::OUT_RING:      //��O

		Move_OUT_RING(target_x, target_y);
		break;

	default:

		target_x = 1280 / 2;
		break;
	}

	//x���W���ڕW�ƕs��v
	if (x != target_x)
	{
		//�ڕW�̕����傫���i�ڕW�͉E�����j
		if (x < target_x)
		{
			move_x += speed;      //�E�ړ��i���̒l�j

			//�ڕW�𒴂����ꍇ
			if (x <= target_x && target_x <= move_x)
			{
				move_x = target_x;     //�ڕW���W�ŌŒ�
			}
		}
		else
		{
			move_x -= speed; //���ړ��i���̒l�j

			//�ڕW�𒴂����ꍇ
			if (move_x <= target_x && target_x <= x)
			{
				move_x = target_x;     //�ڕW���W�ŌŒ�
			}
		}
	}

	//�ړ��𔽉f
	x = move_x;
	y = move_y;
}

//�v���C���[�������O�� 
void Enemy_07::Move_ON_RING(float& target_x, float& target_y)
{
	//�E�i���j����@���i�E�j�@�ƖڕW���W���؂�ւ��

	//�ڕW���W(1�Ԗ�)�ƈ�v���Ă��邩
	static bool match = false;

	//�������邶��񌂂̔��a
	float radius = 25.5f;

	//�����_���ȑ����𐶐�
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	//�s�����łȂ�
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//�v���C���[��������荶��
		if (player_x < (1280 / 2))
		{
			Now_Action = ACT_TYPE::RIGHT_TO_LEFT;  //�E����
		}
		else
		{
			Now_Action = ACT_TYPE::LEFT_TO_RIGHT;  //�����E
		}

		match = false;
	}

	//�E����
	if (Now_Action == ACT_TYPE::RIGHT_TO_LEFT)
	{
		/*******************************�@�P  **++***************************/
		{
			//�����O�E��ڎw��
			if (match == false) target_x = _CONSTANTS_07::RING_RIGHT - (w / 2);

			//�����O�E�ɓ��B
			if (x == _CONSTANTS_07::RING_RIGHT - (w / 2))
			{
				match = true;  //1�ԖڏI��
				speed = 9.0f;  //�X�s�[�h�A�b�v

				//����񌂂𐶐�����i�z��̋�v�f�ł��邱�Ƃ��m���Ɂj                                       
				if ( jan_count + 2 < JANGEKI_MAX && obj_jangeki[jan_count + 2] == nullptr )
				{
					//�X�s�[�h�����g�Ɠ��� ���� �}�C�i�X�����ɔ�Ԃ����
					obj_jangeki[jan_count] = new Jangeki_Base(x, y - 40, radius, -speed, type);
					obj_jangeki[jan_count + 1] = new Jangeki_Base(x - 40, y + 30, radius, -speed, type);
					obj_jangeki[jan_count + 2] = new Jangeki_Base(x + 40, y + 30, radius, -speed, type);
				}
			}
		}
		/*******************************************************************/


		//�����O�E�ɓ��B�����̂��A�����O����ڎw��

		/*******************************�@�Q  **++***************************/
		{
			//�����O����ڎw��
			//if (match == true) target_x = _CONSTANTS_07::RING_LEFT + 200;
			if (match == true) target_x = _CONSTANTS_07::RING_CENTER - 100;

			//�����O���ɓ��B                             
			//if (x == _CONSTANTS_07::RING_LEFT + 200)
			if (x == _CONSTANTS_07::RING_CENTER - 100)
			{
				Pre_Action = Now_Action;        //�����Action��ۑ�

				Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
				speed = init_speed;             //�X�s�[�h��߂�
			}
		}
		/*******************************************************************/
	}

	//�����E
	if (Now_Action == ACT_TYPE::LEFT_TO_RIGHT)
	{
		/*******************************�@�P  **++***************************/
		{
			//�����O����ڎw��
			if (match == false) target_x = _CONSTANTS_07::RING_LEFT + (w / 2);

			//�����O���ɓ��B
			if (x == _CONSTANTS_07::RING_LEFT + (w / 2))
			{
				match = true;  //1�ԖڏI��
				speed = 9.0f;  //�X�s�[�h�A�b�v

				//����񌂂𐶐�����i�z��̋�v�f�ł��邱�Ƃ��m���Ɂj                                       
				if (jan_count + 2 < JANGEKI_MAX && obj_jangeki[jan_count + 2] == nullptr)
				{
					//�X�s�[�h�����g�Ɠ��� ���� �v���X�����ɔ�Ԃ����
					obj_jangeki[jan_count] = new Jangeki_Base(x, y - 40, radius, speed, type);
					obj_jangeki[jan_count + 1] = new Jangeki_Base(x - 40, y + 30, radius, speed, type);
					obj_jangeki[jan_count + 2] = new Jangeki_Base(x + 40, y + 30, radius, speed, type);
				}
			}
		}
		/*******************************************************************/


		//�����O���ɓ��B�����̂��A�����O�E��ڎw��

		/*******************************�@�Q  **++***************************/
		{
			//�����O�E��ڎw��
			//if (match == true) target_x = _CONSTANTS_07::RING_RIGHT - 200;
			if (match == true) target_x = _CONSTANTS_07::RING_CENTER + 100;

			//�����O�E�ɓ��B                            
			//if (x == _CONSTANTS_07::RING_RIGHT - 200)
			if (x == _CONSTANTS_07::RING_CENTER + 100)
			{
				Pre_Action = Now_Action;        //�����Action��ۑ�

				Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
				speed = init_speed;             //�X�s�[�h��߂�
			}
		}
		/*******************************************************************/
	}
}

//�v���C���[������i�󒆁j��
void Enemy_07::Move_ON_FLOOR(float& target_x, float& target_y)
{
	//�v���C���[�������ɂ��鎞�Ԃ��J�E���g
	static unsigned int time_count;

	//�������邶��񌂂̔��a
	float radius = 25.5f;

	//�����_���ȑ����𐶐�
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	//�s�����łȂ�
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		// ���E�����_��
		if (GetRand(1) == 0)
		{
			Now_Action = ACT_TYPE::CLIMB_CORNER_LEFT;    //�R�[�i�[�ɏ��i���j
		}
		else
		{
			Now_Action = ACT_TYPE::CLIMB_CORNER_RIGHT;   //�R�[�i�[�ɏ��i�E�j
		}

		//�J�E���^�[�����Z�b�g
		time_count = 0;
	}


	//�R�[�i�[�ɏ��i���j
	if (Now_Action == ACT_TYPE::CLIMB_CORNER_LEFT)
	{
		//(�P) �W�����v�n�_�ɓ��B�E�W�����v    (�Q) �R�[�i�[���ڎw��

		/*******************************�@�P  **++***************************/
		{
			//�i���j�W�����v�n�_��ڎw��
			if (time_count == 0) target_x = _CONSTANTS_07::RING_LEFT + 100;

			//�W�����v�n�_�ɓ��B
			if (x == _CONSTANTS_07::RING_LEFT + 100 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
			{
				time_count = 1;

				//�W�����v
				Jump_Enemy();
			}
		}
		/*******************************************************************/

		/*******************************�@�Q  **++***************************/
		{
			// �W�����v������
			if ( time_count > 0 )
			{
				//�R�[�i�[���ڎw��         ��
				target_x = _CONSTANTS_07::CORNER_LEFT;

				//�P�b�����ɂ���񌂐���
				if (time_count % 100 == 0)
				{
					obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, 3.0f, type);
				}

				//�R�b��
				if (time_count++ > 180)
				{
					Pre_Action = Now_Action;        //�����Action��ۑ�

					Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
				}
			}
		}
		/*******************************************************************/
	}

	//�R�[�i�[�ɏ��i�E�j
	if (Now_Action == ACT_TYPE::CLIMB_CORNER_RIGHT)
	{
		//(�P) �W�����v�n�_�ɓ��B�E�W�����v    (�Q) �R�[�i�[���ڎw��

		/*******************************�@�P  **++***************************/
		{
			//�i�E�j�W�����v�n�_��ڎw��
			if (time_count == 0) target_x = _CONSTANTS_07::RING_RIGHT - 100;

			//�W�����v�n�_�ɓ��B
			if (x == _CONSTANTS_07::RING_RIGHT - 100 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
			{
				time_count = 1;

				//�W�����v
				Jump_Enemy();
			}
		}
		/*******************************************************************/

		/*******************************�@�Q  **++***************************/
		{
			// �W�����v������
			if (time_count > 0)
			{
				//�R�[�i�[���ڎw��         �E
				target_x = _CONSTANTS_07::CORNER_RIGHT;

				//�P�b�����ɂ���񌂐���
				if (time_count % 100 == 0)
				{
					obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, 3.0f, type);
				}

				//�R�b��
				if (time_count++ > 180)
				{
					Pre_Action = Now_Action;        //�����Action��ۑ�

					Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
				}
			}
		}
		/*******************************************************************/
	}
}

//�v���C���[�������3�b�ȏ�
void Enemy_07::Move_ON_FLOOR_LURK(float& target_x, float& target_y)
{
	// ���B������
	static unsigned short count_ari;

	//�W�����v�́i�e�X�g�j
	float jump_add = -21.5f;

	//(���ɃR�[�i�[�ɏ���Ă���O��)

	//�s�����łȂ�
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		// �O���Action�����R�[�i�[��
		if (Pre_Action == ACT_TYPE::CLIMB_CORNER_LEFT)   Now_Action = ACT_TYPE::CROSS_FLOOR_LEFT;

		// �O���Action���E�R�[�i�[�� 
		if (Pre_Action == ACT_TYPE::CLIMB_CORNER_RIGHT)  Now_Action = ACT_TYPE::CROSS_FLOOR_RIGHT;

		//�J�E���g�̏�����
		count_ari = 0;

		//�W�����v
		Jump_Enemy(jump_add);
	}

	
	//�������邶��񌂂̔��a
	float radius = 25.5f;
	//�����_���ȑ����𐶐�
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));


	// �����n��i������E�j
	if (Now_Action == ACT_TYPE::CROSS_FLOOR_LEFT)
	{
        /*******************************�@�P  **++***************************/
		if (count_ari == 0)
		{
			// ���� 1 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_01;

			// ���� 1 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_01)
			{
				count_ari = 1;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);

				speed = 7.5f;
				Jump_Enemy(jump_add);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�Q  **++***************************/
		if (count_ari == 1)
		{
			// ���� 2 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_02;

			// ���� 2 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_02)
			{
				count_ari = 2;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
				Jump_Enemy(-18.f);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�R  **++***************************/
		if (count_ari == 2)
		{
			// ���� 3 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_03;

			// ���� 3 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_03)
			{
				count_ari = 3;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
				Jump_Enemy(jump_add);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�S  **++***************************/
		if (count_ari == 3)
		{
			// ���� 4 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_04;

			// ���� 4 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_04 && y == (_CONSTANTS_07::FLOOR_NO_01_04_Y - (h / 2)))
			{
				count_ari = 4;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, this->speed, type);
				Jump_Enemy(jump_add);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�T  **++***************************/
		if (count_ari == 4)
		{
			// �E�R�[�i�[�� ��ڎw��
			target_x = _CONSTANTS_07::CORNER_RIGHT;

			// �E�R�[�i�[�� �ɓ��B
			if (x == _CONSTANTS_07::CORNER_RIGHT && y == (_CONSTANTS_07::CORNER_Y - (h / 2)))
			{
				Pre_Action = Now_Action;        //�����Action��ۑ�
				Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���

				speed = init_speed;             //�X�s�[�h�������ɖ߂�
			}
		}

		/*******************************************************************/
	}


	// �����n��i�E���獶�j
	if (Now_Action == ACT_TYPE::CROSS_FLOOR_RIGHT)
	{
		/*******************************�@�P  **++***************************/
		if (count_ari == 0)
		{
			// ���� 4 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_04;

			// ���� 4 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_04)
			{
				count_ari = 1;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);

				speed = 7.5f;
				Jump_Enemy(jump_add);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�Q  **++***************************/
		if (count_ari == 1)
		{
			// ���� 3 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_03;

			// ���� 3 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_03)
			{
				count_ari = 2;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);
				Jump_Enemy(-18.f);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�R  **++***************************/
		if (count_ari == 2)
		{
			// ���� 2 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_02;

			// ���� 2 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_02)
			{
				count_ari = 3;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);
				Jump_Enemy(jump_add);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�S  **++***************************/
		if (count_ari == 3)
		{
			// ���� 1 ��ڎw��
			target_x = _CONSTANTS_07::FLOOR_NO_01;

			// ���� 1 �ɓ��B
			if (x == _CONSTANTS_07::FLOOR_NO_01 && y == (_CONSTANTS_07::FLOOR_NO_01_04_Y - (h / 2)))
			{
				count_ari = 4;

				//����񌂂𔭎˂���
				obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, -(this->speed), type);
				Jump_Enemy(jump_add);   //�W�����v
			}
		}

		/*******************************************************************/

		/*******************************�@�T  **++***************************/
		if (count_ari == 4)
		{
			// ���R�[�i�[�� ��ڎw��
			target_x = _CONSTANTS_07::CORNER_LEFT;

			// ���R�[�i�[�� �ɓ��B
			if (x == _CONSTANTS_07::CORNER_LEFT && y == (_CONSTANTS_07::CORNER_Y - (h / 2)))
			{
				Pre_Action = Now_Action;        //�����Action��ۑ�
				Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���

				speed = init_speed;
			}
		}

		/*******************************************************************/
	}
}

//�v���C���[����O
void Enemy_07::Move_OUT_RING(float& target_x, float& target_y)
{
	//��O�փ_�C�u�i�g�y�E�R���q�[���I�ȁj

	// ���B������
	static unsigned short count_ari;

	//�s�����łȂ�
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//�v���C���[��������荶��
		if (player_x < _CONSTANTS_07::RING_CENTER)
		{
			Now_Action = ACT_TYPE::DIVE_OUT_LEFT;   //�����O��
		}
		else
		{
			Now_Action = ACT_TYPE::DIVE_OUT_RIGHT;  //�����O�E
		}

		count_ari = 0;  //�J�E���^�[�����Z�b�g
		speed = 11.0f;  //�X�s�[�h�A�b�v
	}

	//�����O���փ_�C�u
	if (Now_Action == ACT_TYPE::DIVE_OUT_LEFT)
	{
		// �i1�j����      (2) �W�����v�n�_�ɓ��B�E�W�����v   
		//  (3)�_�C�u     (4) �����O���ɖ߂�

        /*******************************�@�P  **++***************************/
		{
			//�����O�E��ڎw��
			if (count_ari == 0) target_x = _CONSTANTS_07::RING_RIGHT - (w / 2);

			//�����O�E�ɓ��B
			if (x == _CONSTANTS_07::RING_RIGHT - (w / 2))
			{
				count_ari = 1;   // 2 ��
				speed = 11.0f;   //�X�s�[�h�A�b�v
			}
		}
		/*******************************************************************/

		/*******************************�@�Q  **++***************************/
		{
			if (count_ari == 1)
			{
				//�i���j�W�����v�n�_��ڎw��
				target_x = _CONSTANTS_07::RING_LEFT + 400;

				//�W�����v�n�_�ɓ���
				if (x == _CONSTANTS_07::RING_LEFT + 400 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
				{
					count_ari = 2;       // 3 ��
					Jump_Enemy(-23.0f);  //�W�����v

					Jan_360degrees();    //����񌂔���
				}
			}
		}
		/*******************************************************************/

		/*******************************�@�R  **++***************************/
		{
			if (count_ari == 2)
			{
				//�W�����v��

				//�����O�O��ڎw��         ��
				target_x = _CONSTANTS_07::OUT_RING_LEFT - 35;
				
				//�摜����]������
				draw_angle -= 0.1;

				//���n
				if (x == _CONSTANTS_07::OUT_RING_LEFT - 35 && land_flg == true)
				{
					count_ari = 3;       // 4 ��
					speed = init_speed;  //�X�s�[�h�������ɖ߂�
					draw_angle = 0.0;    //�����̊p�x�ɖ߂�
				}
			}
		}
		/*******************************************************************/

		/*******************************�@�S  **++***************************/
		{
			//20�t���[���ҋ@    count_ari�Ńt���[�����v������
			if (count_ari >= 3 && count_ari < 23)
			{
				count_ari++;

				//20�t���[���o�ߌ�
				if (count_ari == 23)
				{
					Jump_Enemy(-18.0f);
					count_ari = 99;
				}
			}

			if (count_ari == 99)
			{
				//�����O����ڎw��         
				target_x = _CONSTANTS_07::RING_LEFT + (w / 2);

				//�����O���ɓ��B
				if (x == _CONSTANTS_07::RING_LEFT + (w / 2))
				{
					Pre_Action = Now_Action;        //�����Action��ۑ�
					Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
					speed = init_speed;             //�X�s�[�h�������ɖ߂�
				}
			}
		}
		/*******************************************************************/
	}


	//�����O�E�փ_�C�u
	if (Now_Action == ACT_TYPE::DIVE_OUT_RIGHT)
	{
		// �i1�j����      (2) �W�����v�n�_�ɓ��B�E�W�����v   
		//  (3)�_�C�u     (4) �����O���ɖ߂�

		/*******************************�@�P  **++***************************/
		{
			//�����O����ڎw��
			if (count_ari == 0) target_x = _CONSTANTS_07::RING_LEFT + (w / 2);

			//�����O���ɓ��B
			if (x == _CONSTANTS_07::RING_LEFT + (w / 2))
			{
				count_ari = 1;   // 2 ��
				speed = 11.0f;   //�X�s�[�h�A�b�v
			}
		}
		/*******************************************************************/

		/*******************************�@�Q  **++***************************/
		{
			if (count_ari == 1)
			{
				//�i�E�j�W�����v�n�_��ڎw��
				target_x = _CONSTANTS_07::RING_RIGHT - 400;

				//�W�����v�n�_�ɓ���
				if (x == _CONSTANTS_07::RING_RIGHT - 400 && y == (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
				{
					count_ari = 2;       // 3 ��
					Jump_Enemy(-23.0f);  //�W�����v

					Jan_360degrees();    //����񌂔���
				}
			}
		}
		/*******************************************************************/

		/*******************************�@�R  **++***************************/
		{
			if (count_ari == 2)
			{
				//�W�����v��

				//�����O�O��ڎw��         �E
				target_x = _CONSTANTS_07::OUT_RING_RIGHT + 35;

				//�摜����]������
				draw_angle += 0.1;

				//���n
				if (x == _CONSTANTS_07::OUT_RING_RIGHT + 35 && land_flg == true)
				{
					count_ari = 3;       // 4 ��
					speed = init_speed;  //�X�s�[�h�������ɖ߂�
					draw_angle = 0.0;    //�����̊p�x�ɖ߂�
				}
			}
		}
		/*******************************************************************/

		/*******************************�@�S  **++***************************/
		{
			//20�t���[���ҋ@    count_ari�Ńt���[�����v������
			if (count_ari >= 3 && count_ari < 23)
			{
				count_ari++;

				//20�t���[���o�ߌ�
				if (count_ari == 23)
				{
					Jump_Enemy(-18.0f);
					count_ari = 99;
				}
			}

			if (count_ari == 99)
			{
				//�����O����ڎw��         
				target_x = _CONSTANTS_07::RING_RIGHT - (w / 2);

				//�����O���ɓ��B
				if (x == _CONSTANTS_07::RING_RIGHT - (w / 2))
				{
					Pre_Action = Now_Action;        //�����Action��ۑ�
					Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
					speed = init_speed;             //�X�s�[�h�������ɖ߂�
				}
			}
		}
		/*******************************************************************/
	}
}

//�v���C���[�̏󋵂��擾
void Enemy_07::CheckPlayerState(const Player* player)
{
	//���s����Action�i�s���j���I���Ă���ύX����
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//�����蔻������p          
		if (player->CheckHitBox_Box(220, 260, 840, 330) == true)        //�����O��͈̔�
		{
			Player_State = PLAYER_STATE::ON_RING;   //�����O��
		}
		else if (player->CheckHitBox_Box(20, -180, 1240, 380) == true)  //�󒆂̑���S�͈̂̔�
		{
			//�O��������̍s�������Ă���
			if ( Pre_Action == ACT_TYPE::CLIMB_CORNER_LEFT || Pre_Action == ACT_TYPE::CLIMB_CORNER_RIGHT )
			{
				Player_State = PLAYER_STATE::ON_FLOOR_LURK;  //�����Ő���ł���
			}
			else 
				Player_State = PLAYER_STATE::ON_FLOOR;       //�����
		}
		else if (player->CheckHitBox_Box(20, 620, 200, 80) == true || player->CheckHitBox_Box(1060, 620, 200, 80) == true)
		{
			Player_State = PLAYER_STATE::OUT_RING;  //��O�i�����O�O�j
		}
		else
		{
			Player_State = PLAYER_STATE::DO_NOT;    //���f���Ȃ�
		}
	}
}


//�s�����������i�ڐG����񂯂�I����@�p�j
void Enemy_07::Init_MoveAndAction()
{
	Player_State = PLAYER_STATE::DO_NOT;
	Now_Action = ACT_TYPE::NO_ACT;
	Pre_Action = ACT_TYPE::NO_ACT;
}

//�i�_�C�u���Ɂj�����蔻����Ƃ�Ȃ�  true : �_�C�u���B�����蔻����Ƃ�Ȃ� 
bool Enemy_07::Is_Diving_Collision()
{
	// Action�̓_�C�u ���� �����O��荂���ʒu�ɂ���  ���@�@�W�����v���i����Ɉ���������Ȃ��悤�Ɂj  
	if (Now_Action == ACT_TYPE::DIVE_OUT_LEFT && y < (_CONSTANTS_07::RING_HEIGHT - (h / 2)) ||
		Now_Action == ACT_TYPE::DIVE_OUT_RIGHT && y < (_CONSTANTS_07::RING_HEIGHT - (h / 2)))
	{
		return true;
	}
	return false;
}

//�i�_�C�u���Ɂj�ڐG����񂯂�����Ȃ�  true : �_�C�u���B�ڐG����񂯂�����Ȃ�
bool Enemy_07::Is_Diving_TouchJanken()
{
	if (Now_Action == ACT_TYPE::DIVE_OUT_LEFT || Now_Action == ACT_TYPE::DIVE_OUT_RIGHT)
	{
		return true;
	}
	return false;
}

/*--------------------------------------------------------------------------------------*/

//360�x����
void Enemy_07::Jan_360degrees()
{
	//�������邶��񌂂̔��a
	float radius = 25.5f;

	//�����_���ȑ����𐶐�
	Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	//45�x����8����
	for (int i = jan_count; i < (jan_count + 8); i++)
	{
		double angle = static_cast<double>((45.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, radius, speed, angle, type);
	}
}

//�c�ɂ������񔭎ˁi����j
void Enemy_07::Jan_Vertical(int count, float rad, float speed, Jan_Type type)
{
	//4����
	obj_jangeki[count]     = new Jangeki_Vertical(x, y, rad, -speed, (y + 50), type);
	obj_jangeki[count + 1] = new Jangeki_Vertical(x, y, rad, -speed, (y + 75), type);
	obj_jangeki[count + 2] = new Jangeki_Vertical(x, y, rad, -speed, (y - 50), type);
	obj_jangeki[count + 3] = new Jangeki_Vertical(x, y, rad, -speed, (y - 75), type);
}



