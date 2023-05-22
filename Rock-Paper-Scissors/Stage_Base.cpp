#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"
#include"MobEnemy_05.h"
#include<iostream>
#include<vector>


//�Փ˔���Ȃ�����   5�b
#define NOT_COLLISION_TIME  300


int Stage_Base::font = 0;         //����(WIN or LOSE or ONEMORE) �p�t�H���g
int Stage_Base::font_score = 0;   //Score�`��p�t�H���g
int Stage_Base::name_font = 0;

namespace _CONSTANTS_SB
{
	//�G�t�F�N�g�ő吶����
	const int EFFECT_MAX = 20;
	//SE Max
	const int SE_MAX = 15;

	//���v���W
	const int CLOCK_X = 640;
	const int CLOCK_Y = 60;

	//�G�̖��O
	const std::vector<std::string> Enemy_Name =
	{
		"NIWATORI",       //1
		"KAERU",        //2
		"ZAKU",           //3
		"RED EYE",       //4
		"TAMAGO",         //5
		"JAN NINJA",      //6
		"JHO",            //7
		"TWIN AVATAR",     //8
		"SHADOW",        //9
		"Y�EY"            //10
	};
}

Stage_Base::Stage_Base() : blackout_time(0), stage_number(0), Prev_EnemyType(Jan_Type::NONE), obj_effectEnemy(nullptr), obj_death(nullptr)
,bf_result(Jan_Result::_ERROR)
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);

	if (font == 0)
		font = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	if (font_score == 0)
		font_score = CreateFontToHandle("���C���I", 30, 5, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	//�t�H���g���쐬
	if (name_font == 0)
		name_font = CreateFontToHandle("���C���I", 20, 4, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//�G�t�F�N�g������
	obj_effect = new Effect_Jangeki * [_CONSTANTS_SB::EFFECT_MAX];
	for (int i = 0; i < _CONSTANTS_SB::EFFECT_MAX; i++) obj_effect[i] = nullptr;

	//�摜
	LoadDivGraph("images/Clock/color_circles.png", 3, 3, 1, 120, 120, image_circle);
	image_clock = LoadGraph("images/Clock/clockback_wood.png");
	image_clockhand = LoadGraph("images/Clock/clockhand_wood.png");
	image_clockchar = LoadGraph("images/Clock/clock_str.png");

	//SE
	obj_sejan = new Sound_Jangeki * [_CONSTANTS_SB::SE_MAX];
	for (int i = 0; i < _CONSTANTS_SB::SE_MAX; i++) obj_sejan[i] = nullptr;

	//SE Player
	Sound_Player::LoadPlayerSound();

	//SE Janken
	se_Janken = nullptr;
}

Stage_Base::~Stage_Base()
{

}

//UI�`��
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	using namespace _CONSTANTS_SB;

	//�������ԕ`��
	//�X�R�A
	DrawFormatStringToHandle(950, 80, 0xffffff, font_score, "Score : %d", GameData::Get_Score(), 0x000000);

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
void Stage_Base::DrawUI_ON_Enemy(const EnemyBase* enemy, const int& notDraw) const
{
	//�����擾
	Jan_Type type = enemy->GetType();
	int enemy_hp = enemy->GetHP();
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

	case Jan_Type::NONE:

		bar_color = 0x8B52A1;    //purple
		break;

	default:
		break;
	}

	float draw_x = enemy_x - 50;  //�`�悘
	float draw_y = enemy_y - 100; //�`�悙

	//����
	if (type != Jan_Type::NONE)DrawRotaGraphF(draw_x - 20, draw_y + 5, 0.3, 1, typeImage[index], TRUE);
	//�g
	DrawBoxAA(draw_x - 3, draw_y - 3, draw_x + 103, draw_y + 13, 0xffffff, TRUE);
	DrawBoxAA(draw_x, draw_y, (draw_x + 100), draw_y + 10, 0x000000, TRUE);
	//HP
	DrawBoxAA(draw_x, draw_y, (draw_x + enemy_hp), draw_y + 10, bar_color, TRUE);

	using namespace _CONSTANTS_SB;

	//���O
	if (notDraw == 0)
	{
		std::string name = Enemy_Name[stage_number > 0 ? stage_number - 1 : 0];
		int str_w = GetDrawStringWidthToHandle(name.c_str(), name.length(), name_font);
		DrawStringToHandle((static_cast<int>(enemy->GetX()) - (str_w / 2)), static_cast<int>(enemy->GetY()) - 80, name.c_str(), 0x00ff00, name_font);
	}
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
void Stage_Base::Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr, int my_StageNum, bool invalidate)
{
	stage_number = my_StageNum;

	//����񂯂�J�n�O 
	if (j_state == Jan_State::BEFORE)
	{
		//�G�ƃv���C���[���ڐG
		if (enemy->Hit_Character(obj_player) == true && nhit_time == 0 && invalidate == false)
		{
			//�ڐG����!
			j_state = Jan_State::START;
			blackout_time = 0;

			//�G���o����������_���Ɍ��߂�@�@�@�i�����_����int�^�̒l(0�`2)�� Jan_Type�^�ɕϊ��j
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//����񂯂�I�u�W�F�N�g����
			obj_janken = new Janken(enemy_janken, my_StageNum);

			//SE������
			se_Janken = nullptr;
			se_count = 0;
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
		obj_janken->Stars_Update();
		//���ʂ��ꎞ�i�[
		Jan_Result result = obj_janken->GetResult();
		
		// ���ʂ� _ERROR(����񂯂�)�łȂ��Ƃ��A����񂯂�I��
		if (result != Jan_Result::_ERROR) j_state = Jan_State::AFTER;
		
	}
	else if (j_state == Jan_State::AFTER)
	{
		obj_janken->Stars_Update();

		if (se_Janken == nullptr && se_count == 0)
		{
			Jan_Result result = obj_janken->GetResult();
			if (result == Jan_Result::WIN)
				se_Janken = new Sound_Janken(SE_JANKEN::JANKEN_WIN);
			else if (result == Jan_Result::LOSE)
				se_Janken = new Sound_Janken(SE_JANKEN::JANKEN_LOSE);
			else if (result == Jan_Result::ONEMORE)
				se_Janken = new Sound_Janken(SE_JANKEN::JANKEN_AIKO);
			else {}
			se_count++;
		}

		//A�{�^���������ꂽ�Ƃ� 
		if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		{
			//�v���C���[�̍��W�������l��
			obj_player->SetX(640);

			//����񂯂�I��
			switch (obj_janken->GetResult())
			{

			case Jan_Result::LOSE:    //����

				

				/*��Փx���������[�h�Ȃ�*/
				if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
				{
					obj_player->ReceiveDamage(100); //����
				}
				else /*���ʂ̃��[�h*/
				{
					//�I�[�o�[���C�h���ꂽAfterJanken_LOSE()���Ăяo��
					stage_ptr->AfterJanken_LOSE();
				}

				//END���o
				blackout_time = 0;
				j_state = Jan_State::END;

				break;


			case Jan_Result::WIN:     //����

				GameData::Add_Score(500);

				/*��Փx���������[�h�Ȃ�*/
				if (GameData::Get_DIFFICULTY() == GAME_DIFFICULTY::HARD)
				{
					enemy->ReceiveDamage(100);
					isHard_Win = true;
				}
				else /*���ʂ̃��[�h*/
				{
					//�I�[�o�[���C�h���ꂽAfterJanken_WIN()���Ăяo��
					stage_ptr->AfterJanken_WIN();
				}

				//END���o
				blackout_time = 0;  
				j_state = Jan_State::END;

				break;


			case Jan_Result::ONEMORE: //������
			{
				

				//����񌂂�����������
				enemy->Init_Jangeki();

				bf_result = Jan_Result::ONEMORE;
				delete obj_janken;

				//�G���o����������_���Ɍ��߂�@�@�@�i�����_����int�^�̒l(0�`2)�� Jan_Type�^�ɕϊ��j
				Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

				//����񂯂�I�u�W�F�N�g����
				obj_janken = new Janken(enemy_janken, my_StageNum);

				//����񂯂�J�n
				j_state = Jan_State::PROGRESS;

				break;
			}
			default:
				break;
			}



		}
	}
	else if (j_state == Jan_State::END)
    {
		//����񌂂�����������
		enemy->Init_Jangeki();
		//�����蔻��Ȃ����Ԃ��Z�b�g
		nhit_time = NOT_COLLISION_TIME;

		//�J�n�O�Ƀ��Z�b�g
		if(++blackout_time > 60) 
		{
			j_state = Jan_State::BEFORE;
			delete obj_janken;
		}
	}
	else {}

	//SE�Đ�
	if (se_Janken != nullptr)
	{
		se_Janken->Play();
		if (se_Janken->CheckPlayEnd() == true)
		{
			delete se_Janken;
			se_Janken = nullptr;
		}
	}

	//�Փ˔���Ȃ�����
	if (--nhit_time < 0) nhit_time = 0;

	//Enemy���Ď�
	if (my_StageNum == 9)
	{
		if (stage09_isclear == true && obj_death == nullptr || enemy->GetHP() <= 0 && obj_death == nullptr)
		{
			enemy->Init_Jangeki();
			//���S���o�p�I�u�W�F�N�g
			obj_death = new Enemy_Death(enemy->GetX(), enemy->GetY(), my_StageNum);

			enemy->SetX(-9999, true);
			enemy->SetY(-9999, true);
		}
	}
	else if (my_StageNum == 10)
	{
	}
	else
	{
		if (enemy->GetHP() <= 0 && obj_death == nullptr)
		{
			enemy->Init_Jangeki();
			//���S���o�p�I�u�W�F�N�g
			obj_death = new Enemy_Death(enemy->GetX(), enemy->GetY(), my_StageNum, enemy->GetType());

			enemy->SetX(-9999, true);
			enemy->SetY(-9999, true);
		}
	}


	Update_DeathEnemy();
};


//����񌂃q�b�g���G�t�F�N�g ����
void Stage_Base::Effect_Update_HitJangeki(const EnemyBase* enemy, const Jangeki_Reflection* ref)
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

		if (obj_effect[effect_count]->GetCharacterType() == _CHAR_TYPE::ENEMY)
			obj_effect[effect_count]->SetCharacterLocation(obj_player->GetX(), obj_player->GetY());
		else if (obj_effect[effect_count]->GetCharacterType() == _CHAR_TYPE::PLAYER)
			obj_effect[effect_count]->SetCharacterLocation(enemy->GetX(), enemy->GetY());
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

	//SE�𐶐�����z��̗v�f�ԍ�
	int se_count;
	for (se_count = 0; se_count < _CONSTANTS_SB::SE_MAX; se_count++)
	{
		if (obj_sejan[se_count] == nullptr) break;
		obj_sejan[se_count]->Play();

		//�폜
		if (obj_sejan[se_count]->CheckPlayEnd() == true)
		{
			delete obj_sejan[se_count];
			obj_sejan[se_count] = nullptr;

			//�l�߂�
			for (int j = 0; j < (_CONSTANTS_SB::SE_MAX - 1); j++)
			{
				if (obj_sejan[j + 1] == nullptr) break;
				obj_sejan[j] = obj_sejan[j + 1];
				obj_sejan[j + 1] = nullptr;
			}
			se_count--;
		}

	}

	//player�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** p_jan = obj_player->GetJangeki();
	//enemy�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** e_jan = enemy->GetJangeki();

	//--------------------  player����񌂂�enemy  -------------------------------------

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
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, Jan_Type::PAPER, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
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
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, Jan_Type::ROCK, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂ݗL��
				if (p_type == Jan_Type::SCISSORS)
				{
					//�G�t�F�N�g����
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, Jan_Type::SCISSORS, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			case Jan_Type::NONE:                            //�����Ȃ�

				//���˂���񌂂ɓ��Ă邱�ƂŐ��������z�[�~���O����񌂂̂ݗL��
				if (p_jan[i]->IsGetPlayerHoming() == true)
				{
					//�G�t�F�N�g����
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(e_x, e_y, p_type, _CHAR_TYPE::PLAYER);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
				break;

			default:
				break;
			}
		}
	}

	//----------------------------------------------------------------------------------

	//--------------------  enemy����񌂂�player  -------------------------------------
	{
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
					obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y, e_jan[i]->GetType(), _CHAR_TYPE::ENEMY);
					//effect_count++;

					//SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
					//se_count++;
				}
			}
		}

		//����
		if (ref != nullptr)
		{
			Jangeki_Base** r_jan = ref->GetJangeki();

			for (int r = 0; r < JANGEKI_MAX; r++)
			{
				//��v�f�Ȃ�I��
				if (r_jan[r] == nullptr) break;

				//�����蔻��
				if (obj_player->Hit_Jangeki(r_jan[r]) == true)
				{
					//�G�t�F�N�g����
					if (obj_effect[effect_count] == nullptr && effect_count < _CONSTANTS_SB::EFFECT_MAX)
					{
						obj_effect[effect_count] = new Effect_Jangeki(p_x, p_y, r_jan[r]->GetType(), _CHAR_TYPE::ENEMY);
						//effect_count++;

						//SE
						obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::HIT_JAN);
						//se_count++;
					}
				}
			}
		}
	}
	//----------------------------------------------------------------------------------

	//-------------------  enemy����񌂂�player�����  ------------------------------

	for (int p = 0; p < JANGEKI_MAX; p++)
	{
		if (p_jan[p] == nullptr) break;                  //�Ȃ���Δ�����

		//enemy
		for (int e = 0; e < JANGEKI_MAX; e++)
		{
			if (e_jan[e] == nullptr) break;              //�Ȃ���Δ�����

			if (p_jan[p]->Hit_Jangeki(e_jan[e]) == true) //������
			{
				int result = p_jan[p]->CheckAdvantage(e_jan[e]);

				//�������̏ꍇ
				if (result == 2)
				{
					//����񌂊Ԃ̋���
					float dx = e_jan[e]->GetX() - p_jan[p]->GetX();
					float dy = e_jan[e]->GetY() - p_jan[p]->GetY();

					float jan_x = p_jan[p]->GetX() + (dx / 2);
					float jan_y = p_jan[p]->GetY() + (dy / 2);

					obj_effect[effect_count] = new Effect_Jangeki(jan_x, jan_y, e_jan[e]->GetType(), _CHAR_TYPE::NOT_CHARA);
					effect_count++;

					//SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ONEMORE);
					//se_count++;
					GameData::Add_PierceCount(1); //�ђʉ񐔉��Z
					GameData::Add_Score(100 / 2); //�X�R�A���Z
				}
				else if (result == 1)   //����
				{
					// SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::PLAYER_WIN);
					//se_count++;
					GameData::Add_PierceCount(2); //�ђʉ񐔉��Z
					GameData::Add_Score(100);     //�X�R�A���Z
				}
				else if (result == 0)   //����
				{
					// SE
					obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ENEMY_WIN);
					//se_count++;
				}
				else {};
			}

			//ref����
			if (ref != nullptr)
			{
				Jangeki_Base** r_jan = ref->GetJangeki();
				for (int r = 0; r < JANGEKI_MAX; r++)
				{
					if (r_jan[r] == nullptr) break;              //������
					if (p_jan[p]->Hit_Jangeki(r_jan[r]) == true) //������
					{
						int result = p_jan[p]->CheckAdvantage(r_jan[r]);

						//�������̏ꍇ
						if (result == 2)
						{
							//����񌂊Ԃ̋���
							float dx = r_jan[r]->GetX() - p_jan[p]->GetX();
							float dy = r_jan[r]->GetY() - p_jan[p]->GetY();

							float jan_x = p_jan[p]->GetX() + (dx / 2);
							float jan_y = p_jan[p]->GetY() + (dy / 2);

							obj_effect[effect_count] = new Effect_Jangeki(jan_x, jan_y, r_jan[r]->GetType(), _CHAR_TYPE::NOT_CHARA);
							effect_count++;

							//SE
							obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ONEMORE);
							//se_count++;
							GameData::Add_PierceCount(1); //�ђʉ񐔉��Z
							GameData::Add_Score(100 / 2); //�X�R�A���Z
						}
						else if (result == 1)   //����
						{
							// SE
							obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::PLAYER_WIN);
							//se_count++;
							GameData::Add_PierceCount(2); //�ђʉ񐔉��Z
							GameData::Add_Score(100);     //�X�R�A���Z
						}
						else if (result == 0)   //����
						{
							// SE
							obj_sejan[se_count] = new Sound_Jangeki(SE_JAN::ENEMY_WIN);
							//se_count++;
						}
						else {};
					}
				}
			}
		}
	}

	//----------------------------------------------------------------------------------


	//----------------------------------�@�����ω��@------------------------------------
		//�O��̑����ƈ���Ă���΃G�t�F�N�g����
	if (enemy->GetType() != Prev_EnemyType && Prev_EnemyType != Jan_Type::NONE)
	{
		if (obj_effectEnemy == nullptr)
		{
			obj_effectEnemy = new Effect_Enemy(enemy->GetX(), enemy->GetY(), enemy->GetType());
		}
	}
	//�G�̑����ω�
	Prev_EnemyType = enemy->GetType();

	if (obj_effectEnemy != nullptr)
	{
		obj_effectEnemy->Update();
		obj_effectEnemy->SetEnemyLocation(enemy->GetX(), enemy->GetY());
		if (obj_effectEnemy->IsEffectFinished() == true)
		{
			delete obj_effectEnemy;
			obj_effectEnemy = nullptr;
		}
	}
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

	if (obj_effectEnemy != nullptr) obj_effectEnemy->Draw();
	Draw_DeathEnemy();
}

