#include "Enemy_07.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Vertical.h"
#include<typeinfo>

#define _USE_MATH_DEFINES
#include<math.h>

//�萔
namespace _ENEMY_07
{
	const float RING_LEFT  = 250.0f;    //�����O���[
	const float RING_RIGHT = 1030.0f;   //�����O�E�[


	char state_string[][10] = { "ON_RING","DO_NOT" };   //�e�X�g�p
	char action_str[][15] = { "NO_ACT","LEFT_TO_RIGHT","RIGHT_TO_LEFT" };
}

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_07::Enemy_07(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
, Player_State(PLAYER_STATE::DO_NOT), Now_Action(ACT_TYPE::NO_ACT)
{
	speed = 3.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

	//�p�^�[���icsv�Ɂj
	moveinfo[0] = { 1,620.f,0.f,1 };
	moveinfo[1] = { 1,1030.f,0.f,0 };
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
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

	LPCTSTR string = _ENEMY_07::state_string[static_cast<int>(Player_State)];
	LPCTSTR string_act = _ENEMY_07::action_str[static_cast<int>(Now_Action)];

	DrawString(200, 300, string, 0xff0000);
	DrawString(200, 330, string_act, 0xff0000);
}

//����񌂐����E�X�V
void Enemy_07::Update_Jangeki()
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
		float radius = 25.5f;   //���a
		float speed = 6.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//����
		if (frame_count % 120 == 0)
		{
			switch (GetRand(2))
			{
			case 0:
				Jan_360degrees(jan_count, radius, speed, type);
				break;

			case 1:
				obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
				break;

			case 2:
				Jan_Vertical(jan_count, radius, speed, type);
				break;

			default:
				break;
			}

		}
	}

}

//�s���p�^�[���ɉ������s��
void Enemy_07::Move_Pattern()
{
	//�ړ���
	float move_x = x;
	float move_y = y;

	//�ڕW���W�Ɗ��S��v�ix���W�����j
	if (x == moveinfo[current].location_x)
	{
		current = moveinfo[current].next_index;   //���̃p�^�[����
	}

	//x���W���ڕW�ƕs��v
	if (x != moveinfo[current].location_x)
	{
		//�ڕW�̕����傫���i�ڕW�͉E�����j
		if (x < moveinfo[current].location_x)
		{
			move_x += speed;      //�E�ړ��i���̒l�j

			//�ڕW�𒴂����ꍇ
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{
				move_x = moveinfo[current].location_x;     //�ڕW���W�ŌŒ�
			}
		}
		else
		{
			move_x -= speed; //���ړ��i���̒l�j

			//�ڕW�𒴂����ꍇ
			if (move_x <= moveinfo[current].location_x && moveinfo[current].location_x <= x)
			{
				move_x =  moveinfo[current].location_x;     //�ڕW���W�ŌŒ�
			}
		}
	}

	//�ړ��𔽉f
	x = move_x;
	y = move_y;
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

	switch (Player_State)
	{
	case PLAYER_STATE::ON_RING:    //�����O��

		Move_ON_RING(target_x, target_y);
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

	//�s�����łȂ�
	if (Now_Action == ACT_TYPE::NO_ACT)
	{
		//�v���C���[��������荶��
		if (player_x < (1280 / 2))
		{
			Now_Action = ACT_TYPE::RIGHT_TO_LEFT;  //�E����
			match = false;
		}
		else
		{
			Now_Action = ACT_TYPE::LEFT_TO_RIGHT;  //�����E
			match = false;
		}
	}

	//�E����
	if (Now_Action == ACT_TYPE::RIGHT_TO_LEFT)
	{
		/*******************************�@�P  **++***************************/
		{
			//�����O�E��ڎw��
			if (match == false) target_x = _ENEMY_07::RING_RIGHT - (w / 2);

			//�����O�E�ɓ��B
			if (x == _ENEMY_07::RING_RIGHT - (w / 2))
			{
				match = true;  //1�ԖڏI��
				speed = 9.0f;  //�X�s�[�h�A�b�v
			}
		}
		/*******************************************************************/


		//�����O�E�ɓ��B�����̂��A�����O����ڎw��

		/*******************************�@�Q  **++***************************/
		{
			//�����O����ڎw��
			if (match == true) target_x = _ENEMY_07::RING_LEFT + (w / 2);

			//�����O���ɓ��B                             
			if (x == _ENEMY_07::RING_LEFT + (w / 2))
			{
				Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
				speed = 3.0f;                   //�X�s�[�h��߂�
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
			if (match == false) target_x = _ENEMY_07::RING_LEFT + (w / 2);

			//�����O�E�ɓ��B
			if (x == _ENEMY_07::RING_LEFT + (w / 2))
			{
				match = true;  //1�ԖڏI��
				speed = 9.0f;  //�X�s�[�h�A�b�v
			}
		}
		/*******************************************************************/


		//�����O���ɓ��B�����̂��A�����O�E��ڎw��

		/*******************************�@�Q  **++***************************/
		{
			//�����O�E��ڎw��
			if (match == true) target_x = _ENEMY_07::RING_RIGHT - (w / 2);

			//�����O�E�ɓ��B                            
			if (x == _ENEMY_07::RING_RIGHT - (w / 2))
			{
				Now_Action = ACT_TYPE::NO_ACT;  //Action�̊���
				speed = 3.0f;                   //�X�s�[�h��߂�
			}
		}
		/*******************************************************************/
	}
}


//�v���C���[�̏󋵂��擾
void Enemy_07::CheckPlayerState(const Player* player)
{
	//�����蔻������p          �����O��͈̔�
	if (player->CheckHitBox_Box(220, 260, 840, 330) == true)
	{
		Player_State = PLAYER_STATE::ON_RING;   //�����O��
	}
	else
	{
		Player_State = PLAYER_STATE::DO_NOT;    //�����O��ł͂Ȃ�
	}
}


/*--------------------------------------------------------------------------------------*/

//360�x���ˁi�K�E�j
void Enemy_07::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	//45�x����8����
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
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



