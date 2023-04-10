#include"Enemy_01.h"
#include"DxLib.h"
#include<math.h>
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"

//�萔�@
namespace _CONSTANTS_01
{
	// "����"�͉�ʉE���珇�� 1,2,3,....�Ɣԍ�������
	const float FLOOR_NO_01_X = 1150.0f;   //����P (���S�����W)
	const float FLOOR_NO_01_Y = 500.0f;    //����P (���S�����W)

	const float FLOOR_NO_02_X = 950.0f;    //����Q (���S�����W)
	const float FLOOR_NO_02_Y = 290.0f;    //����Q (���S�����W)

	const float FLOOR_NO_03_X = 560.0f;    //����R (���S�����W)
	const float FLOOR_NO_03_Y = 140.0f;    //����R (���S�����W)

	const float FLOOR_NO_03_L = 350.0f;    //����R�i�������W�j
	const float FLOOR_NO_03_R = 770.0f;    //����R�i�E�����W�j

	const float FLOOR_NO_04_X = 110.0f;    //����S (���S�����W)
	const float FLOOR_NO_04_Y = 290.0f;    //����S (���S�����W)

	const float FLOOR_NO_05_X = 310.0f;    //����T (���S�����W)
	const float FLOOR_NO_05_Y = 500.0f;    //����T (���S�����W)

	//const float FLOOR_NO_03 = 790.0f;   //����R (���S�����W)
	//const float FLOOR_NO_04 = 1185.0f;  //����S (���S�����W)

}


//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_01::Enemy_01(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
, Now_Action(ACT_TYPE::NOT_ACT), jan_count(0), current_action(0)
{
	speed = 4.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��
}

//�f�X�g���N�^
Enemy_01::~Enemy_01()
{

}


//�X�V
void Enemy_01::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

	Move_Controller();

	/********************   �W�����v�֌W   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	//{
	//	g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
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
void Enemy_01::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();


	//DrawFormatString(50, 100, 0xff00ff, "Current : %d", current_action);

}

//����񌂐����E�X�V
void Enemy_01::Update_Jangeki()
{
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

	////�z��̋�v�f
	//if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	//{
	//	float radius = 35.5f;   //���a
	//	float speed = -2.0f;     //�X�s�[�h

	//	//�����_���ȑ����𐶐�
	//	Jan_Type type = static_cast<Jan_Type>(GetRand(2));


	//	//����
	//	if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	//}
}


//�W�����v�i�W�����v�́j
void Enemy_01::Jump_Enemy(float g_add)
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

//�s������
void Enemy_01::Move_Controller()
{
	//�ڕW���W
	float target_x = 0;
	float target_y = 0;

	//�ړ���
	float move_x = x;
	float move_y = y;

	switch (current_action)
	{
	case 0:
		Action01_LR(target_x, target_y);
		break;

	case 1:
		Action02_Jump(target_x, target_y);
		break;

	case 2:
		Action03_Floor_LR(target_x, target_y);
		break;

	case 3:
		Action04_GetOff_Floor_LEFT(target_x, target_y);
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





//���E�ړ�
void Enemy_01::Action01_LR(float& target_x, float& target_y)
{
	// ���B������
	static unsigned short count_ari;

	if (count_ari == 0)
	{
		target_x = 500;

		if (x == 500) count_ari = 1;

		Jump_Enemy();
	}

	if (count_ari == 1 && land_flg == true)
	{
		target_x = 980;

		if (x == 980)
		{
			current_action = 1;  //action�̏I���i���̃A�N�V�����ցj
			count_ari = 0;       //������
		}
	}
}

//�W�����v�ő����n��
void Enemy_01::Action02_Jump(float& target_x, float& target_y)
{
	// ���B������
	static unsigned short count_ari;

	//�W�����v�n�_��ڎw��
	if (count_ari == 0)
	{
		target_x = 990.0f;   //�W�����v�n�_��

		//���B
		if (x == 990.0f)
		{
			Jump_Enemy();   //�W�����v
			count_ari = 1;
		}
	}

	//����1��ڎw��
	if (count_ari == 1)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_01_X;      //����P��ڎw��

		//���B
		if (x == _CONSTANTS_01::FLOOR_NO_01_X && land_flg == true)
		{
			Jump_Enemy();   //�W�����v
			count_ari = 2;
		}
	}

	//����2��ڎw��
	if (count_ari == 2)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_02_X;      //����Q��ڎw��

		//���B
		if (x == _CONSTANTS_01::FLOOR_NO_02_X && y == (_CONSTANTS_01::FLOOR_NO_02_Y - h / 2))
		{
			Jump_Enemy();        //�W�����v
			count_ari = 3;
		}
	}

	//����3��ڎw��
	if (count_ari == 3)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_03_X;      //����R��ڎw��

		//���B
		if (x == _CONSTANTS_01::FLOOR_NO_03_X && y == (_CONSTANTS_01::FLOOR_NO_03_Y - h / 2))
		{
			current_action = 2;  //�A�N�V�����̏I���i���̃A�N�V�����ցj
			count_ari = 0;       //������
		}
	}


}

//��������������
void Enemy_01::Action03_Floor_LR(float& target_x, float& target_y)
{
	// ���B������
	static unsigned short count_ari;

	//�ŏ��ɍ�
	if (count_ari == 0 || count_ari == 2)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_03_L;

		if (x == _CONSTANTS_01::FLOOR_NO_03_L)
		{
			//����񌂂𔭎�
			Fire_JanTakeAim(player_x, player_y);

			count_ari++;
		}
	}

	//���ɉE
	if (count_ari == 1 || count_ari == 3)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_03_R;

		if (x == _CONSTANTS_01::FLOOR_NO_03_R)
		{
			//����񌂂𔭎�
			Fire_JanTakeAim(player_x, player_y);

			count_ari++;

			if (count_ari == 4)
			{
				current_action = 3;  //�A�N�V�����̏I���i���̃A�N�V�����ցj
				count_ari = 0;       //������
			}
		}
	}
}

//�����������~���
void Enemy_01::Action04_GetOff_Floor_LEFT(float& target_x, float& target_y)
{
	// ���B������
	static unsigned short count_ari;

	if (x == 330) Jump_Enemy();

	//����4��ڎw��
	if (count_ari == 0)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_04_X;

		if (x == _CONSTANTS_01::FLOOR_NO_04_X)
		{
			count_ari = 1;
		}
	}


	//����5��ڎw��
	if (count_ari == 1)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_05_X;

		if (x == _CONSTANTS_01::FLOOR_NO_05_X)
		{
			current_action = 1;  //�A�N�V�����̏I���i"�W�����v�ő����n��"�ցj
			count_ari = 0;       //������
		}
	}
}

//�v���C���[�ڊ|���Ă���񌂂𔭎˂���
void Enemy_01::Fire_JanTakeAim(const float& player_x, const float& player_y)
{
	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //���a
		float speed = 2.5f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//����
		obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
	}
}