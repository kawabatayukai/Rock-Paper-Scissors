#include"DxLib.h"
#include"KeyManager.h"
#include"Janken.h"

int Janken::font_result = 0;         //����(WIN or LOSE or ONEMORE) �p�t�H���g 
int Janken::font_other = 0;          //�u����񂯂�..�v,�u�ۂ�v�ȂǗp�t�H���g

#define STAR_MAX 50

//�R���X�g���N�^�@�@�@�@�@�@�@�@�@�@enemy�̏o���肪���܂�
Janken::Janken(Jan_Type enemy_jan, const int stage_num)
	: enemy_jan(enemy_jan), p_image_x(-50), e_image_x(1330), stage_num(stage_num), image_enemy(0), star_time(0)
	, winLine_angle(0.0)
{
	//�K���ɏ�����
	player_jan = Jan_Type::NONE;
	result = Jan_Result::_ERROR;

	//�摜�ǂݍ���
	LoadDivGraph("images/Janken_Test.png", 3, 3, 1, 200, 200, image);
	image_backjan = LoadGraph("images/Janken/touch_janBack.png");             //����񂯂񒆔w�i

	image_hand = LoadGraph("images/Janken_Hand2.png");

	LoadDivGraph("images/Player/�����p���}��ALL�摜.png", 1, 1, 1, 100, 100, &image_player);

	switch (stage_num)
	{
	case 1:
		image_enemy = LoadGraph("images/stage01/chicken_Janken.png");
		image_back = LoadGraph("images/stage01/Tutorial_Back.png");
		break;

	case 2:
		image_enemy = LoadGraph("images/stage02/ex.png");
		image_back = LoadGraph("images/stage02/mizuumi01.png");
		break;

	case 3:
		image_enemy = LoadGraph("images/stage03/stage03attack.png");
		image_back = LoadGraph("images/stage03/stage03back.png");
		break;

	case 4:
		image_enemy = LoadGraph("images/Stage04/stage_Boss04.png");
		image_back = LoadGraph("images/Stage04/Stage_Image2.png");
		break;

	case 5:
		image_enemy = LoadGraph("images/stage05/Stage5_Enemy_NoMove_L.png");
		image_back = LoadGraph("images/stage05/Stage5_Stageimage.png");
		break;

	case 6:
		image_enemy = LoadGraph("images/stage06/stage06_Janken.png");
		image_back = LoadGraph("images/stage06/mori32-.png");
		break;

	case 7:
		image_enemy = LoadGraph("images/stage07/stage07_Janken.png");
		image_back = LoadGraph("images/stage07/back02.png");
		break;

	case 8:
		image_enemy = LoadGraph("images/stage08/Stage8_image100.png");
		image_back = LoadGraph("images/stage08/Stage08_1.jpg");
		break;

	case 9:
		image_enemy = LoadGraph("images/stage09/Stage9_100.png");
		image_back = LoadGraph("images/stage09/stage09_image.png");
		break;

	case 10:
		image_enemy = LoadGraph("images/stage10/�X�e�[�W10�G�̉摜�P��.png");
		image_back = 0;
		break;


	default:
		break;
	}

	image_winLine = LoadGraph("images/Janken/Janken_WIN_Line.png");
	image_loseSmoke = new int[8];
	LoadDivGraph("images/Janken/Janken_LOSE_Smoke.png", 8, 8, 1, 240, 240, image_loseSmoke);

	//star
	stars = new Janken_Star * [STAR_MAX];
	for (int i = 0; i < STAR_MAX; i++) stars[i] = nullptr;
	stars[0] = new Janken_Star(70, 680, 0, 720);
	stars[1] = new Janken_Star(140, 640, 0, 720);
	stars[2] = new Janken_Star(210, 602, 0, 720);
	stars[3] = new Janken_Star(280, 562, 0, 720);
	stars[4] = new Janken_Star(350, 523, 0, 720);
	stars[5] = new Janken_Star(420, 484, 0, 720);
	stars[6] = new Janken_Star(490, 444, 0, 720);
	stars[7] = new Janken_Star(560, 405, 0, 720);
	stars[8] = new Janken_Star(770, 286, 0, 720);
	stars[9] = new Janken_Star(840, 247, 0, 720);
	stars[10] = new Janken_Star(910, 208, 0, 720);
	stars[11] = new Janken_Star(980, 168, 0, 720);
	stars[12] = new Janken_Star(1050, 129, 0, 720);
	stars[13] = new Janken_Star(1120, 90, 0, 720);
	stars[14] = new Janken_Star(1190, 50, 0, 720);
	stars[15] = new Janken_Star(1260, 11, 0, 720);

	//�t�H���g�f�[�^���쐬�@�@�@�@�@
	if(font_result == 0)
		font_result = CreateFontToHandle("���C���I", 70, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
	if(font_other == 0)
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
	delete image_loseSmoke;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
	if (image_back == -1 || image_back == 0)        //�摜�ǂݍ��ݎ��s
	{
		DrawBox(0, 0, 1280, 720, 0x808080, TRUE);
	}
	else
	{
		DrawGraph(0, 0, image_back, FALSE);
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
			//�W���� Smoke
			if (result == Jan_Result::WIN)
			{
				DrawRotaGraph(p_image_x, 300, 1, winLine_angle, image_winLine, TRUE);
				DrawRotaGraph(e_image_x, 600, 4, winLine_angle*-1, image_loseSmoke[smokeCount], TRUE);
			}
			else if (result == Jan_Result::LOSE)
			{
				DrawRotaGraph(e_image_x, 600, 1, winLine_angle, image_winLine, TRUE);
				DrawRotaGraph(p_image_x, 300, 4, winLine_angle * -1, image_loseSmoke[smokeCount], TRUE);
			}
			else {}

			SetDrawBlendMode(DX_BLENDMODE_ADD, 110);
			if (result == Jan_Result::WIN)
			{
				DrawRotaGraph(p_image_x, 300, 1.02, winLine_angle, image_winLine, TRUE);

				SetDrawBright(0, 0, 200);
				DrawRotaGraph(e_image_x, 600, 4, 0, image_loseSmoke[smokeCount], TRUE);
				SetDrawBright(255, 255, 255);
			}
			else if (result == Jan_Result::LOSE)
			{
				DrawRotaGraph(e_image_x, 600, 1.02, winLine_angle, image_winLine, TRUE);

				SetDrawBright(0, 0, 200);
				DrawRotaGraph(p_image_x, 300, 4, 0, image_loseSmoke[smokeCount], TRUE);
				SetDrawBright(255, 255, 255);
			}	
			else {}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


			DrawStringToHandle(400, 450, "�� ��", white, font_other);

			//�v���C���[�̎�
			if (player_jan != Jan_Type::NONE)
			{
				DrawRotaGraph(420, 180, 1.0, 0.5, image[static_cast<int>(player_jan)], TRUE);
			}

			//�G�̎�
			if (enemy_jan != Jan_Type::NONE)
			{
				DrawRotaGraph(850, 500, 1.0, 0.5, image[static_cast<int>(enemy_jan)], TRUE);
			}

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

	for (int i = 0; i < STAR_MAX; i++)
	{
		if (stars[i] == nullptr) break;

		if (stars[i]->GetX() >= 560.f && stars[i]->GetX() <= 740.f
			&& stars[i]->GetY() >= 300.f && stars[i]->GetY() <= 400.f)
		{
		}
		else
		{
			stars[i]->Draw();
		}
	}

	if (end_alpha_value > 0) SetDrawBlendMode(DX_BLENDMODE_ALPHA, end_alpha_value);
	//"VS"
	DrawGraph(0, 0, image_backjan, TRUE);
	//�v���C���[
	DrawRotaGraph(p_image_x, 300, 2, 0, image_player, TRUE);
	//Enemy
	DrawRotaGraph(e_image_x, 600, 2, 0, image_enemy, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//��
void Janken::Stars_Update()
{
	int starcount;
	for (starcount = 0; starcount < STAR_MAX; starcount++)
	{
		if (stars[starcount] == nullptr) break;
		stars[starcount]->Update();

		if (stars[starcount]->CheckScreenOut() == true)
		{
			delete stars[starcount];
			stars[starcount] = nullptr;

			//�l�߂�
			for (int d = 0; d < (STAR_MAX - 1); d++)
			{
				if (stars[d + 1] == nullptr) break;
				stars[d] = stars[d + 1];
				stars[d + 1] = nullptr;
			}
			starcount--;
		}
	}

	if (++star_time % 6 == 0)
	{
		if (starcount < STAR_MAX && stars[starcount] == nullptr)
		{
			stars[starcount] = new Janken_Star(1280.f, 0.f, 0.f, 720.f);
		}
	}

	if (result != Jan_Result::_ERROR) winLine_angle += 0.002;
	if (result != Jan_Result::_ERROR && star_time % 7 == 0) smokeCount++;
	if (smokeCount > 7) smokeCount = 0;
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


//(�������̎��p) �K�v�ȕϐ�������������
void Janken::OneMore_Init()
{
	button_B = false;   //B�{�^����������Ă��邩
	button_Y = false;   //Y�{�^����������Ă��邩
	button_X = false;   //X�{�^����������Ă��邩

	//�G�̏o������Đݒ�
	enemy_jan = Jan_Type::NONE;
	enemy_jan = static_cast<Jan_Type> (GetRand(2));
	

	result = Jan_Result::_ERROR;
}

//���ߓx�Z�b�g
void Janken::SetAlphaValue(const int& value)
{
	if (value > 0) end_alpha_value = value;
}