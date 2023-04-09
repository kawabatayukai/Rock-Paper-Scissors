#include"DxLib.h"
#include"Jangeki_Growing.h"

//コンストラクタ
Jangeki_Growing::Jangeki_Growing(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type),
	 frame_count(0), index_jangeki(1), rate_pct(200.0)
{
	//属性に応じた画像
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

//コンストラクタ（角度付き）
Jangeki_Growing::Jangeki_Growing(float x, float y, float r, float speed, double angle, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, angle, type),
	 frame_count(0), index_jangeki(1), rate_pct(200.0)
{
	//属性に応じた画像
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

//デストラクタ
Jangeki_Growing::~Jangeki_Growing(){}

//更新（オーバーライド）
void Jangeki_Growing::Update()
{
	x += speed;
	y -= speed_y;

	if (++frame_count % 6 == 0)
	{
		index_jangeki++;  //次の画像
		if (index_jangeki > 3) index_jangeki = 1;

		frame_count = 0;
	}

	//拡大率を徐々に上げる
	rate_pct -= 5.0;
	if (rate_pct <= 100) rate_pct = 100;
}

//描画（オーバーライド）
void Jangeki_Growing::Draw() const
{
	//拡大率
	//double rate = (static_cast<double>(r) * 2) / 100;
	double rate = (static_cast<double>(r) * 2) / rate_pct;

	//座標をint型に変換　（警告減らす）
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	//描画
	DrawRotaGraph(x, y, rate, 0, image_jangeki[index_jangeki], TRUE);
}