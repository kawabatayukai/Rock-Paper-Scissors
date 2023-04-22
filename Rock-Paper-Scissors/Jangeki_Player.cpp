#include"DxLib.h"
#include"Jangeki_Player.h"

//�R���X�g���N�^
Jangeki_Player::Jangeki_Player(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type),
	frame_count(0), index_jangeki(1), rate_pct(200.0), index_effect(0), index_max(0), turn_effect(0.0)
{
	//�����ɉ������摜
	switch (type)
	{
	case Jan_Type::ROCK:

		LoadDivGraph("images/Effect/jan100_gu.png", 6, 6, 1, 100, 100, image_jangeki);
		image_lightning = LoadGraph("images/Effect/lightning_gu_120.png");
		break;

	case Jan_Type::SCISSORS:

		LoadDivGraph("images/Effect/jan100_tyoki.png", 6, 6, 1, 100, 100, image_jangeki);
		image_lightning = LoadGraph("images/Effect/lightning_tyoki_120.png");
		break;

	case Jan_Type::PAPER:

		LoadDivGraph("images/Effect/jan100_pa.png", 6, 6, 1, 100, 100, image_jangeki);
		image_lightning = LoadGraph("images/Effect/lightning_pa_120.png");
		break;

	default:
		break;
	}

	//�G�t�F�N�g��ǂݍ���ł���
	//index_max = 10;     //����
	//index_max = 15;     //2
	index_max = 12;     //3
	//index_max = 12;       //4


	//LoadDivGraph("images/Effect/test_jan.png", 10, 10, 1, 180, 180, image_effect);
	//LoadDivGraph("images/Effect/test_jan2.png", 15, 15, 1, 156, 156, image_effect);
	//LoadDivGraph("images/Effect/test_jan3.png", 12, 12, 1, 240, 240, image_effect);
	//LoadDivGraph("images/Effect/test_jan4.png", 12, 12, 1, 210, 210, image_effect);

	LoadDivGraph("images/Effect/win_gu.png", 12, 12, 1, 240, 240, image_effects[0]);
	LoadDivGraph("images/Effect/win_tyoki.png", 12, 12, 1, 240, 240, image_effects[1]);
	LoadDivGraph("images/Effect/win_pa.png", 12, 12, 1, 240, 240, image_effects[2]);
}

//�R���X�g���N�^�i�p�x�t���j
Jangeki_Player::Jangeki_Player(float x, float y, float r, float speed, double angle, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, angle, type),
	 frame_count(0), index_jangeki(1), rate_pct(200.0), index_effect(0), index_max(0), turn_effect(0.0)
{
	//�����ɉ������摜
	switch (type)
	{
	case Jan_Type::ROCK:

		LoadDivGraph("images/Effect/jan100_gu.png", 6, 6, 1, 100, 100, image_jangeki);
		image_lightning = LoadGraph("images/Effect/lightning_gu_120.png");
		//image_lightning = LoadGraph("images/Effect/effect_gu.png");
		break;

	case Jan_Type::SCISSORS:

		LoadDivGraph("images/Effect/jan100_tyoki.png", 6, 6, 1, 100, 100, image_jangeki);
		image_lightning = LoadGraph("images/Effect/lightning_tyoki_120.png");
		//image_lightning = LoadGraph("images/Effect/effect_tyoki.png");
		break;

	case Jan_Type::PAPER:

		LoadDivGraph("images/Effect/jan100_pa.png", 6, 6, 1, 100, 100, image_jangeki);
		image_lightning = LoadGraph("images/Effect/lightning_pa_120.png");
		//image_lightning = LoadGraph("images/Effect/effect_pa.png");
		break;

	default:
		break;
	}

	//�G�t�F�N�g��ǂݍ���ł���
	//index_max = 10;     //����
	//index_max = 15;     //2
	index_max = 12;     //3
	//index_max = 12;       //4

	//LoadDivGraph("images/Effect/test_jan.png", 10, 10, 1, 180, 180, image_effect);
	//LoadDivGraph("images/Effect/test_jan2.png", 15, 15, 1, 156, 156, image_effect);
	//LoadDivGraph("images/Effect/test_jan3.png", 12, 12, 1, 240, 240, image_effect);
	//LoadDivGraph("images/Effect/test_jan4.png", 12, 12, 1, 210, 210, image_effect);

	LoadDivGraph("images/Effect/win_gu.png", 12, 12, 1, 240, 240, image_effects[0]);
	LoadDivGraph("images/Effect/win_tyoki.png", 12, 12, 1, 240, 240, image_effects[1]);
	LoadDivGraph("images/Effect/win_pa.png", 12, 12, 1, 240, 240, image_effects[2]);
}

//�f�X�g���N�^
Jangeki_Player::~Jangeki_Player()
{
	
}

//�X�V�i�I�[�o�[���C�h�j
void Jangeki_Player::Update()
{
	x += speed;
	y -= speed_y;

	//����񌂓��m�̏Փ˂ŏ������Ƃ��̂�
	//if (effect_type == Jan_Result::WIN)

	if(player_effect == EFFECT_TYPE::WIN)
	{
		frame_count++;
		if (frame_count % 2 == 0) index_effect++;
		turn_effect += 0.5;

		if (index_effect > index_max)
		{
			index_effect = 0;
			//effect_type = Jan_Result::_ERROR;
			player_effect == EFFECT_TYPE::_NO_EFFECT;
			turn_effect = 0.0;
		}
	}

	//�g�嗦�����X�ɏグ��
	rate_pct -= 5.0;
	if (rate_pct <= 100) rate_pct = 100;
}

//�`��i�I�[�o�[���C�h�j
void Jangeki_Player::Draw() const
{
	//�g�嗦
	double rate = (static_cast<double>(r) * 2) / rate_pct;

	//���W��int�^�ɕϊ��@�i�x�����炷�j
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	//�G�t�F�N�g(���I�ȂȂɂ�)
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                       //���Z�������[�h
	DrawRotaGraph(x, y, 0.65, GetRand(360), image_lightning, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);               //�u�����h���[�h�����Z�b�g

	Draw_Effect();

	//�`��
	DrawRotaGraph(x, y, rate, 0, image_jangeki[2], TRUE);
}  


//�ђʃG�t�F�N�g�`��
void  Jangeki_Player::Draw_Effect() const
{
	//����񌂓��m�̏Փ˂ŏ������Ƃ��̂�
	//if (effect_type == Jan_Result::WIN)
	if(player_effect == EFFECT_TYPE::WIN)
	{
		int n = static_cast<int>(this->type);

		SetDrawBlendMode(DX_BLENDMODE_ADD, 180);
		//DrawRotaGraphF(x, y, 1.2, turn_effect, image_effects[n][index_effect], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraphF(x, y, 0.9, 0, image_effects[n][index_effect], TRUE);
	}
	else
	{
		return;
	}
}