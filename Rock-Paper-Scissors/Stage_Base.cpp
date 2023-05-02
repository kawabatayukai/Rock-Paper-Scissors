#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"

#include<vector>

//�Փ˔���Ȃ�����   5�b
#define NOT_COLLISION_TIME  300

namespace _CONSTANTS_SB
{
	//�G�t�F�N�g�ő吶����
	const int EFFECT_MAX = 20;
	
	//���v���W
	const int CLOCK_X = 640;
	const int CLOCK_Y = 60;
}

Stage_Base::Stage_Base() : blackout_time(0)
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);

	//                           �T�C�Y ��              �O�g
	font = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//�G�t�F�N�g������
	obj_effect = new Effect_Jangeki * [_CONSTANTS_SB::EFFECT_MAX];
	for (int i = 0; i < _CONSTANTS_SB::EFFECT_MAX; i++) obj_effect[i] = nullptr;

	//�摜
	LoadDivGraph("images/Clock/color_circles.png", 3, 3, 1, 120, 120, image_circle);
	image_clock = LoadGraph("images/Clock/clockback_wood.png");
	image_clockhand = LoadGraph("images/Clock/clockhand_wood.png");
	image_clockchar = LoadGraph("images/Clock/clock_str.png");
}

Stage_Base::~Stage_Base()
{

}

//UI�`��
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	using namespace _CONSTANTS_SB;

	int color = 0x00ff00;    //HP�o�[�̐F

	//�������ԕ`��
	//DrawFormatStringToHandle(500, 20, 0x00ff00, font, "%d��%d�b", GameData::Get_Each_Time() / 3600, GameData::Get_Each_Time() / 60);
	DrawFormatStringToHandle(500, 20, 0x00ff00, font, "%d : %d", GameData::Get_Each_Time_Min(), GameData::Get_Each_Time_Sec(),0xffffff);

	//�X�R�A�\��
	DrawFormatString(20, 220, 0xffffff, "�X�R�A�F%d", GameData::Get_Score());

	//�X�R�A
	DrawFormatString(1050, 150, 0x00ff00, "Score : %d", GameData::Get_Score());

	// ------------------------------ ���v ------------------------------------
	//���݂̃p�[�Z���e�[�W(��`)
	double circle_rate = (100 * static_cast<double>(GameData::Get_Each_Time())) / static_cast<double>(GameData::Get_ConstTimeLimit());
	//�j�̊p�x
	double hand_angle = ((360 * circle_rate) / 100) * static_cast<double>(3.14 / 180);

	//�F���ς��
	int circle_index = 0;
	if (circle_rate <= 66 && circle_rate > 33) circle_index = 1;
	else if (circle_rate < 33) circle_index = 2;
	else {};

	
	DrawRotaGraph(CLOCK_X, CLOCK_Y, 1, 0, image_clock, TRUE);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 250);
	DrawCircleGauge(CLOCK_X, CLOCK_Y, circle_rate, image_circle[circle_index], 0.0, 0.85, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRotaGraph(CLOCK_X, CLOCK_Y, 1, 0, image_clockchar, TRUE);
	DrawRotaGraph(CLOCK_X, CLOCK_Y, 1, -hand_angle, image_clockhand, TRUE);
}

//�G�̏��UI�`��
void Stage_Base::DrawUI_ON_Enemy(const EnemyBase* enemy) const
{
	//�����擾
	Jan_Type type = enemy->GetType();
	int enemy_hp  = enemy->GetHP();
	float enemy_x = enemy->GetX();
	float enemy_y = enemy->GetY();
	float enemy_h = enemy->GetH();

	//HP�o�[�̐F
	int bar_color = 0xffffff;
	//�`�悷�邶��񌂑����̔z��ԍ�
	int index = 0;

	switch (type)
	{
	case Jan_Type::ROCK:

		index = 0;
		bar_color = 0xff0000;    //red
		break;

	case Jan_Type::SCISSORS:

		index = 1;
		bar_color = 0xffd400;    //yellow
		break;

	case Jan_Type::PAPER:

		index = 2;
		bar_color = 0x0000ff;    //blue
		break;

	default:
		break;
	}

	float draw_x = enemy_x - 50;  //�`�悘
	float draw_y = enemy_y - 100; //�`�悙

	//����
	if(type != Jan_Type::NONE)DrawRotaGraph(draw_x - 20, draw_y + 5, 0.3, 1, typeImage[index], TRUE);
	//�g
	DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
	DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
	//HP
	DrawBoxAA(draw_x, draw_y, (draw_x + enemy_hp), draw_y + 10, bar_color, TRUE);
}

//���E�ǂ̏����@�@STAGE_XX_FLOOR ��������
void Stage_Base::Init_Floor(const int floor_MAX)
{
	//���E�� * floor_MAX�@���̃��������m��
	obj_floor = new Floor * [floor_MAX];
	for (int i = 0; i < floor_MAX; i++) obj_floor[i] = nullptr;   //nullptr�őS�ď�����
}


