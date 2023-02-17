#include "Stage_Base.h"

Stage_Base::Stage_Base()
{

}

Stage_Base::~Stage_Base()
{

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