#include "Stage_Base.h"
#include"KeyManager.h"
#include"DxLib.h"


//�Փ˔���Ȃ�����   5�b
#define NOT_COLLISION_TIME  300

Stage_Base::Stage_Base()
{
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, typeImage);
	hpImage = LoadGraph("images/HitPoint.png");
}

Stage_Base::~Stage_Base()
{

}

//UI�`��
void Stage_Base::DrawUI(Jan_Type type, int hp) const
{
	switch (type)
	{
	case Jan_Type::ROCK:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[0], TRUE);
		break;
	case Jan_Type::SCISSORS:
					
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[1], TRUE);
		break;
	case Jan_Type::PAPER:
		DrawRotaGraph(810, 60, 0.5, 0, typeImage[2], TRUE);
		break;
	default:
		break;
	}

	DrawRotaGraph(1030, 60, 0.5, 0, hpImage, TRUE);			//�̗̓Q�[�W�g
	DrawBox(948, 45, 948 + static_cast<int>(hp * 2.54), 75, 0x00ff00, TRUE);	//�̗̓Q�[�W
	DrawFormatString(1120, 85, 0x00ff00, "�c��:%d", hp);	//�c��̗�(���l)

	/*if (hp > 0) DrawFormatString(1000, 50, 0xffffff, "HP : %d", hp);
	else DrawString(1100, 50, "death!", 0xffffff);*/
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
			j_state = Jan_State::PROGRESS;

			//�G���o����������_���Ɍ��߂�@�@�@�i�����_����int�^�̒l(0�`2)�� Jan_Type�^�ɕϊ��j
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//����񂯂�I�u�W�F�N�g����
			obj_janken = new Janken(enemy_janken, my_StageNum);
		}

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

				delete obj_janken;

				//����񂯂�J�n
				j_state = Jan_State::PROGRESS;

				//����񂯂�I�u�W�F�N�g����
				obj_janken = new Janken(static_cast<Jan_Type> (GetRand(2)));
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