//���E�ǂƂ̂����蔻��
void Stage_Base::HitCtrl_Floor(CharaBase* character, const int floor_MAX)
{
	for (int i = 0; i < floor_MAX; i++)
	{
		character->Hit_Floor(obj_floor[i]);
	}
}


//"�ڐG������񂯂�"����   player(�����P�Ԗځ@�̏��s���ʂ�Ԃ�)
Jan_Result Stage_Base::Get_JankenResult(Jan_Type player, Jan_Type enemy)
{
	// player�i�����P�Ԗځj��
	switch (player)
	{
	case Jan_Type::ROCK:         //�O�[�̎�

		if (enemy == Jan_Type::PAPER)    return Jan_Result::LOSE;    //enemy�i�����Q�Ԗځj���p�[�̎�
		if (enemy == Jan_Type::SCISSORS) return Jan_Result::WIN;     //enemy�i�����Q�Ԗځj���`���L�̎�
		if (enemy == Jan_Type::ROCK)     return Jan_Result::ONEMORE; //enemy�i�����Q�Ԗځj���O�[�̎�
		break;

	case Jan_Type::SCISSORS:     //�`���L�̎�

		if (enemy == Jan_Type::ROCK)     return Jan_Result::LOSE;    //enemy�i�����Q�Ԗځj���O�[�̎�
		if (enemy == Jan_Type::PAPER)    return Jan_Result::WIN;     //enemy�i�����Q�Ԗځj���p�[�̎�
		if (enemy == Jan_Type::SCISSORS) return Jan_Result::ONEMORE; //enemy�i�����Q�Ԗځj���`���L�̎�
		break;

	case Jan_Type::PAPER:        //�p�[�̎�

		if (enemy == Jan_Type::SCISSORS) return Jan_Result::LOSE;    //enemy�i�����Q�Ԗځj���`���L�̎�
		if (enemy == Jan_Type::ROCK)     return Jan_Result::WIN;     //enemy�i�����Q�Ԗځj���O�[�̎�
		if (enemy == Jan_Type::PAPER)    return Jan_Result::ONEMORE; //enemy�i�����Q�Ԗځj���p�[�̎�
		break;

	default:
		break;
	}

	//����ȊO�̓G���[
	return Jan_Result::_ERROR;
}



//�G�ƃv���C���[�̓����蔻�聨�ڐG����񂯂񏈗�    �G�ւ̃|�C���^�A"this" ��������
void Stage_Base::Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr, int my_StageNum)
{
	//����񂯂�J�n�O 
	if (j_state == Jan_State::BEFORE)
	{
		//�G�ƃv���C���[���ڐG
		if (enemy->Hit_Character(obj_player) == true && nhit_time == 0)
		{
			//�ڐG����!
			j_state = Jan_State::START;
			blackout_time = 0;

			//�G���o����������_���Ɍ��߂�@�@�@�i�����_����int�^�̒l(0�`2)�� Jan_Type�^�ɕϊ��j
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//����񂯂�I�u�W�F�N�g����
			obj_janken = new Janken(enemy_janken, my_StageNum);
		}

	}
	else if (j_state == Jan_State::START)
	{
		//�ڐG��������
		blackout_time++;

		//1�b�ł���񂯂��ʂ�
		if (blackout_time > 60) j_state = Jan_State::PROGRESS;
	}
	else if (j_state == Jan_State::PROGRESS)
	{
		//����񂯂�
		obj_janken->Update();

		// ���ʂ� _ERROR(����񂯂�)�łȂ��Ƃ��A����񂯂�I��
		if (obj_janken->GetResult() != Jan_Result::_ERROR)
		{
			j_state = Jan_State::AFTER;
		}
	}
	else if (j_state == Jan_State::AFTER)
	{
		//A�{�^���������ꂽ�Ƃ� 
		if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		{
			//�v���C���[�̍��W�������l��
			obj_player->SetX(640);

			//����񂯂�I��
			switch (obj_janken->GetResult())
			{

			case Jan_Result::LOSE:    //����

				//�I�[�o�[���C�h���ꂽAfterJanken_LOSE()���Ăяo��
				stage_ptr->AfterJanken_LOSE();

				//����񌂂�����������
				enemy->Init_Jangeki();

				delete obj_janken;
				//�����蔻��Ȃ����Ԃ��Z�b�g
				nhit_time = NOT_COLLISION_TIME;

				//�J�n�O�Ƀ��Z�b�g
				j_state = Jan_State::BEFORE;
				break;


			case Jan_Result::WIN:     //����

				//�I�[�o�[���C�h���ꂽAfterJanken_WIN()���Ăяo��
				stage_ptr->AfterJanken_WIN();

				//����񌂂�����������
				enemy->Init_Jangeki();

				delete obj_janken;
				//�����蔻��Ȃ����Ԃ��Z�b�g
				nhit_time = NOT_COLLISION_TIME;

				//�J�n�O�Ƀ��Z�b�g
				j_state = Jan_State::BEFORE;

				break;


			case Jan_Result::ONEMORE: //������

				//����񌂂�����������
				enemy->Init_Jangeki();

				obj_janken->OneMore_Init();

				//����񂯂�J�n
				j_state = Jan_State::PROGRESS;

				break;

			default:

				delete obj_janken;
				break;
			}



		}
	}
	else {}

	//�Փ˔���Ȃ�����
	if (--nhit_time < 0) nhit_time = 0;
}


