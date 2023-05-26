
#include"DxLib.h"
#include<math.h>
#include "Jangeki_Base.h"
#include"GameData.h"

//�R���X�g���N�^
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, Jan_Type type, bool ref)
	: x(x), y(y), r(r), speed(speed), smoke_index(0.0), rate_turn(0.0), type(type), refrection(ref), rate_pct(200.0)
	, player_effect(EFFECT_TYPE::_NO_EFFECT), enemy_effect(EFFECT_TYPE::_NO_EFFECT)
	, effect_x(0.0f), effect_y(0.0f)
{

	//���˂����
	if (ref == true) LoadDivGraph("images/stage09/Reflection_Jangeki.png", 3, 3, 1, 100, 100, reflection_image);

	index_max = 11;
}

//�R���X�g���N�^�i�p�x����j
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type, bool ref)
	: x(x), y(y), r(r), smoke_index(0.0), rate_turn(0.0), type(type), refrection(ref), rate_pct(200.0)
	, player_effect(EFFECT_TYPE::_NO_EFFECT), enemy_effect(EFFECT_TYPE::_NO_EFFECT)
	, effect_x(0.0f), effect_y(0.0f)
{
	//���˂����
	if (ref == true) LoadDivGraph("images/stage09/Reflection_Jangeki.png", 3, 3, 1, 100, 100, reflection_image);

	index_max = 11;

	//x,y�����̃X�s�[�h�����߂�
	this->speed = fabsf(speed) * cosf(static_cast<float>(angle));
	speed_y = fabsf(speed) * sinf(static_cast<float>(angle));
}

//�f�X�g���N�^
Jangeki_Base::~Jangeki_Base()
{
}

int Jangeki_Base::image[3];              //����񌂉摜
int Jangeki_Base::image_effects[3][12];  //�ђʎ��G�t�F�N�g
int Jangeki_Base::image_smoke[3][4];        //�X���[�N�ȃG�t�F�N�g

//�摜�ǂݍ���
void Jangeki_Base::Input_Images()
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//�ʏ킶���
	LoadDivGraph("images/Effect/enemy_jan2.png", 3, 3, 1, 100, 100, image);

	//�G�t�F�N�g
	LoadDivGraph("images/Effect/smoke_gu.png", 4, 4, 1, 170, 170, image_smoke[0]);
	LoadDivGraph("images/Effect/smoke_tyoki.png", 4, 4, 1, 170, 170, image_smoke[1]);
	LoadDivGraph("images/Effect/smoke_pa.png", 4, 4, 1, 170, 170, image_smoke[2]);


	LoadDivGraph("images/Effect/win_gu.png", 12, 12, 1, 240, 240, image_effects[0]);
	LoadDivGraph("images/Effect/win_tyoki.png", 12, 12, 1, 240, 240, image_effects[1]);
	LoadDivGraph("images/Effect/win_pa.png", 12, 12, 1, 240, 240, image_effects[2]);
}

//�X�V
void Jangeki_Base::Update()
{
	x += speed;
	y -= speed_y;

	//�G�t�F�N�g
	Update_Effect();
}

