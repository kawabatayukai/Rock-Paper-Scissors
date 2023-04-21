#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include "Player.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Player.h"

//����񌂔��ˊԊu�@�i1�b�j
#define PLAYER_JAN_INTERVAL 30


//�R���X�g���N�^�@�@�@�@�@�@�@�@�@�@�@�@�@  ���@���@���@�@�@����
Player::Player(float x, float y) : CharaBase(x, y, 57.0f, 100.0f)  //���N���X�̃R���X�g���N�^���Ă�
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0)
{
	speed = 7.0f;
	hp = 100;

	//������ݒ�i�E�j
	dir = static_cast<int>(DIRECTION::RIGHT);//LEFT
	 
	//�摜�ǂݍ���
	//image = LoadGraph("images/sd_body-1.png");
	LoadDivGraph("images/�����p���}��ALL�摜�r����3.png", 10, 5, 2, 100, 100, image);
	//LoadDivGraph("images/�����p���}���摜�疳��.png", 10, 5, 2, 100, 100, image);

	//LoadDivGraph("images/�����p���}��ALL�摜�r����3.png", 2, 1, 2, 126, 125, image_Jamp);

	LoadDivGraph("images/�����p���}���W�����v�摜�r����.png", 3, 3, 1, 100, 100, image_JanType);  //����񌂉摜

	image[4] = LoadGraph("images/�����p���}���W�����v�摜�r�����E.png");
	image[9] = LoadGraph("images/�����p���}���W�����v�摜�r������.png");

	image_setsumei = LoadGraph("images/Setumei.png");

	head_Image[0] = LoadGraph("images/�����p���}����̂�.png");
	head_Image[1] = LoadGraph("images/�����p���}����̂ݍ�.png");

	armL_Image[0] = LoadGraph("images/�r�݂̂��[h��.png");
	armR_Image[0] = LoadGraph("images/�r�݂̂��[h�E.png");

	armL_Image[1] = LoadGraph("images/�r�݂̂��傫��.png");
	armR_Image[1] = LoadGraph("images/�r�݂̂��傫�E.png");

	armL_Image[2] = LoadGraph("images/�r�݂̂ρ[��.png");
	armR_Image[2] = LoadGraph("images/�r�݂̂ρ[�E.png");

	hpImage = LoadGraph("images/HitPoint.png");

	Init_Jangeki();       //����񌂂�p��

	//�f�t�H���g�� �O�[
	select_JanType = Jan_Type::ROCK;

	//�t�H���g���쐬
	ui_font = CreateFontToHandle("���C���I", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//�R���X�g���N�^�i�R�s�[�R���X�g���N�^�j
Player::Player(const Player& player) : CharaBase(player.x, player.y, player.w, player.h)  //���N���X�̃R���X�g���N�^���Ă�
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0)
{
	//�����o�ϐ��������̃I�u�W�F�N�g�̓��e�ŏ���������
	// 
	//
	//�����o�Ƀ|�C���^�ϐ����܂ނ��ߒ���


/************ ���N���X�@CharaBase�@�̓��e ************/

	this->speed = player.speed;       //�X�s�[�h
	this->hp = player.hp;          //HP
	this->dir = player.dir;         //����
	this->land_flg = player.land_flg;    //�ڒn�t���O

	Init_Jangeki();       //����񌂂�p�Ӂi����񌂂͈����p���Ȃ��j

/************* �����܂Ł@CharaBase�@�̓��e *************/


	//this->image = player.image;             //�v���C���[�摜
	this->select_JanType = player.select_JanType;    //�I������"��"
	this->jan_angle = player.jan_angle;              //����񌂊p�x
	LoadDivGraph("images/�����p���}��ALL�摜�r����.png", 10, 5, 2, 100, 100, image);
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //����񌂉摜
	image_setsumei = LoadGraph("images/Setumei.png");

	armL_Image[0] = LoadGraph("images/�r�݂̂��[h��.png");
	armR_Image[0] = LoadGraph("images/�r�݂̂��[h�E.png");

	armL_Image[1] = LoadGraph("images/�r�݂̂��傫��.png");
	armR_Image[1] = LoadGraph("images/�r�݂̂��傫�E.png");

	armL_Image[2] = LoadGraph("images/�r�݂̂ρ[��.png");
	armR_Image[2] = LoadGraph("images/�r�݂̂ρ[�E.png");

	hpImage = LoadGraph("images/HitPoint.png");

	//�t�H���g���쐬
	ui_font = CreateFontToHandle("���C���I", 20, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
}

//�f�X�g���N�^
Player::~Player()
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(ui_font);
}

//�X�V
void Player::Update()
{
	//�O��̍��W����ۑ�
	old_x = x;

	//��
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
	{
		x -= speed;
		if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) //�E�X�e�B�b�N��������ĂȂ���
		{
			dir = static_cast<int>(DIRECTION::LEFT);   //������ݒ�i���j
		}
	}
	playerChange_Image = 2; //switch���̊��蓖�Ĕԍ�

	//�E
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
	{
		x += speed;
		if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) //�E�X�e�B�b�N��������ĂȂ���
		{
			dir = static_cast<int>(DIRECTION::RIGHT);   //������ݒ�i�E�j
		}
	}
	playerChange_Image = 1; //switch���̊��蓖�Ĕԍ�

	//�摜�̑I��ύX
	PlayerSwitch();

	//�����
	Update_Jangeki();

	/********************   �W�����v�֌W   ********************/

	if (land_flg == true && KeyManager::OnPadClicked(PAD_INPUT_5))
	{
		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l��
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/



//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�Ə��@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

	//�E�X�e�B�b�N�̃A�i���O���͂��擾
	double right_x = static_cast<double>(KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X));   //��
	double right_y = static_cast<double>(KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y));   //��

	//���͒l�𐧌�(�킩��₷��)
	if (right_x > 30000) right_x = 30000;
	if (right_x < -30000) right_x = -30000;
	if (right_y > 30000) right_y = 30000;
	if (right_y < -30000) right_y = -30000;

	//�t���ڂŏƏ��̊p�x�����߂�
	jan_angle = atan2(static_cast<double>(right_y - y), static_cast<double>(right_x - x));


	//�p�x�𐧌�����
	{
		//�E�����̎�
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true)
		{
			if (/*jan_angle < 0*/KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) jan_angle = 0;
			if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
			{
				//jan_angle = (M_PI / 2);
				dir = static_cast<int>(DIRECTION::LEFT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = 0;
		}

		if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
		{
			//jan_angle = (M_PI / 2);
			dir = static_cast<int>(DIRECTION::LEFT);
		}

		//�������̎�
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
		{
			if (/*jan_angle < 0*/KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0) jan_angle = M_PI;
			if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
			{
				//jan_angle = (M_PI / 2);
				dir = static_cast<int>(DIRECTION::RIGHT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = M_PI;
		}

		if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
		{
			//jan_angle = (M_PI / 2);
			dir = static_cast<int>(DIRECTION::RIGHT);
		}

		//������̎�
		if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_UP) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = jan_angle / 2;
		}
		if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_DOWN) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = jan_angle / -2;
		}

		//�������̎�
		if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_UP) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = M_PI / 2;
		}
		if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_DOWN) &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			jan_angle = M_PI / -2;
		}
	}



	////�v���C���[���W
	//DrawFormatString(300, 200, 0xffffff, "Player_X : %f", x);
	//DrawFormatString(300, 230, 0xffffff, "Player_Y : %f", y);

	////�E�X�e�B�b�N�A�i���O���͒l
	//DrawFormatString(500, 300, 0xffffff, "Right_X : %d", static_cast<int>(right_x));
	//DrawFormatString(500, 330, 0xffffff, "Right_Y : %d", static_cast<int>(right_y));

	//DrawFormatString(500, 430, 0xffffff, "�t���ڍ��W_X : %lf", static_cast<double>(right_x - x));
	//DrawFormatString(500, 460, 0xffffff, "�t���ڍ��W_Y : %lf", static_cast<double>(right_y - y));
	//DrawFormatString(500, 490, 0xffffff, "�t����(�ʓx�@) : %lf", jan_angle * 180 / M_PI);
	//DrawFormatString(500, 360, 0xffffff, "Angle : %lf", jan_angle);

