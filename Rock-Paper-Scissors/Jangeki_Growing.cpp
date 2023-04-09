#include"DxLib.h"
#include"Jangeki_Growing.h"

//�R���X�g���N�^
Jangeki_Growing::Jangeki_Growing(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type),
	 frame_count(0), index_jangeki(1), rate_pct(200.0)
{
	//�����ɉ������摜
	switch (type)
	{
	case Jan_Type::ROCK:

		LoadDivGraph("images/Effect/jan120_gu.png", 6, 6, 1, 120, 120, image_jangeki);
		break;

	case Jan_Type::SCISSORS:

		LoadDivGraph("images/Effect/jan120_tyoki.png", 6, 6, 1, 120, 120, image_jangeki);
		break;

	case Jan_Type::PAPER:

		LoadDivGraph("images/Effect/jan120_pa.png", 6, 6, 1, 120, 120, image_jangeki);
		break;

	default:
		break;
	}
}

//�R���X�g���N�^�i�p�x�t���j
Jangeki_Growing::Jangeki_Growing(float x, float y, float r, float speed, double angle, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, angle, type),
	 frame_count(0), index_jangeki(1), rate_pct(200.0)
{
	//�����ɉ������摜
	switch (type)
	{
	case Jan_Type::ROCK:

		LoadDivGraph("images/Effect/jan120_gu.png", 6, 6, 1, 120, 120, image_jangeki);
		break;

	case Jan_Type::SCISSORS:

		LoadDivGraph("images/Effect/jan120_tyoki.png", 6, 6, 1, 120, 120, image_jangeki);
		break;

	case Jan_Type::PAPER:

		LoadDivGraph("images/Effect/jan120_pa.png", 6, 6, 1, 120, 120, image_jangeki);
		break;

	default:
		break;
	}
}

//�f�X�g���N�^
Jangeki_Growing::~Jangeki_Growing(){}

//�X�V�i�I�[�o�[���C�h�j
void Jangeki_Growing::Update()
{
	x += speed;
	y -= speed_y;

	if (++frame_count % 6 == 0)
	{
		index_jangeki++;  //���̉摜
		if (index_jangeki > 3) index_jangeki = 1;

		frame_count = 0;
	}

	//�g�嗦�����X�ɏグ��
	rate_pct -= 5.0;
	if (rate_pct <= 100) rate_pct = 100;
}

//�`��i�I�[�o�[���C�h�j
void Jangeki_Growing::Draw() const
{
	//�g�嗦
	//double rate = (static_cast<double>(r) * 2) / 100;
	double rate = (static_cast<double>(r) * 2) / rate_pct;

	//���W��int�^�ɕϊ��@�i�x�����炷�j
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	//�`��
	DrawRotaGraph(x, y, rate, 0, image_jangeki[index_jangeki], TRUE);
}