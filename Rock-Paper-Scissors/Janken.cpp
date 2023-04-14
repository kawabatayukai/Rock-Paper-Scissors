#include"DxLib.h"
#include"KeyManager.h"
#include"Janken.h"


//�R���X�g���N�^�@�@�@�@�@�@�@�@�@�@enemy�̏o���肪���܂�
Janken::Janken(Jan_Type enemy_jan, const int stage_num)
	: enemy_jan(enemy_jan), p_image_x(-50), e_image_x(1330), stage_num(stage_num)
{
	//�K���ɏ�����
	player_jan = Jan_Type::ROCK;
	result = Jan_Result::_ERROR;

	//�摜�ǂݍ���
	LoadDivGraph("images/Janken_Test.png", 3, 3, 1, 200, 200, image);
	image_back = LoadGraph("images/Jan_Back_ver1.png");             //����񂯂񒆔w�i
	image_hand = LoadGraph("images/Janken_Hand2.png");
	image_player = LoadGraph("images/sd_body-1.png");
	image_enemy = LoadGraph("images/tyokitest.png");

	//�G�̉摜
	image_all_enemy[0] = LoadGraph("images/tyokitest.png");
	image_all_enemy[1] = LoadGraph("images/tyokitest.png");
	image_all_enemy[2] = LoadGraph("images/stage02/ex.png");
	image_all_enemy[3] = LoadGraph("images/stage03/stage03attack.png");
	image_all_enemy[4] = LoadGraph("images/Stage04/�X�e�[�W4_�{�X100.png");
	image_all_enemy[5] = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png");
	image_all_enemy[6] = LoadGraph("images/tyokitest.png");
	image_all_enemy[7] = LoadGraph("images/tyokitest.png");
	image_all_enemy[8] = LoadGraph("images/stage08/Stage8_image100.png");
	image_all_enemy[9] = LoadGraph("images/stage09/Stage9_100.png");
	image_all_enemy[10] = LoadGraph("images/tyokitest.png");

	//�t�H���g�f�[�^���쐬�@�@�@�@�@�@Windows�W�����ڃt�H���g�Ȃ���v�B�����@�@�@[��� "Yu Gothic UI"]
	font_result = CreateFontToHandle("���C���I", 70, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
	font_other = CreateFontToHandle("���C���I", 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	//�F
	blue      = GetColor(0, 0, 255);    
	red       = GetColor(255, 0, 0);
	brack     = GetColor(0, 0, 0);
	white     = GetColor(255, 255, 255);
	green     = GetColor(0, 255, 0);
}

//�f�X�g���N�^
Janken::~Janken()
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(font_result);
}

//�X�V
void Janken::Update()
{
	//40�t���[����
	if (++time > 40)
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
	else
	{
		const int speed = 10;     //�ړ��X�s�[�h
		const int p_goal = 200;   //��~�_player
		const int e_goal = 1070;  //��~�_enemy

		//�v���C���[�摜���ړ�������
		p_image_x += speed;
		if (p_image_x > p_goal) p_image_x = p_goal;

		//�G�摜���ړ�������
		e_image_x -= speed;
		if (e_image_x < e_goal) e_image_x = e_goal;
	}
}

//�`��
void Janken::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, TRUE);

	//�v���C���[
	DrawRotaGraph(p_image_x, 300, 2, 0, image_player, TRUE, TRUE);

	//�摜�ǂݍ��݂Ɏ��s���Ă��Ȃ����
	if (image_all_enemy[stage_num] != -1)
	{
		DrawRotaGraph(e_image_x, 600, 2, 0, image_all_enemy[stage_num], TRUE);
	}
	else
	{
		DrawRotaGraph(e_image_x, 600, 2, 0, image_enemy, TRUE);
	}


	//40�t���[����
	if (time > 40)
	{
		//�ǂ̃{�^����������Ă��Ȃ��Ƃ�
		if (button_B == false && button_Y == false && button_X == false)
		{
			DrawStringToHandle(380, 450, "����񂯂�....", white, font_other);

			//�ӂ�����
			DrawOval(600, 100, 130, 80, 0xffffff, TRUE);
			DrawOval(480, 200, 40, 20, 0xffffff, TRUE);
			DrawOval(400, 230, 20, 10, 0xffffff, TRUE);
			DrawRotaGraph(600, 100, 0.35, 0, image_hand, TRUE);  //��
		}
		else
		{
			DrawStringToHandle(400, 450, "�� ��", white, font_other);

			//�v���C���[�̎�
			DrawRotaGraph(420, 180, 1.0, 0.5, image[static_cast<int>(player_jan)], TRUE);

			//�G�̎�
			DrawRotaGraph(850, 500, 1.0, 0.5, image[static_cast<int>(enemy_jan)], TRUE);


			//����񂯂�̌��ʁi�v���C���[�ڐ��j
			switch (result)
			{
			case Jan_Result::LOSE:

				DrawStringToHandle(50, 50, "LOSE...", blue, font_result, brack);
				DrawStringToHandle(950, 300, "WIN!", red, font_result, brack);
				break;

			case Jan_Result::WIN:

				DrawStringToHandle(50, 50, "WIN!", red, font_result, brack);
				DrawStringToHandle(950, 300, "LOSE...", blue, font_result, brack);
				break;

			case Jan_Result::ONEMORE:

				DrawStringToHandle(50, 50, "AGAIN!", 0xffffff, font_result);
				DrawStringToHandle(850, 300, "AGAIN!", 0xffffff,font_result);
				break;

			default:
				break;
			}

			//�_��
			static int counter;

			if (counter++ < 30)
			{
				DrawStringToHandle(350, 650, "-- Press  A  Button --", white, font_other, green);
			}
			else if (counter > 60)  counter = 0;
			else {}
		}
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