//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
}

/* ���̕`��E����(���Ԃ���������)*/
void Player::HeadDrawMove() const
{
	///*********************
	//*                    *
	//*   ���̕`��E����   *
	//*                    *
	//*********************/

	//DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
}

/*�r�̕`��E����*/
void Player::ArmDrawMove() const
{
	/*********************
	*                    *
	*   �r�̕`��E����   *
	*                    *
	*********************/

	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	switch (select_JanType)
	{
	case Jan_Type::ROCK: //�O�[�̎�

		// ������ && �ڒn && �v���C���[�摜�����Ԃ̉摜����Ȃ���  
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image != 2 && player_Image != 7) //���r�̓���
		{
			DrawRotaGraph(x - 20, y + 3, 1.0f, M_PI - jan_angle, armL_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)//�v���C���[�摜�����Ԃ̎�
		{
			DrawRotaGraph(x - 1, y + 3, 1.0f, M_PI - jan_angle, armL_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x - 14, y - 5, 1.0f, M_PI - jan_angle, armL_Image[0], TRUE);
		}

		// �E���� && �ڒn && �v���C���[�摜�����Ԃ̉摜����Ȃ��� 
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image != 2 && player_Image != 7) //�E�r�̓���
		{
			DrawRotaGraph(x + 20, y + 3, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
			//DrawRotaGraph(x + 8, y - 5, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)//�v���C���[�摜�����Ԃ̎�
		{
			DrawRotaGraph(x + 1, y + 3, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x + 14, y - 5, 1.0f, M_PI - jan_angle, armR_Image[0], TRUE);
		}
		break;

	case Jan_Type::SCISSORS: //�`���L�̎�

		// ������ && �ڒn && �v���C���[�摜�����Ԃ̉摜����Ȃ���  
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image != 2 && player_Image != 7) //���r�̓���
		{
			DrawRotaGraph(x - 20, y + 3, 1.0f, M_PI - jan_angle, armL_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)//�v���C���[�摜�����Ԃ̎�
		{
			DrawRotaGraph(x - 1, y + 3, 1.0f, M_PI - jan_angle, armL_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x - 14, y - 5, 1.0f, M_PI - jan_angle, armL_Image[1], TRUE);
		}

		// �E���� && �ڒn && �v���C���[�摜�����Ԃ̉摜����Ȃ���  
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image != 2 && player_Image != 7) //�E�r�̓���
		{
			DrawRotaGraph(x + 20, y + 3, 1.0f, M_PI - jan_angle, armR_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)//�v���C���[�摜�����Ԃ̎�
		{
			DrawRotaGraph(x + 1, y + 3, 1.0f, M_PI - jan_angle, armR_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x + 14, y - 5, 1.0f, M_PI - jan_angle, armR_Image[1], TRUE);
		}
		break;

	case Jan_Type::PAPER: //�p�[�̎�

		// ������ && �ڒn && �v���C���[�摜�����Ԃ̉摜����Ȃ���  
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image != 2 && player_Image != 7) //���r�̓���
		{
			DrawRotaGraph(x - 20, y + 3, 1.0f, M_PI - jan_angle, armL_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)//�v���C���[�摜�����Ԃ̎�
		{
			DrawRotaGraph(x - 1, y + 3, 1.0f, M_PI - jan_angle, armL_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x - 14, y - 5, 1.0f, M_PI - jan_angle, armL_Image[2], TRUE);
		}

		// �E���� && �ڒn && �v���C���[�摜�����Ԃ̉摜����Ȃ��� 
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image != 2 && player_Image != 7) //�E�r�̓���
		{
			DrawRotaGraph(x + 20, y + 3, 1.0f, M_PI - jan_angle, armR_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)//�v���C���[�摜�����Ԃ̎�
		{
			DrawRotaGraph(x + 1, y + 3, 1.0f, M_PI - jan_angle, armR_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x + 14, y - 5, 1.0f, M_PI - jan_angle, armR_Image[2], TRUE);
		}
		break;
	default:
		break;
	}
}

//�v���C���[��UI�`��
void Player::PlayerDrawUI(int hp) const
{
	/*switch (type)
	{
	case Jan_Type::ROCK:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[0], TRUE);
		break;
	case Jan_Type::SCISSORS:

		DrawRotaGraph(810, 60, 0.5, 0, typeImage[1], TRUE);
		break;
	case Jan_Type::PAPER:
		DrawRotaGraph(950, 60, 0.5, 0, typeImage[2], TRUE);
		break;
	default:
		break;
	}*/

	//DrawRotaGraph(200, 50, 0.5, 0, hpImage, TRUE);			//�̗̓Q�[�W�g
	//DrawBox(115, 33, 120 + static_cast<int>(hp * 2.54), 67, 0x00ff00, TRUE);	//�̗̓Q�[�W
	//DrawFormatString(200, 40, 0x0000ff, "�c��:%d", hp);	//�c��̗�(���l)

	float draw_x = x - 50;  //�`�悘
	float draw_y = y - 100; //�`�悙

	int bar_color = 0x00ff00;

	//�g
	DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
	DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
	//HP
	DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
}

//�`��
void Player::Draw() const
{
	//���S����`��
	//DrawRotaGraphF(x, y, 1, 0, image, TRUE,
		//dir == static_cast<int>(DIRECTION::RIGHT) ? TRUE : FALSE);  //�����ɂ���Ĕ��]

	//����񌂕`��
	Draw_Jangeki();

	//�Ə���        �E�X�e�B�b�N�ɓ��͂����鎞
	if (  KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 &&
		  KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 )
	{
		/*�r�̕`�悾��*/
		ArmDrawMove();
	}
	else
	{
		int vx = static_cast<int>(550 * cos(jan_angle));
		int vy = static_cast<int>(550 * sin(jan_angle));

		DrawLineAA(x, y, x + vx, y - vy, 0xffff00, 3);

		/*�r�̕`��E����*/
		ArmDrawMove();
	}

#ifdef DEBUG_OFF_PLAYER

	//�e�X�g HP�\��
	//if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	//DrawFormatString((int)(x), (int)(y - 100), 0xffffff, "%s", dir == 0 ? "L" : "R");

	PlayerDrawUI(GetHP());

	//�e�X�g �I�������
	DrawStringToHandle(30, 105, "SELECT : ", 0xffffff, ui_font);
	DrawRotaGraph(165, 115, 0.5, 0, image_JanType[static_cast<int>(select_JanType)], TRUE);
	DrawStringToHandle(30, 150, "RB : ����", 0xffffff, ui_font);
	DrawStringToHandle(30, 180, "LB : �W�����v", 0xffffff, ui_font);

	//�e�X�g
	//DrawGraph(20, 80, image_setsumei, TRUE);
	DrawRotaGraph(300, 130, 0.5, 0, image_setsumei, TRUE);

#endif // DEBUG_OFF_PLAYER

	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image[player_Image], TRUE);
	//DrawRotaGraphF(x, y, 1, 0, image[9], TRUE);
}

