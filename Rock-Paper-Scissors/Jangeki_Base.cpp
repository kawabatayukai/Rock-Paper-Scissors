#include"DxLib.h"
#include<math.h>
#include "Jangeki_Base.h"
#include"GameData.h"

//�R���X�g���N�^
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, Jan_Type type, bool ref)
	: x(x), y(y), r(r), speed(speed), smoke_index(0.0), rate_turn(0.0), type(type), refrection(ref), rate_pct(200.0)
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//�摜�ǂݍ���
	LoadDivGraph("images/Effect/enemy_jan2.png", 3, 3, 1, 100, 100, image);
	
	//���˂����
	LoadDivGraph("images/stage09/Reflection_Jangeki.png", 3, 3, 1, 100, 100, reflection_image);

	//�G�t�F�N�g
	switch (type)
	{
	case Jan_Type::ROCK:
		LoadDivGraph("images/Effect/smoke_gu.png", 4, 4, 1, 170, 170, image_smoke);
		break;

	case Jan_Type::SCISSORS:
		LoadDivGraph("images/Effect/smoke_tyoki.png", 4, 4, 1, 170, 170, image_smoke);
		break;

	case Jan_Type::PAPER:
		LoadDivGraph("images/Effect/smoke_pa.png", 4, 4, 1, 170, 170, image_smoke);
		break;

	case Jan_Type::NONE:
		break;

	default:
		break;
	}

}

//�R���X�g���N�^�i�p�x����j
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type, bool ref)
	: x(x), y(y), r(r), smoke_index(0.0), rate_turn(0.0), type(type), refrection(ref), rate_pct(200.0)
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//�摜�ǂݍ���
	LoadDivGraph("images/Effect/enemy_jan2.png", 3, 3, 1, 100, 100, image);

	//���˂����
	LoadDivGraph("images/stage09/Reflection_Jangeki.png", 3, 3, 1, 100, 100, reflection_image);

	//�G�t�F�N�g
	switch (type)
	{
	case Jan_Type::ROCK:
		LoadDivGraph("images/Effect/smoke_gu.png", 4, 4, 1, 170, 170, image_smoke);
		break;

	case Jan_Type::SCISSORS:
		LoadDivGraph("images/Effect/smoke_tyoki.png", 4, 4, 1, 170, 170, image_smoke);
		break;

	case Jan_Type::PAPER:
		LoadDivGraph("images/Effect/smoke_pa.png", 4, 4, 1, 170, 170, image_smoke);
		break;

	case Jan_Type::NONE:
		break;

	default:
		break;
	}

	//x,y�����̃X�s�[�h�����߂�
	this->speed = fabsf(speed) * cosf(static_cast<float>(angle));
	speed_y     = fabsf(speed) * sinf(static_cast<float>(angle));
}

//�f�X�g���N�^
Jangeki_Base::~Jangeki_Base()
{
	DrawRotaGraph(x, y, 1, 0, image[0], TRUE);
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

	//���˂łȂ��Ƃ�
	if (refrection == false)
	{
		//�X���[�N�G�t�F�N�g
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(x, y, rate * 0.75, rate_turn, image_smoke[2], TRUE);
		DrawRotaGraph(x, y, rate * 0.75, -rate_turn, image_smoke[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//�ʏ킶���
		DrawRotaGraph(x, y, rate, 0, image[type_num], TRUE);
	}
	else
	{
		//�X���[�N�G�t�F�N�g
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(x, y, rate * 0.75, rate_turn, image_smoke[2], TRUE);
		DrawRotaGraph(x, y, rate * 0.75, -rate_turn, image_smoke[1], TRUE);
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
	static short frame_count;
	if (++frame_count % 10 == 0)
	{
		smoke_index++;
		frame_count = 0;

		if (smoke_index > 3) smoke_index = 0;

		//rate_turn = GetRand(360);
	}
	rate_turn += 0.008;
}



// *********  �����̂���񌂑����Ǝ����̑������r  *********
// �E�����̑������s���i��@�����F�O�[�@�����F�p�[�j�@�@return 0
// �E�����̑������L���i��@�����F�O�[�@�����F�`���L�j�@return 1
// �E�@�@�@�������@�@�i��@�����F�O�[�@�����F�O�[�j�@�@return 2
int Jangeki_Base::CheckAdvantage(const Jangeki_Base* jangeki)
{
	int result_num = 0;    //���ʂ��i�[

	// �����̂���񌂂̑�����
	switch (jangeki->GetType())
	{
	case Jan_Type::ROCK:         //�O�[�̎�

		if (this->type == Jan_Type::SCISSORS) result_num= 0; //�����̑������`���L�̎��@0(�s��)
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
	if (result_num == 1) //����񂯂񏟂�
	{
		GameData::Add_Score(100);    //�X�R�A���Z
	}
	if (result_num == 2) //����񂯂񂠂���
	{
		GameData::Add_Score(100 / 2);    //�X�R�A���Z
	}

	//�L���̎�
	if (result_num == 1)
	{
		GameData::Add_Score(100);    //�X�R�A���Z
	}

	return result_num;
}


//�ǐՑΏۂ̍��W���Z�b�g�@�@�v���C���[�̍��W����肽���Ƃ��Ɏg���܂�
void Jangeki_Base::SetTargetLocation(const float target_x, const float target_y)
{
	this->target_x = target_x;
	this->target_y = target_y;
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