//���S������
void Stage_Base::Update_DeathEnemy()
{
	if (obj_death != nullptr)
	{
		obj_death->Update();
	}
}

//���S���`��
void Stage_Base::Draw_DeathEnemy() const
{
	if (obj_death != nullptr)
	{
		obj_death->Draw();
	}
}

//���S���o�I���`�F�b�N
bool Stage_Base::IsEnd_DeathEnemy()
{
	if (obj_death != nullptr)
	{
		if (obj_death->IsDeathEnd() == true)
		{
			return true;
			delete obj_death;

			GameData::Add_Score(1000);
		}
	}
	return false;
}

void Stage_Base::GetStage09IsClear(bool isclear)
{
	stage09_isclear = isclear;
}

//����񂯂�`��
void Stage_Base::Draw_Janken() const
{
	obj_janken->Draw();
}

//����񂯂�J�n����
void Stage_Base::Draw_JankenStart() const
{
	if (j_state == Jan_State::END)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (static_cast<int>(blackout_time * 5)));
		obj_janken->SetAlphaValue(255 - (static_cast<int>(blackout_time * 5)));
		if (blackout_time < 60) obj_janken->Draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		for (int i = 0; i < 12; i++)
		{
			DrawBox(0, i * 60, (1280 - (blackout_time * 21)), (i * 60) + 30, 0x000000, TRUE);

			DrawBox(1280, (i * 60) + 30, blackout_time * 21, (i * 60) + 60, 0x000000, TRUE);
		}
	}
	else
	{
		//�|�P�����o�g����
		for (int i = 0; i < 12; i++)
		{
			DrawBox(0, i * 60, blackout_time * 21, (i * 60) + 30, 0x000000, TRUE);

			DrawBox(1280, (i * 60) + 30, (1280 - (blackout_time * 21)), (i * 60) + 60, 0x000000, TRUE);
		}
	}
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

	if (j_state == Jan_State::END) return Jan_State::START;

	return j_state;
}