/*�摜�̕ύX�擾*/
void  Player::PlayerSwitch()
{
	/*�v���C���[�̉摜�ύX*/
	switch (playerChange_Image)
	{
		/*���E�ړ�*/
	case 1: //�E�ړ�
	   /*                �E����            �ڒn                   �E�E������Ă�                      */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			playerGetMove = 1;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 0;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}
		/*               ������            �ڒn                   �E�E������Ă�                     */
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			playerGetMove = 6;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 5;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}

		/*�W�����v�̎�*/
		/*         �E����         ��ڒn     */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false)
		{
			player_Image = 4;     //�摜���擾
			break;
		}

	case 2: //���ړ��̎�
	   /*               ������            �ڒn                   ���E������Ă�                     */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			playerGetMove = 6;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 5;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}
		/*               �E����            �ڒn                   ���E������Ă�                     */
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			playerGetMove = 1;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 0;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}

		/*�W�����v�̎�*/
		/*           ������         ��ڒn     */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false)
		{
			player_Image = 9;     //�摜���擾
			break;
		}


	case 0: //�~�܂��Ă���

		/*                              �E����            �ڒn                                           ������ĂȂ�   */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) == FALSE)
		{
			pCount = 0;  //�����ĂȂ��Ƃ��p
		}

		/*                           ������            �ڒn                                           ������ĂȂ�  */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) == FALSE)
		{
			pCount = 5;  //�����ĂȂ��Ƃ��p
		}
		playerGetMove = pCount; //�Ō�ɓ��������̉摜
		playerCount++;          //�t���[���̃J�E���g

		PlayerChangeMoveimg();  //�摜�ύX��
		break;

	default:
		break;
	}
}