//����񌂃q�b�g���G�t�F�N�g ����
void Stage_Base::Effect_Update_HitJangeki(const EnemyBase* enemy)
{
	//�G�̍��W
	float e_x = enemy->GetX();
	float e_y = enemy->GetY();

	//�v���C���[�̍��W
	float p_x = obj_player->GetX();
	float p_y = obj_player->GetY();

	//�G�t�F�N�g�𐶐�����z��̗v�f�ԍ�
	int effect_count;

	//�G�t�F�N�g
	for (effect_count = 0; effect_count < _CONSTANTS_SB::EFFECT_MAX; effect_count++)
	{
		//��Ȃ�I��
		if (obj_effect[effect_count] == nullptr) break;

		obj_effect[effect_count]->Update();

		//�폜
		if (obj_effect[effect_count]->Check_PlayEnd() == true)
		{
			delete obj_effect[effect_count];
			obj_effect[effect_count] = nullptr;    //������

			//�l�߂�
			for (int j = effect_count; j < (_CONSTANTS_SB::EFFECT_MAX - 1); j++)
			{
				//���̗v�f�� nullptr �Ȃ炻��ȏ�͏������Ȃ�
				if (obj_effect[j + 1] == nullptr) break;

				obj_effect[j] = obj_effect[j + 1];
				obj_effect[j + 1] = nullptr;
			}
			effect_count--;
		}
	}


	//--------------------  player����񌂂�enemy  -------------------------------------
	{
		//player�̂���񌂂��Ƃ��Ă���
		Jangeki_Base** p_jan = obj_player->GetJangeki();

		//player����񌂂�enemy�̓����蔻��
		for (int i = 0; i < JANGEKI_MAX; i++)
		{
			//��v�f�Ȃ�I��
			if (p_jan[i] == nullptr) break;

			//�����蔻��
			if (enemy->Hit_Jangeki(p_jan[i]) == true)
			{
				Jan_Type p_type = p_jan[i]->GetType();  //������������񌂂̑���

				//�s�������̂�
				switch (enemy->GetType())
				{
				case Jan_Type::ROCK:                           //�G�̑����@�O�[

					//�p�[�̂ݗL��
					if (p_type == Jan_Type::PAPER)
					{
						//�G�t�F�N�g����
						if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
						{
							obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y);
						}
					}
					break;

				case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

					//�O�[�̂ݗL��
					if (p_type == Jan_Type::ROCK)
					{
						//�G�t�F�N�g����
						if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
						{
							obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y);
						}
					}
					break;

				case Jan_Type::PAPER:                          //�G�̑����@�p�[

					//�`���L�̂ݗL��
					if (p_type == Jan_Type::ROCK)
					{
						//�G�t�F�N�g����
						if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
						{
							obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y);
						}
					}
					break;

				default:
					break;
				}
			}
		}
	}
	//----------------------------------------------------------------------------------

	//--------------------  enemy����񌂂�player  -------------------------------------
	{
		//enemy�̂���񌂂��Ƃ��Ă���
		Jangeki_Base** e_jan = enemy->GetJangeki();

		//enemy����񌂂�player�̓����蔻��
		for (int i = 0; i < JANGEKI_MAX; i++)
		{
			//��v�f�Ȃ�I��
			if (e_jan[i] == nullptr) break;

			//�����蔻��
			if (obj_player->Hit_Jangeki(e_jan[i]) == true)
			{
				//�G�t�F�N�g����
				if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
				{
					obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y);
				}
			}
		}
	}
	//----------------------------------------------------------------------------------
}

//����񌂃q�b�g���G�t�F�N�g �`��
void Stage_Base::Effect_Draw_HitJangeki() const
{
	//�G�t�F�N�g
	for (int i = 0; i < _CONSTANTS_SB::EFFECT_MAX; i++)
	{
		//��Ȃ�I��
		if (obj_effect[i] == nullptr) break;
		obj_effect[i]->Draw();
	}
}


//����񂯂�`��
void Stage_Base::Draw_Janken() const
{
	obj_janken->Draw();
}

//����񂯂�J�n����
void Stage_Base::Draw_JankenStart() const
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(blackout_time * 5));
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//DrawBox(0, 0, static_cast<int>(blackout_time), static_cast<int>(blackout_time), 0xffffff, TRUE);
}


//����񂯂�I����̋����i�v���C���[�����j
void Stage_Base::AfterJanken_WIN()
{
	obj_player->SetX(100);
}

//����񂯂�I����̋����i�v���C���[�����j
void Stage_Base::AfterJanken_LOSE()
{
	obj_player->SetX(100);
}


//����񂯂�̏�Ԏ擾
Jan_State Stage_Base::GetJanState() const
{
	////�������
	//if (j_state == Jan_State::START) return Jan_State::BEFORE;
	//else return j_state;

	return j_state;
}
