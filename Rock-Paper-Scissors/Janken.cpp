#include"DxLib.h"
#include"KeyManager.h"
#include"Janken.h"

//�R���X�g���N�^�@�@�@�@�@�@�@�@�@�@enemy�̏o���肪���܂�
Janken::Janken(Jan_Type enemy_jan) : enemy_jan(enemy_jan)
{
	//�K���ɏ�����
	player_jan = Jan_Type::ROCK;
	result = Jan_Result::_ERROR;

	//�摜�ǂݍ���
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image);

	SetFontSize(50);
}

//�f�X�g���N�^
Janken::~Janken()
{

	SetFontSize(20);
}

//�X�V
void Janken::Update()
{
	//B,Y,X���������܂łȂɂ����Ȃ� �@�����ꂽ�u��if���̒�
	if (Check_AnyButton() == true)
	{
		// ����񂯂�̌��ʂ��擾
		result = Get_JankenResult();
	}
	else
	{
		return;   //�������Ȃ�
	}
}

//�`��
void Janken::Draw() const
{
	//�v���C���[
	DrawCircle(120, 200, 200, 0xffffff, TRUE);
	DrawString(120, 200, "player", 0x000000);

	//�G
	DrawCircle(1160, 200, 200, 0xffff00, TRUE);
	DrawString(1160, 200, "enemy", 0x000000);

	//�ǂ̃{�^����������Ă��Ȃ��Ƃ�
	if (button_B == false && button_Y == false && button_X == false)
	{
		DrawString(280, 400, "���� �� �� ��....", 0xffffff);
	}
	else
	{
		DrawString(280, 400, "�� ��", 0xffffff);

		//�v���C���[�̎�
		DrawRotaGraph(250, 580, 1.8, 1, image[static_cast<int>(player_jan)], TRUE);

		//�G�̎�
		DrawRotaGraph(1030, 580, 1.8, 1, image[static_cast<int>(enemy_jan)], TRUE);


		//����񂯂�̌��ʁi�v���C���[�ڐ��j
		switch (result)
		{
		case Jan_Result::LOSE:

			DrawString(350, 300, "������", 0xffffff);
			break;

		case Jan_Result::WIN:

			DrawString(350, 300, "������", 0xffffff);
			break;

		case Jan_Result::ONEMORE:

			DrawString(350, 300, "������", 0xffffff);
			break;

		default:
			break;
		}

		DrawString(300, 600, "A�{�^���������Ă�������", 0xffffff);
	}

	
}


//B�i�O�[�j,Y�i�`���L�j,X�i�p�[�j�̂����ꂩ�������ꂽ�u�ԁAtrue��Ԃ�
bool Janken::Check_AnyButton()
{
	//�ǂ̃{�^����������Ă��Ȃ��Ƃ�
	if( button_B == false && button_Y == false && button_X == false )
	{
		//�ǂꂩ����������,3�̂������ true ������
		button_B = KeyManager::OnPadClicked(PAD_INPUT_B);  //B�{�^���̓���
		button_Y = KeyManager::OnPadClicked(PAD_INPUT_4);  //Y�{�^�������
		button_X = KeyManager::OnPadClicked(PAD_INPUT_3);  //X�{�^�������
	}
	else
	{
		//player�̏o���肪���܂�
		if (button_B == true) player_jan = Jan_Type::ROCK;      //B�{�^���̎��̓O�[
		if (button_Y == true) player_jan = Jan_Type::SCISSORS;  //Y�{�^���̎��̓`���L
		if (button_X == true) player_jan = Jan_Type::PAPER;     //X�{�^���̎��̓p�[

		//�ǂꂩ�������ꂽ��true
		return true;
	}

	//�������܂�false
	return false;
}



//"�ڐG������񂯂�"����
//   Check_AnyButton() �ŉ����ꂽ�{�^���� enemy�i�����j�̏��s���ʂ�Ԃ� (�����ꂽ�{�^���ڐ�)
Jan_Result Janken::Get_JankenResult()
{
	// button_type�i�����ꂽ�{�^���j��
	switch ( player_jan )
	{
	case Jan_Type::ROCK:         //�O�[�̎�

		if (enemy_jan == Jan_Type::PAPER)    return Jan_Result::LOSE;    //enemy�i�����Q�Ԗځj���p�[�̎�
		if (enemy_jan == Jan_Type::SCISSORS) return Jan_Result::WIN;     //enemy�i�����Q�Ԗځj���`���L�̎�
		if (enemy_jan == Jan_Type::ROCK)     return Jan_Result::ONEMORE; //enemy�i�����Q�Ԗځj���O�[�̎�
		break;

	case Jan_Type::SCISSORS:     //�`���L�̎�

		if (enemy_jan == Jan_Type::ROCK)     return Jan_Result::LOSE;    //enemy�i�����Q�Ԗځj���O�[�̎�
		if (enemy_jan == Jan_Type::PAPER)    return Jan_Result::WIN;     //enemy�i�����Q�Ԗځj���p�[�̎�
		if (enemy_jan == Jan_Type::SCISSORS) return Jan_Result::ONEMORE; //enemy�i�����Q�Ԗځj���`���L�̎�
		break;

	case Jan_Type::PAPER:        //�p�[�̎�

		if (enemy_jan == Jan_Type::SCISSORS) return Jan_Result::LOSE;    //enemy�i�����Q�Ԗځj���`���L�̎�
		if (enemy_jan == Jan_Type::ROCK)     return Jan_Result::WIN;     //enemy�i�����Q�Ԗځj���O�[�̎�
		if (enemy_jan == Jan_Type::PAPER)    return Jan_Result::ONEMORE; //enemy�i�����Q�Ԗځj���p�[�̎�
		break;

	default:
		break;
	}

	//����ȊO�̓G���[
	return Jan_Result::_ERROR;
}