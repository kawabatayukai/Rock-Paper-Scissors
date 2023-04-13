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
}

//デストラクタ
Jangeki_Growing::~Jangeki_Growing(){}

//更新（オーバーライド）
void Jangeki_Growing::Update()
{
	x += speed;
	y -= speed_y;

	//if (++frame_count % 1 == 0)
	//{
	//	index_jangeki++;  //次の画像
	//	if (index_jangeki > 3) index_jangeki = 1;

	//	frame_count = 0;
	//}

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

	//エフェクト(雷的ななにか)
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                       //加算合成モード
	DrawRotaGraph(x, y, 0.65, GetRand(360), image_lightning, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);               //ブレンドモードをリセット

	//描画
	DrawRotaGraph(x, y, rate, 0, image_jangeki[2], TRUE);
}  