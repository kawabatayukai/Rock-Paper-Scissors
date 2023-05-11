#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include "Player.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Jangeki_Homing.h"
#include"Jangeki_Player.h"
#include"GameData.h"
#include"SoundSystem.h"
#include"SortSave.h"

//����񌂔��ˊԊu�@�i1�b�j
#define PLAYER_JAN_INTERVAL 30


//�R���X�g���N�^�@�@�@�@�@�@�@�@�@�@�@�@�@  ���@���@���@�@�@����
Player::Player(float x, float y) : CharaBase(x, y, 57.0f, 100.0f)  //���N���X�̃R���X�g���N�^���Ă�
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0), player_state(PLAYER_STATE::ALIVE), playerCount2(0), Prev_recoveryScore(0)
, obj_effect(nullptr), obj_effectchange(nullptr)
{
	speed = 7.0f;
	hp = 100;

	//������ݒ�i�E�j
	dir = static_cast<int>(DIRECTION::RIGHT);//LEFT
	 
	//�摜�ǂݍ���
	
	//��
	head_Image[0] = LoadGraph("images/�����p���}���ڂȂ��E.png");
	head_Image[1] = LoadGraph("images/�����p���}���ڂȂ���.png");
	head_Image[2] = LoadGraph("images/�����p���}���ڂȂ��E��.png");
	head_Image[3] = LoadGraph("images/�����p���}���ڂȂ�����.png");
	//head_Image[0] = LoadGraph("images/�����p���}����̂݉E.png");
	//head_Image[1] = LoadGraph("images/�����p���}����̂ݍ�.png");

	//��
	eye_ImageR[0] = LoadGraph("images/�����p���}���ڂ̂݉E.png");
	eye_ImageL[0] = LoadGraph("images/�����p���}���ڂ̂ݍ�.png");
	eye_ImageR[1] = LoadGraph("images/�����p���}���ڂނ��E.png");
	eye_ImageL[1] = LoadGraph("images/�����p���}���ڂނ���png");

	//��
	LoadDivGraph("images/�����p���}���摜�疳���O�[.png", 10, 5, 2, 100, 100, image[0]);
	LoadDivGraph("images/�����p���}���摜�疳���`���L.png", 10, 5, 2, 100, 100, image[1]);
	LoadDivGraph("images/�����p���}���摜�疳���p�[.png", 10, 5, 2, 100, 100, image[2]);

	image[0][4] = LoadGraph("images/�����p���}���W�����v�摜�r�����E�O�[.png");
	image[0][9] = LoadGraph("images/�����p���}���W�����v�摜�r�������O�[.png");

	image[1][4] = LoadGraph("images/�����p���}���W�����v�摜�r�����E�`���L.png");
	image[1][9] = LoadGraph("images/�����p���}���W�����v�摜�r�������`���L.png");

	image[2][4] = LoadGraph("images/�����p���}���W�����v�摜�r�����E�p�[.png");
	image[2][9] = LoadGraph("images/�����p���}���W�����v�摜�r�������p�[.png");

	//�r
	armL_Image[0] = LoadGraph("images/�r�݂̂��[h��.png");
	armR_Image[0] = LoadGraph("images/�r�݂̂��[h�E.png");

	armL_Image[1] = LoadGraph("images/�r�݂̂��傫��.png");
	armR_Image[1] = LoadGraph("images/�r�݂̂��傫�E.png");

	armL_Image[2] = LoadGraph("images/�r�݂̂ρ[��.png");
	armR_Image[2] = LoadGraph("images/�r�݂̂ρ[�E.png");

	//���S��
	image_death = LoadGraph("images/�����p���}����̂ݍ���.png");

	image_setsumei = LoadGraph("images/Setumei.png");
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //����񌂉摜
	image_setsumei = LoadGraph("images/Janken/Setumei50ptg.png");
	image_set_circle = LoadGraph("images/Janken/Setumei_Select50.png");
	image_set_LTRT = LoadGraph("images/Janken/Setumei_LTRT_235_105.png");
	image_set_GPT = LoadGraph("images/Janken/Setumei_GTP.png");

	hpImage = LoadGraph("images/HitPoint.png");

	Init_Jangeki();       //����񌂂�p��

	//�f�t�H���g�� �O�[
	select_JanType = Jan_Type::ROCK;

	//�t�H���g���쐬
	ui_font = CreateFontToHandle("���C���I", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//�t�H���g���쐬
	name_font = CreateFontToHandle("���C���I", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	LoadDivGraph("images/stage09/teleport2.png", 15, 15, 1, 120, 150, img_Playeranim); //img_Playeranim
}

//�R���X�g���N�^�i�R�s�[�R���X�g���N�^�j
Player::Player(const Player& player) : CharaBase(player.x, player.y, player.w, player.h)  //���N���X�̃R���X�g���N�^���Ă�
, player_Image(0), playerGetMove(0), playerCount(0), playerChange_Image(0), pCount(0), player_state(PLAYER_STATE::ALIVE), playerCount2(0)
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
	LoadDivGraph("images/�����p���}��ALL�摜�r����.png", 10, 5, 2, 100, 100, image[0]);
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //����񌂉摜
	image_setsumei = LoadGraph("images/Janken/Setumei50ptg.png");
	image_set_circle = LoadGraph("images/Janken/Setumei_Select50.png");
	image_set_LTRT = LoadGraph("images/Janken/Setumei_LTRT_235_105.png");
	image_set_GPT = LoadGraph("images/Janken/Setumei_GTP.png");

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
	//�v���C���[��HP��0�ȉ��̎��܂��͎��Ԑ؂�A"����"��Ԃ�
	if (this->hp <= 0 || GameData::Get_Each_Time() <= 0) player_state = PLAYER_STATE::DEATH;

	//�O��̍��W����ۑ�
	old_x = x;

	//�X�R�A1000����HP��
	int _score = GameData::Get_MaxScore();
	if (_score % 300 == 0 && _score != Prev_recoveryScore)
	{
		Prev_recoveryScore = _score;
		Recover_HP(20);

		if (obj_effect == nullptr) obj_effect = new Effect_Player(x, y);
	}

	//�G�t�F�N�g
	if (obj_effect != nullptr)
	{
		obj_effect->SetPlayerLocation(x, y);
		obj_effect->Update();

		//�Đ��I��
		if (obj_effect->IsEffectFinished() == true)
		{
			delete obj_effect;
			obj_effect = nullptr;
		}
	}
	//�G�t�F�N�g
	if (obj_effectchange != nullptr)
	{
		obj_effectchange->SetPlayerLocation(x, y);
		obj_effectchange->Update();

		//�Đ��I��
		if (obj_effectchange->IsEffectFinished() == true)
		{
			delete obj_effectchange;
			obj_effectchange = nullptr;
		}
	}

	//���S���ȊO
	if (player_state == PLAYER_STATE::ALIVE)
	{
		//��
		if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))
		{
			x -= speed;

			if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 
				&& KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 /*|| x < old_x*/) //�E�X�e�B�b�N��������ĂȂ���
			{
				dir = static_cast<int>(DIRECTION::LEFT);   //������ݒ�i���j
			}
		}
		playerChange_Image = 2; //switch���̊��蓖�Ĕԍ�

		//�E
		if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT))
		{
			x += speed;
			if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 
				&& KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0 /*|| x > old_x*/) //�E�X�e�B�b�N��������ĂȂ���
			{
				dir = static_cast<int>(DIRECTION::RIGHT);   //������ݒ�i�E�j
			}
		}
		/*else
		{
			x--;
		}*/
		playerChange_Image = 1; //switch���̊��蓖�Ĕԍ�

		//�摜�̑I��ύX
		PlayerSwitch();

		//if (land_flg == true && KeyManager::OnPadClicked_LT())
		if (land_flg == true && KeyManager::OnPadClicked(PAD_INPUT_5))
		{
			g_add = -21.5f;    //�d�͉����x���}�C�i�X�l��
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

			//SE
			SoundSystem::PlaySE(SE::PLAYER_JUMP);
		}
	}
	else if(player_state == PLAYER_STATE::DEATH)
	{
		static bool isJumped;
		jan_angle = 0.0;

		if (land_flg == false && isJumped == false) 
		{
			land_flg = true;
		}

		if (land_flg == true)
		{
			isJumped = true;
			g_add = -24.5f;    //�d�͉����x���}�C�i�X�l��
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
		}
		w = 0;
		h = 0;

		if (y > 780.f)
		{
			player_state = PLAYER_STATE::DEATH_END;
		}
	}

	//�����
	Update_Jangeki();

	/********************   �W�����v�֌W   ********************/

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (player_state != PLAYER_STATE::DEATH)
	{
		if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);
	}


	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	if (y > old_y) land_flg = false;

	/**********************************************************/