/*�摜�̓���ύX*/
void  Player::PlayerChangeMoveimg()
{
	static int std = 0; //�摜�̊

	/*�摜�̕ێ�*/
	switch (playerGetMove)
	{
		/*�E�ړ�*/
	case 1: //1�̉摜
		if (player_Image != 2 && player_Image != 3)
		{
			player_Image = 1;
			std = 1; //�Z�b�g����
		}
		break;
	case 2: //2�̉摜
		if (player_Image != 1 && player_Image != 3)
		{
			player_Image = 2;
			std = 2; //�Z�b�g����
		}
		break;
	case 3: //3�̉摜
		if (player_Image != 1 && player_Image != 2)
		{
			player_Image = 3;
			std = 3; //�Z�b�g����
		}
		break;

		/*���ړ�*/
	case 6: //6�̉摜
		if (player_Image != 7 && player_Image != 8)
		{
			player_Image = 6;
			std = 6; //�Z�b�g����
		}
		break;
	case 7: //7�̉摜
		if (player_Image != 6 && player_Image != 8)
		{
			player_Image = 7;
			std = 7; //�Z�b�g����
		}
		break;
	case 8: //8�̉摜
		if (player_Image != 6 && player_Image != 7)
		{
			player_Image = 8;
			std = 8; //�Z�b�g����
		}
		break;

		/*�W�����v*/
	case 4: //4�̉摜
		player_Image = 4;
		std = 0; //�Z�b�g����
		break;
	case 9: //9�̉摜
		player_Image = 9;
		std = 0; //�Z�b�g����
		break;

		/*�~�܂��Ă���*/
	case 0: //0�̉摜
		player_Image = 0;
		std = 0; //�Z�b�g����
		break;
	case 5: //5�̉摜
		player_Image = 5;
		std = 0; //�Z�b�g����
		break;
	default:
		break;
	}

	/*�����Ă���悤�ɉ摜�ύX*/
	if (playerCount % 10 == 0) //10�t���[�����̏���
	{
		/*�E�ړ�*/
		/*�E���� && �Ə������΂������ĂȂ� && �E�E������Ă���*/
		if (dir == static_cast<int>(DIRECTION::RIGHT) /*&& jan_angle < (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			if (std == 1 && 2 > player_Image) // �摜 1
			{
				player_Image = 2;
				std = 2;
			}
			else if (std == 2 && 3 > player_Image) // �摜 2
			{
				player_Image = 3;
				std = 3;
			}
			else if (std == 3 && 2 < player_Image) //�摜 3
			{
				player_Image = 2;
				std = 4;
			}
			else if (std == 4 && 1 < player_Image) // �摜 2
			{
				player_Image = 1;
				std = 1;
			}
			playerCount = 0;
		}
		/*������ && �E�E������Ă���*/
		else if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			if (std == 6 && 7 > player_Image) // �摜 6
			{
				player_Image = 7;
				std = 7;
			}
			else if (std == 7 && 8 > player_Image) // �摜 7
			{
				player_Image = 8;
				std = 8;
			}
			else if (std == 8 && 7 < player_Image) // �摜 8
			{
				player_Image = 7;
				std = 9;
			}
			else if (std == 9 && 6 < player_Image) // �摜 7
			{
				player_Image = 6;
				std = 6;
			}
			playerCount = 0;
		}

		/*���ړ�*/
		/*������ && �Ə������΂������ĂȂ� && ���E������Ă���*/
		if (dir == static_cast<int>(DIRECTION::LEFT) /*&& jan_angle > (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			if (std == 6 && 7 > player_Image) // �摜 6
			{
				player_Image = 7;
				std = 7;
			}
			else if (std == 7 && 8 > player_Image) // �摜 7
			{
				player_Image = 8;
				std = 8;
			}
			else if (std == 8 && 7 < player_Image) // �摜 8
			{
				player_Image = 7;
				std = 9;
			}
			else if (std == 9 && 6 < player_Image) // �摜 7
			{
				player_Image = 6;
				std = 6;
			}
			playerCount = 0;
		}
		/*�E���� && ���E������Ă���*/
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			if (std == 1 && 2 > player_Image) // �摜 1
			{
				player_Image = 2;
				std = 2;
			}
			else if (std == 2 && 3 > player_Image) // �摜 2
			{
				player_Image = 3;
				std = 3;
			}
			else if (std == 3 && 2 < player_Image) //�摜 3
			{
				player_Image = 2;
				std = 4;
			}
			else if (std == 4 && 1 < player_Image) // �摜 2
			{
				player_Image = 1;
				std = 1;
			}
			playerCount = 0;
		}
	}
}