//�`��
void Jangeki_Base::Draw() const
{
	//�g�嗦
	double rate = (static_cast<double>(r) * 2) / rate_pct;

	//���W��int�^�ɕϊ��@�i�x�����炷�j
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	//������ϊ�
	int type_num = static_cast<int>(type);
	if (type_num > 2) type_num = 0;

	//����񌂓��m�̏Փ˂ŏ������Ƃ��̂�
	if (enemy_effect == EFFECT_TYPE::WIN)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 180);
		DrawRotaGraphF(x, y, 1.2, turn_effect, image_effects[type_num][index_effect], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(x, y, 0.9, 0, image_effects[type_num][index_effect], TRUE);
	}
	else
	{

	}

	//���˂łȂ��Ƃ�
	if (refrection == false)
	{
		//�X���[�N�G�t�F�N�g
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(x, y, rate * 0.75, rate_turn, image_smoke[type_num][2], TRUE);
		DrawRotaGraph(x, y, rate * 0.75, -rate_turn, image_smoke[type_num][1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//�ʏ킶���
		DrawRotaGraph(x, y, rate, 0, image[type_num], TRUE);
	}
	else
	{
		//�X���[�N�G�t�F�N�g
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(x, y, rate * 0.75, rate_turn, image_smoke[type_num][2], TRUE);
		DrawRotaGraph(x, y, rate * 0.75, -rate_turn, image_smoke[type_num][1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//���˂����
		DrawRotaGraph(x, y, rate, 0, reflection_image[type_num], TRUE);
	}
}

//��ʊO�ɂ��邩�@true:��ʊO�@false:��ʓ�
bool Jangeki_Base::CheckScreenOut()
{
	if (x > 1280 || x < 0) return true;
	if (y > 780 || y < 0) return true;

	return false;
}

//�G�t�F�N�g�𓮍삳����i�S�Ă̔h������񌂓��EUpdate�ŌĂԁj�����F�t���[�����̊g���
void Jangeki_Base::Update_Effect(double fp_rate)
{
	//�g�嗦�����X�ɏグ��
	rate_pct -= fp_rate;
	if (rate_pct <= 100) rate_pct = 100;

	//�X���[�N
	static int frame_count;
	if (++frame_count % 10 == 0)
	{
		smoke_index++;
		frame_count = 0;

		if (smoke_index > 3) smoke_index = 0;
	}
	rate_turn += 0.008;

	if (enemy_effect == EFFECT_TYPE::WIN)
	{
		static int frame;

		if (++frame % 2 == 0) index_effect++;
		turn_effect += 0.5;

		if (index_effect > index_max)
		{
			index_effect = 0;
			//effect_type = Jan_Result::_ERROR;
			enemy_effect = EFFECT_TYPE::_NO_EFFECT;
			turn_effect = 0.0;

			frame = 0;
		}
	}
}



// *********  �����̂���񌂑����Ǝ����̑������r  *********
// �E�����̑������s���i��@�����F�O�[�@�����F�p�[�j�@�@return 0
// �E�����̑������L���i��@�����F�O�[�@�����F�`���L�j�@return 1
// �E�@�@�@�������@�@�i��@�����F�O�[�@�����F�O�[�j�@�@return 2
int Jangeki_Base::CheckAdvantage(Jangeki_Base* jangeki)
{
	int result_num = 99;    //���ʂ��i�[

	// �����̂���񌂂̑�����
	switch (jangeki->GetType())
	{
	case Jan_Type::ROCK:         //�O�[�̎�

		if (this->type == Jan_Type::SCISSORS) result_num = 0; //�����̑������`���L�̎��@0(�s��)
		if (this->type == Jan_Type::PAPER) result_num = 1;    //�����̑������p�[�̎��@�@1(�L��)
		if (this->type == Jan_Type::ROCK) result_num = 2;     //�����̑������O�[�̎��@�@2(������)
		break;

	case Jan_Type::SCISSORS:     //�`���L�̎�

		if (this->type == Jan_Type::PAPER) result_num = 0;    //�����̑������p�[�̎��@0(�s��)
		if (this->type == Jan_Type::ROCK) result_num = 1;     //�����̑������O�[�̎��@1(�L��)
		if (this->type == Jan_Type::SCISSORS) result_num = 2; //�����̑������`���L�̎��@2(������)
		break;

	case Jan_Type::PAPER:        //�p�[�̎�

		if (this->type == Jan_Type::ROCK) result_num = 0;     //�����̑������O�[�̎��@0(�s��)
		if (this->type == Jan_Type::SCISSORS) result_num = 1; //�����̑������`���L�̎��@1(�L��)
		if (this->type == Jan_Type::PAPER) result_num = 2;    //�����̑������p�[�̎��@2(������)
		break;

	default:
		break;
	}

	//����񂯂񕉂�
	if (result_num == 0)
	{
		//enemy���̃G�t�F�N�g����
		jangeki->enemy_effect = EFFECT_TYPE::WIN;
	}
	//����񂯂񏟂�
	if (result_num == 1)
	{
		//player���̃G�t�F�N�g����
		player_effect = EFFECT_TYPE::WIN;
	}
	//����񂯂񂠂���
	if (result_num == 2)
	{
		//���E�G�t�F�N�g����
		player_effect = EFFECT_TYPE::OFFSET;
		jangeki->enemy_effect = EFFECT_TYPE::OFFSET;

		//enemy�������
		float e_x = jangeki->GetX();
		float e_y = jangeki->GetY();

		//����񌂊Ԃ̋���
		float dis_x = e_x - this->x;
		float dis_y = e_y - this->y;
		effect_x = dis_x / 2;
		effect_y = dis_y / 2;
	}

	return result_num;
}


//�ǐՑΏۂ̍��W���Z�b�g�@�@�v���C���[�̍��W����肽���Ƃ��Ɏg���܂�
void Jangeki_Base::SetTargetLocation(const float target_x, const float target_y)
{
	this->target_x = target_x;
	this->target_y = target_y;
}

//�G�̍��W���Z�b�g
void Jangeki_Base::SetEnemyLocation(const float enemy_x, const float enemy_y)
{
	this->enemy_x = enemy_x;
	this->enemy_y = enemy_y;
}

//�~�`�̓����蔻��
bool Jangeki_Base::Hit_CircleCircle(float c_x, float c_y, float c_r) const
{
	//�����Ƒ���Ԃ̃x�N�g�����v�Z
	float vectrX = fabsf(x - c_x);    //x���W�̍���
	float vectrY = fabsf(y - c_y);    //y���W�̍���
	float vectrLength = sqrtf((vectrX * vectrX) + (vectrY * vectrY));      //2�̉~�̋���  �x�N�g���̑傫�����v�Z

	//�����Ƒ���Ԃ̃x�N�g���Ɣ��a�̍��v���r
	if (vectrLength < (r + c_r)) return true;

	return false;
}

//�����蔻��
bool Jangeki_Base::Hit_Jangeki(const Jangeki_Base* jangeki)
{
	if (jangeki == nullptr) return false;

	if (Hit_CircleCircle(jangeki->GetX(), jangeki->GetY(), jangeki->GetR()) == true)
	{
		return true;
	}

	return false;
}