//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�@�Ə��@�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

	static double old_angle;

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
			if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
			{
				//�p�x���Ȃ��ɂ���
				jan_angle = 0;
			}
			if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
			{
				dir = static_cast<int>(DIRECTION::LEFT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			//�p�x���Ȃ��ɂ���
			jan_angle = 0;
		}

		if (jan_angle > (M_PI / 2) || jan_angle < (M_PI / -2))
		{
			dir = static_cast<int>(DIRECTION::LEFT);
		}

		//�������̎�
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
		{
			if (/*jan_angle < 0*/KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
			{
				//�p�x���Ȃ��ɂ���
				jan_angle = M_PI;
			}
			if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
			{
				dir = static_cast<int>(DIRECTION::RIGHT);
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false && 
			    KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 && KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			//�p�x���Ȃ��ɂ���
			jan_angle = M_PI;
		}

		if (jan_angle < (M_PI / 2) && jan_angle > (M_PI / -2))
		{
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

	//�p�x��ێ�����
	if (old_angle != jan_angle)
	{
       old_angle = jan_angle;
	}
	

//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
}

/* ���̕`��E����)*/
void Player::HeadDrawMove() const
{
	///*********************
	//*                    *
	//*   ���̕`��̂�     *
	//*                    *
	//*********************/

	//DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);

	/*HP�������ȏ�̎�*/
	if (this->hp > 50)
	{
		/*�E����*/
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
		{
			//DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);

			/*������*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x + 3, y - 18, 1.0f, M_PI, head_Image[0], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
		{
			DrawRotaGraph(x + 3, y - 19, 1.0f, M_PI, head_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
		{
			DrawRotaGraph(x - 7, y - 19, 1.0f, M_PI, head_Image[0], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
		{
			DrawRotaGraph(x + 5, y - 17, 1.0f, M_PI, head_Image[0], TRUE);
		}
		/*else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);
		}*/

		/*������*/
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
		{
			//DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);

			/*������*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x - 3, y - 18, 1.0f, 0, head_Image[1], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
		{
			DrawRotaGraph(x - 3, y - 19, 1.0f, 0, head_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
		{
			DrawRotaGraph(x + 7, y - 19, 1.0f, 0, head_Image[1], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
		{
			DrawRotaGraph(x - 5, y - 17, 1.0f, 0, head_Image[1], TRUE);
		}
		/*else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //�W�����v�̎�
		{
			DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);
		}*/
	}
	/*HP�������ȉ��̎�*/
	else if (this->hp <= 50)
	{
		/*�E����*/
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
		{
			/*������*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[2], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x + 3, y - 18, 1.0f, M_PI, head_Image[2], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
		{
			DrawRotaGraph(x + 3, y - 19, 1.0f, M_PI, head_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
		{
			DrawRotaGraph(x - 7, y - 19, 1.0f, M_PI, head_Image[2], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
		{
			DrawRotaGraph(x + 5, y - 17, 1.0f, M_PI, head_Image[2], TRUE);
		}

		/*������*/
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
		{
			/*������*/
			static int st = 0;
			switch (st)
			{
			case 0:
				if (playerCount % 200 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[3], TRUE);
				}
				else
				{
					st = 1;
				}
				break;
			case 1:
				if (playerCount % 50 != 0) //���t���[���̏���
				{
					DrawRotaGraph(x - 3, y - 18, 1.0f, 0, head_Image[3], TRUE);
				}
				else
				{
					st = 0;
				}
				break;
			}
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
		{
			DrawRotaGraph(x - 3, y - 19, 1.0f, 0, head_Image[3], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
		{
			DrawRotaGraph(x + 7, y - 19, 1.0f, 0, head_Image[3], TRUE);
		}
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
		{
			DrawRotaGraph(x - 5, y - 17, 1.0f, 0, head_Image[3], TRUE);
		}
	}

	///*********************
	//*                    *
	//*   ���̕`��E����   *
	//*                    *
	//*********************/

	/*�E����*/
	/*if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
	{
		DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	{
		DrawRotaGraph(x + 3, y - 19, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	{
		DrawRotaGraph(x - 7, y - 19, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	{
		DrawRotaGraph(x + 5, y - 17, 1.0f, M_PI - jan_angle, head_Image[0], TRUE);
	}*/
	/*if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false) //�W�����v�̎�
	{
		DrawRotaGraph(x + 3, y - 22, 1.0f, M_PI, head_Image[0], TRUE);
	}*/

	/*������*/
	/*if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
	{
		DrawRotaGraph(x - 3, y - 22, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	{
		DrawRotaGraph(x - 3, y - 19, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	{
		DrawRotaGraph(x + 7, y - 19, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}
	 if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	{
		DrawRotaGraph(x - 5, y - 17, 1.0f, M_PI - jan_angle, head_Image[1], TRUE);
	}*/
	/*if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == false) //�W�����v�̎�
	{
		DrawRotaGraph(x - 3, y - 22, 1.0f, 0, head_Image[1], TRUE);
	}*/
}

/*�ڂ̕`��E����*/
void Player::EyeDrawMove() const
{
	///*********************
	//*                    *
	//*   �ڂ̕`��̂�     *
	//*                    *
	//*********************/

	/*�E����*/
	if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
	{
		/*�u����*/
		static int st = 0;
		static int stk = 0;
		switch (st)
		{
		case 0:
			if (playerCount % 200 != 0) //���t���[���̏���
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 1;
			}
			break;
		case 1:
			if (playerCount % 50 != 0) //���t���[���̏���
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 0;
			}
			break;
		}
	}
	else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	{
		DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
		/*�u����*/
		//static int st = 0;
		//switch (st)
		//{
		//case 0:
		//	if (playerCount % 100 != 0) //10�t���[�����̏���
		//	{
		//		DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
		//	}
		//	else
		//	{
		//		st = 1;
		//	}
		//	break;
		//case 1:
		//	if (playerCount % 10 != 0) //10�t���[�����̏���
		//	{
		//		DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[1], TRUE);
		//	}
		//	else
		//	{
		//		st = 0;
		//	}
		//	break;
		//}
	}
	else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	{
		DrawRotaGraph(x - 3, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
	}
	else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	{
		DrawRotaGraph(x + 9, y - 23, 1.0f, M_PI, eye_ImageR[0], TRUE);
	}

	/*������*/
	if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
	{
		/*�u����*/
		static int st = 0;
		static int stk = 0;
		switch (st)
		{
		case 0:
			if (playerCount % 200 != 0) //���t���[���̏���
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 1;
			}
			break;
		case 1:
			if (playerCount % 50 != 0) //���t���[���̏���
			{
				switch (stk)
				{
				case 0:
					if (playerCount % 120 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[0], TRUE);
					}
					else
					{
						stk = 1;
					}
					break;
				case 1:
					if (playerCount % 10 != 0) //�ڃt���[���̏���
					{
						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[1], TRUE);
					}
					else
					{
						stk = 0;
					}
					break;
				}
			}
			else
			{
				st = 0;
			}
			break;
		}
	}
	else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	{
		DrawRotaGraph(x - 6, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	}
	else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	{
		DrawRotaGraph(x + 3, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	}
	else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	{
		DrawRotaGraph(x - 9, y - 23, 1.0f, 0, eye_ImageL[0], TRUE);
	}

	///*********************
	//*                    *
	//*       �u������     *
	//*                    *
	//*********************/

	/*static int st = 0;
	static int stk = 0;
	static int stky = 0;*/

	/*�E����*/
	//if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true)
	//{
	//	//static int st = 0;
	//	//static int stk = 0;
	//	if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 0)
	//	{
	//		/*�u����*/
	//		switch (st)
	//		{
	//		case 0:
	//			if (playerCount % 200 != 0) //���t���[���̏���
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x + 6, y - 28, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 1;
	//			}
	//			break;
	//		case 1:
	//			if (playerCount % 50 != 0) //���t���[���̏���
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x + 6, y - 24, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 0;
	//			}
	//			break;
	//		}
	//	}
	//	switch (stky)
	//	{
	//	case 0:
	//		if (playerCount2 % 120 != 0) //�ڃt���[���̏���
	//		{
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	//			{
	//				DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	//			{
	//				DrawRotaGraph(x - 3, y - 25, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	//			{
	//				DrawRotaGraph(x + 9, y - 23, 1.0f, M_PI, eye_ImageR[0], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 1;
	//		}
	//		break;
	//	case 1:
	//		if (playerCount2 % 10 != 0) //�ڃt���[���̏���
	//		{
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 1)
	//			{
	//				DrawRotaGraph(x + 6, y - 25, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 2)
	//			{
	//				DrawRotaGraph(x - 3, y - 25, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && player_Image == 3)
	//			{
	//				DrawRotaGraph(x + 9, y - 23, 1.0f, M_PI, eye_ImageR[1], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 0;
	//		}
	//		break;
	//	}
	//}
	///*������*/
	//if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true)
	//{
	//	//static int st = 0;
	//	//static int stk = 0;
	//	if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 5)
	//	{
	//		/*�u����*/
	//		static int st = 0;
	//		static int stk = 0;
	//		switch (st)
	//		{
	//		case 0:
	//			if (playerCount % 200 != 0) //���t���[���̏���
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x - 6, y - 28, 1.0f, 0, eye_ImageL[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 1;
	//			}
	//			break;
	//		case 1:
	//			if (playerCount % 50 != 0) //���t���[���̏���
	//			{
	//				switch (stk)
	//				{
	//				case 0:
	//					if (playerCount % 120 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[0], TRUE);
	//					}
	//					else
	//					{
	//						stk = 1;
	//					}
	//					break;
	//				case 1:
	//					if (playerCount % 10 != 0) //�ڃt���[���̏���
	//					{
	//						DrawRotaGraph(x - 6, y - 24, 1.0f, 0, eye_ImageL[1], TRUE);
	//					}
	//					else
	//					{
	//						stk = 0;
	//					}
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				st = 0;
	//			}
	//			break;
	//		}
	//	}
	//	switch (stky)
	//	{
	//	case 0:
	//		if (playerCount2 % 120 != 0) //�ڃt���[���̏���
	//		{
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	//			{
	//				DrawRotaGraph(x - 6, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	//			{
	//				DrawRotaGraph(x + 3, y - 25, 1.0f, 0, eye_ImageL[0], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	//			{
	//				DrawRotaGraph(x - 9, y - 23, 1.0f, 0, eye_ImageL[0], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 1;
	//		}
	//		break;
	//	case 1:
	//		if (playerCount2 % 10 != 0) //�ڃt���[���̏���
	//		{
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 6)
	//			{
	//				DrawRotaGraph(x - 6, y - 25, 1.0f, 0, eye_ImageL[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 7)
	//			{
	//				DrawRotaGraph(x + 3, y - 25, 1.0f, 0, eye_ImageL[1], TRUE);
	//			}
	//			if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && player_Image == 8)
	//			{
	//				DrawRotaGraph(x - 9, y - 23, 1.0f, 0, eye_ImageL[1], TRUE);
	//			}
	//		}
	//		else
	//		{
	//			stky = 0;
	//		}
	//		break;
	//	}
	//}
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

/*�̂̕`��E����*/
void Player::BodyDrawMove() const
{
	//���S����`��
	switch (select_JanType)
	{
	case Jan_Type::ROCK:
		DrawRotaGraphF(x, y, 1, 0, image[0][player_Image], TRUE);
		break;
	case Jan_Type::SCISSORS:
		DrawRotaGraphF(x, y, 1, 0, image[1][player_Image], TRUE);
		break;
	case Jan_Type::PAPER:
		DrawRotaGraphF(x, y, 1, 0, image[2][player_Image], TRUE);
		break;
	case Jan_Type::NONE:
		break;
	default:
		break;
	}
}

//�v���C���[��UI�`��
void Player::PlayerDrawUI(int hp) const
{
	float draw_x = x - 50;  //�`�悘
	float draw_y = y - 100; //�`�悙

	int bar_color = 0x00ff00;
	if (hp <= 30) 
	{
		bar_color = 0xff0000;

		static int flash_count;       //�_�ŉ�
		if (flash_count < 4)
		{
			static int frame_count;
			if (++frame_count < 10)
			{
				//�g
				DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
				DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
				//HP
				DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
			}
			else if (frame_count > 20)
			{
				frame_count = 0;
				flash_count++;
			}
		}
		else
		{
			//�g
			DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
			DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
			//HP
			DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
		}
	}
	else
	{
		//�g
		DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
		DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
		//HP
		DrawBoxAA(draw_x, draw_y, (draw_x + hp), draw_y + 10, bar_color, TRUE);
	}
}

//�`��
void Player::Draw() const
{
	//����񌂕`��
	Draw_Jangeki();

	//���S���ȊO
	if (player_state == PLAYER_STATE::ALIVE)
	{
		//�G�t�F�N�g
		if (obj_effectchange != nullptr)
		{
			obj_effectchange->Draw_Back();
		}
		else {};
		//�G�t�F�N�g
		if (obj_effect != nullptr)
		{
			obj_effect->Draw_Back();
		}
		else {};

		//�Ə���        �E�X�e�B�b�N�ɓ��͂����鎞
		if (KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X) == 0 &&
			KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y) == 0)
		{
			/*�r�̕`�悾��*/
			ArmDrawMove();
		}
		else
		{
			int vx = static_cast<int>(550 * cos(jan_angle));
			int vy = static_cast<int>(550 * sin(jan_angle));

			/*�^�������Ȑ��̏Ə���*/
			//DrawLineAA(x, y, x + vx, y - vy, 0xffff00, 3); 

			/*�r�̕`��E����*/
			ArmDrawMove();
		}
		//���S����`��
		BodyDrawMove();

		/*��*/
		HeadDrawMove();

		//��
		EyeDrawMove();

		//�G�t�F�N�g
		if (obj_effectchange != nullptr)
		{
			obj_effectchange->Draw_Front();
		}
		else {};
		//�G�t�F�N�g
		if (obj_effect != nullptr)
		{
			obj_effect->Draw_Front();
		}
	}
	else
	{
		//���S�摜
		DrawRotaGraphF(x, y, 1, 0, image_death, TRUE);
	}

	PlayerDrawUI(GetHP());

	//�e�X�g �I�������
	DrawStringToHandle(30, 150, "RB : ����", 0xffffff, ui_font);
	DrawStringToHandle(30, 180, "LB : �W�����v", 0xffffff, ui_font);

	//���O�\��
	for (int i = 0; i < 10; i++)
	{
		DrawFormatStringToHandle(x - 80, y - 80, 0x00ff00, name_font, "%10s", sortSave.getRankingData(i).name);
	}

	//�e�X�g 110
	int circle_x = 0;
	switch (select_JanType)
	{
	case Jan_Type::ROCK:
		circle_x = 2;
		break;
	case Jan_Type::SCISSORS:
		circle_x = 1;
		break;
	case Jan_Type::PAPER:
		circle_x = 0;
		break;
	default:
		circle_x = 0;
		break;
	}

	DrawGraph(40, 40,  image_setsumei, TRUE);
	DrawGraph(50 + (circle_x * 60), 50, image_set_circle, TRUE);
	DrawGraph(13, 10, image_set_LTRT, TRUE);
	DrawGraph(55, 100, image_set_GPT, TRUE);

	//�I���̉��o XYB
	if (KeyManager::OnPadPressed(PAD_INPUT_3))      //X
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
		DrawCircle(75, 120, 15, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (KeyManager::OnPadPressed(PAD_INPUT_4))  //Y
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
		DrawCircle(135, 120, 15, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (KeyManager::OnPadPressed(PAD_INPUT_B))  //B
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 120);
		DrawCircle(195, 120, 15, 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {}

	// LT RT
	if (KeyManager::GetValue_LT() > 30)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ADD, 30);
		DrawTriangleAA(33.f, 17.f, 33.f, 39.f, 23.f, 28.f, 0xffa500, TRUE);
		DrawBoxAA(33.f, 24.f, 60.f, 32.f, 0xffa500, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (KeyManager::GetValue_RT() > 30)
	{
		//SetDrawBlendMode(DX_BLENDMODE_ADD, 30);
		DrawTriangleAA(234.f, 17.f, 234.f, 39.f, 244.f, 28.f, 0xffa500, TRUE);
		DrawBoxAA(207.f, 24.f, 234.f, 32.f, 0xffa500, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	///*�e���|�[�g���̃A�j���[�V����*/
	//if (animflg == true)
	//{
	//	if(DrawGraph(x - 50, y - 50, img_Playeranim[animtimer / 2 % 15], TRUE));
	//}
}

/*�摜�̕ύX�擾*/
void  Player::PlayerSwitch()
{
	/*�v���C���[�̉摜�ύX*/
	switch (playerChange_Image)
	{

	/***********
	* ���E�ړ� *
	************/

	case 1: //�E�ړ�
	   /*                �E����            �ڒn                   �E�E������Ă�                      */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) /*|| x > old_x*/)
		{
			playerGetMove = 1;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 0;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}
		/*               ������            �ڒn                   �E�E������Ă�                     */
		else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_RIGHT) /*|| x > old_x*/)
		{
			playerGetMove = 6;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 5;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}

		/*�����摜�ύX*/
		//if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && x > old_x)
		//{
		//	playerGetMove = 1;      //�摜���擾
		//	playerCount++;          //�t���[���J�E���g�𑝂₷
		//	PlayerChangeMoveimg();  //�摜�ύX��
		//	pCount = 0;             //�����ĂȂ��Ƃ��p
		//	playerChange_Image = 0; //�����ĂȂ��Ƃ��p
		//	break;
		//}
		//else if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && x > old_x)
		//{
		//	playerGetMove = 6;      //�摜���擾
		//	playerCount++;          //�t���[���J�E���g�𑝂₷
		//	PlayerChangeMoveimg();  //�摜�ύX��
		//	pCount = 5;             //�����ĂȂ��Ƃ��p
		//	playerChange_Image = 0; //�����ĂȂ��Ƃ��p
		//	break;
		//}

		/*�W�����v�̎�*/
		/*         �E����         ��ڒn     */
		if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == false)
		{
			player_Image = 4;     //�摜���擾
			break;
		}

	case 2: //���ړ��̎�
	   /*               ������            �ڒn                   ���E������Ă�                     */
		if (dir == static_cast<int>(DIRECTION::LEFT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) /*|| x < old_x*/)
		{
			playerGetMove = 6;      //�摜���擾
			playerCount++;          //�t���[���J�E���g�𑝂₷
			PlayerChangeMoveimg();  //�摜�ύX��
			pCount = 5;             //�����ĂȂ��Ƃ��p
			playerChange_Image = 0; //�����ĂȂ��Ƃ��p
			break;
		}
		/*               �E����            �ڒn                   ���E������Ă�                     */
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && land_flg == true && KeyManager::OnPadPressed(PAD_INPUT_LEFT) /*|| x < old_x*/)
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
		if (dir == static_cast<int>(DIRECTION::RIGHT) /*&& jan_angle < (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_RIGHT)/* || x > old_x*/)
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
		else if (dir == static_cast<int>(DIRECTION::LEFT) && KeyManager::OnPadPressed(PAD_INPUT_RIGHT)/* || x > old_x*/)
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
		if (dir == static_cast<int>(DIRECTION::LEFT) /*&& jan_angle > (M_PI / 2)*/ && KeyManager::OnPadPressed(PAD_INPUT_LEFT)/* || x < old_x*/)
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
		else if (dir == static_cast<int>(DIRECTION::RIGHT) && KeyManager::OnPadPressed(PAD_INPUT_LEFT)/* || x > old_x*/)
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

			//LT,RT�Ŕ��˂��邶��񌂑�����I���i�Z�b�g�j����
	static int select_num;

	if (KeyManager::OnPadClicked_RT()) select_num++, animflg = true; //�A�j���[�V�����J�n;
	if (select_num > 2) select_num = 0;

	if (KeyManager::OnPadClicked_LT()) select_num--, animflg = true; //�A�j���[�V�����J�n;
	if (select_num < 0) select_num = 2;

	//�O��̑���
	Jan_Type old_type = select_JanType;

	// B,Y,X�@�{�^���Ŕ��˂��邶��񌂑�����I���i�Z�b�g�j����
	if (KeyManager::OnPadClicked(PAD_INPUT_B))         //B�{�^��
	{
		//  �O�[��I�� 
		select_JanType = Jan_Type::ROCK;
		select_num = 2;
		animflg = true; //�A�j���[�V�����J�n
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_4))    //Y�{�^��
	{
		//  �`���L��I�� 
		select_JanType = Jan_Type::SCISSORS;
		select_num = 1;
		animflg = true; //�A�j���[�V�����J�n
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_3))    //X�{�^��
	{
		//  �p�[��I�� 
		select_JanType = Jan_Type::PAPER;
		select_num = 0;
		animflg = true; //�A�j���[�V�����J�n
	}
	else
	{

	}
	switch (select_num)
	{
	case 0:
		select_JanType = Jan_Type::PAPER;

		break;

	case 1:
		select_JanType = Jan_Type::SCISSORS;

		break;

	case 2:
		select_JanType = Jan_Type::ROCK;

		break;

	default:
		break;
	}

	/*�A�j���[�V�����̏���*/
	if (animflg == true)
	{
		animtimer++;

		if (animtimer / 3 % 15 == 14)
		{

			if (anim_count == 0)
			{
				animtimer = 0;
				anim_count = 1;
			}
			else
			{
				animtimer = 0;
				animflg = false;
				anim_count = 0;
			}

		}
	}

	if (old_type != select_JanType)
	{
		//�G�t�F�N�g����
		if (obj_effectchange != nullptr)
		{
			delete obj_effectchange;
			obj_effectchange = nullptr;
		}
		if (obj_effectchange == nullptr)obj_effectchange = new Effect_ChangePlayer(select_JanType, x, y);
	}

	//select_JanType = static_cast<Jan_Type>(select_num);

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
	obj_jangeki[jan_count]->SetPlayerHoming();
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

//�v���C���[�����S���Ă��邩
bool Player::IsDeathPlayer() const
{
	if (player_state == PLAYER_STATE::DEATH_END)
	{
		return true;
	}
	return false;
}