//����񌂐����E�X�V
void Player::Update_Jangeki()
{
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();
		obj_jangeki[jan_count]->SetTargetLocation(enemy_x, enemy_y);  //����񌂂ɓG�̍��W���Z�b�g

		//��ʊO�ō폜����
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ���� ���ˁE���� ���� ***********************/

	// B,Y,X�@�{�^���Ŕ��˂��邶��񌂑�����I���i�Z�b�g�j����
	if (KeyManager::OnPadClicked(PAD_INPUT_B))         //B�{�^��
	{
		//  �O�[��I�� 
		select_JanType = Jan_Type::ROCK;
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_4))    //Y�{�^��
	{
		//  �`���L��I�� 
		select_JanType = Jan_Type::SCISSORS;
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_3))    //X�{�^��
	{
		//  �p�[��I�� 
		select_JanType = Jan_Type::PAPER;
	}
	else {}


	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //���a
		float speed = 8.0f;     //�X�s�[�h

		//������ �}�C�i�X�����@�@�E�����@�v���X����
		speed = speed * (dir == static_cast<int>(DIRECTION::LEFT) ? -1 : 1);

		//RB�{�^���őI�����������̂���񌂂𔭎�
		if (KeyManager::OnPadClicked(PAD_INPUT_6) == true && jan_interval == 0)
		{
			//�p�x�����鎞�i�Ə��g�p���j
			if (jan_angle != 0)
			{
				//����񌂐���        (�p�x�w��t��)                                        
				obj_jangeki[jan_count] = new Jangeki_Player(x, y, radius, speed, jan_angle, select_JanType);
			}
			else
			{
				//����񌂐���        (�p�x�w��Ȃ�)                                        
				obj_jangeki[jan_count] = new Jangeki_Player(x, y, radius, speed, select_JanType);
			}

			//�Ԋu�ݒ�
			jan_interval = PLAYER_JAN_INTERVAL;
		}
	}

	//�Ԋu
	jan_interval--;
	if (jan_interval < 0) jan_interval = 0;
}

