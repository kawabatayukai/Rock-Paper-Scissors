#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"

//�Փ˔���Ȃ�����   5�b
#define NOT_COLLISION_TIME  300

Stage_Base::Stage_Base() : blackout_time(0)
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);
	hpImage = LoadGraph("images/HitPoint.png");

	//                           �T�C�Y ��              �O�g
	font = CreateFontToHandle(NULL, 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//�G�t�F�N�g�p��
	obj_effect =  new Effect_Jangeki * [30];
	for (int i = 0; i < 30; i++) obj_effect[i] = nullptr;
}

Stage_Base::~Stage_Base()
{

}

//UI�`��
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	int color = 0x00ff00;    //HP�o�[�̐F

	switch (type)
	{
	case Jan_Type::ROCK:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[0], TRUE);
		color = 0xff0000;    //red
		break;
	case Jan_Type::SCISSORS:
					
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[1], TRUE);
		color = 0xffd400;    //yellow
		break;

	case Jan_Type::PAPER:

		DrawRotaGraph(810, 60, 0.5, 0, typeImage[2], TRUE);
		color = 0x0000ff;    //blue
		break;

	default:
		break;
	}


	DrawRotaGraph(1030, 60, 0.5, 0, hpImage, TRUE);			//�̗̓Q�[�W�g
	DrawBox(948, 45, 948 + static_cast<int>(hp * 2.54), 75, color, TRUE);	//�̗̓Q�[�W
	DrawFormatString(1120, 85, 0x00ff00, "�c��:%d", hp);	//�c��̗�(���l)

	//�������ԕ`��
	//DrawFormatStringToHandle(500, 20, 0x00ff00, font, "%d��%d�b", GameData::Get_Each_Time() / 3600, GameData::Get_Each_Time() / 60);
	DrawFormatStringToHandle(500, 20, 0x00ff00, font, "%d : %d", GameData::Get_Each_Time_Min(), GameData::Get_Each_Time_Sec(),0xffffff);

	//�X�R�A�\��
	DrawFormatString(20, 220, 0xffffff, "�X�R�A�F%d", GameData::Get_Score());

	//�X�R�A
	DrawFormatString(1050, 150, 0x00ff00, "Score : %d", GameData::Get_Score());

	
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
			//����񂯂�J�n
			//j_state = Jan_State::PROGRESS;

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

				//delete obj_janken;
				obj_janken->OneMore_Init();

				//����񂯂�J�n
				j_state = Jan_State::PROGRESS;

				//����񂯂�I�u�W�F�N�g����
				//obj_janken = new Janken(again_type);
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

//�G�t�F�N�g�Đ��i�G�t�F�N�g�Đ�����X�C�b�`�j
void Stage_Base::Play_Effect(float play_x, float play_y,unsigned int effect_type)
{
	int e_jancount;

	//��v�f�̐擪��T��(���S��)
	for (e_jancount = 0; e_jancount < 30; e_jancount++)
	{
		if (obj_effect[e_jancount] == nullptr) break;  //��
	}

	//�G�t�F�N�g�𐶐�
	if (e_jancount <= 30 && obj_effect[e_jancount] == nullptr)
	{
		obj_effect[e_jancount] = new Effect_Jangeki(play_x, play_y,effect_type);
	}
}

//�G�t�F�N�g�𓮍삳����
void Stage_Base::Update_Effect()
{
	int effect_count;

	//�G�t�F�N�g����
	{
		for (effect_count = 0; effect_count < 30; effect_count++)
		{
			//��̏ꍇ������
			if (obj_effect[effect_count] == nullptr) break;

			obj_effect[effect_count]->Update();

			//��ʊO�ō폜����
			if (obj_effect[effect_count]->Check_PlayEnd() == true)
			{
				delete obj_effect[effect_count];     //�폜
				obj_effect[effect_count] = nullptr;  //������

				//�l�߂�
				for (int i = effect_count; i < (30 - 1); i++)
				{
					//��̏ꍇ������
					if (obj_effect[effect_count] == nullptr) break;

					obj_effect[effect_count] = obj_effect[effect_count + 1];
					obj_effect[effect_count + 1] = nullptr;
				}
			}
		}
	}


	////�v���C���[�̂���񌂂��擾����
	//Jangeki_Base** p_jangeki;
	//if (obj_player != nullptr) p_jangeki = obj_player->GetJangeki();
	//else return;
	//
	////����񌂔z��̒�����G�t�F�N�g�𔭓����ׂ�����񌂂�T��
	//for (int i = 0; i < JANGEKI_MAX; i++)
	//{
	//	//��Ȃ甲����
	//	if (p_jangeki[i] == nullptr) break;

	//	//�G�t�F�N�g�𔭐����ׂ������
	//	if (p_jangeki[i]->GetEffectType() != Jan_Result::_ERROR)
	//	{
	//		int e_jancount;
	//		//��v�f�̐擪��T��(���S��)
	//		for (e_jancount = 0; e_jancount < 30; e_jancount++)
	//		{
	//			if (obj_effect[e_jancount] == nullptr) break;  //��
	//		}

	//		//�G�t�F�N�g�𐶐�
	//		if (e_jancount <= 30 && obj_effect[e_jancount] == nullptr)
	//		{
	//			obj_effect[e_jancount] = new Effect_Jangeki(p_jangeki[i]->GetX(), p_jangeki[i]->GetY());
	//		}
	//	}
	//}
}

//�G�t�F�N�g�`��
void Stage_Base::Draw_Effect() const
{
	for (int effect_count = 0; effect_count < 30; effect_count++)
	{
		//��̏ꍇ������
		if (obj_effect[effect_count] == nullptr) break;

		obj_effect[effect_count]->Draw();
	}
}