//�z�[�~���O����ꐶ��
void Player::Create_Homing(int jan_count, float x, float y, float r, float speed, Jan_Type type)
{
	//�s���ȏꍇ�͏������Ȃ�
	if (jan_count > JANGEKI_MAX || jan_count < 0)  return;

	//��U�폜
	delete obj_jangeki[jan_count];
	
	//�z�[�~���O�𐶐�
	obj_jangeki[jan_count] = new Jangeki_Homing(x, y, r, speed, type);
}

//�G�̍��W���擾
void Player::SetEnemyLocation(const float x, const float y)
{
	this->enemy_x = x;
	this->enemy_y = y;
}

//old_y�̎擾�֐�
int Player::Get_OldX()
{
	return static_cast<int>(old_x);
}

//y�̎擾�֐�
int Player::Get_X()
{
	return static_cast<int>(x);
}

//old_y�̎擾�֐�
int Player::Get_OldY()
{
	return static_cast<int>(old_y);
}

//y�̎擾�֐�
int Player::Get_Y()
{
	return static_cast<int>(y);
}

//HP�񕜁i���� : �񕜗ʁj
void Player::Recover_HP(const unsigned int recovery)
{
	//HP�ő�ʁi�����͗v���P�j
	int max_hp = 100;

	this->hp += recovery;
	if (hp > max_hp) hp = max_hp;
}