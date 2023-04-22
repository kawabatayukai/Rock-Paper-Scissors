#include"DxLib.h"
#include"Jangeki_Player.h"

//コンストラクタ
Jangeki_Player::Jangeki_Player(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type),
	frame_count(0), index_jangeki(1), rate_pct(200.0), index_effect(0), index_max(0), turn_effect(0.0)
{
	//属性に応じた画像
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

	//エフェクトを読み込んでおく
	//index_max = 10;     //無印
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

//コンストラクタ（角度付き）
Jangeki_Player::Jangeki_Player(float x, float y, float r, float speed, double angle, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, angle, type),
	 frame_count(0), index_jangeki(1), rate_pct(200.0), index_effect(0), index_max(0), turn_effect(0.0)
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

	//エフェクトを読み込んでおく
	//index_max = 10;     //無印
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

//デストラクタ
Jangeki_Player::~Jangeki_Player()
{
	
}

//更新（オーバーライド）
void Jangeki_Player::Update()
{
	x += speed;
	y -= speed_y;

	//じゃん撃同士の衝突で勝ったときのみ
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

	//拡大率を徐々に上げる
	rate_pct -= 5.0;
	if (rate_pct <= 100) rate_pct = 100;
}

//描画（オーバーライド）
void Jangeki_Player::Draw() const
{
	//拡大率
	double rate = (static_cast<double>(r) * 2) / rate_pct;

	//座標をint型に変換　（警告減らす）
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	//エフェクト(雷的ななにか)
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);                       //加算合成モード
	DrawRotaGraph(x, y, 0.65, GetRand(360), image_lightning, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 255);               //ブレンドモードをリセット

	Draw_Effect();

	//描画
	DrawRotaGraph(x, y, rate, 0, image_jangeki[2], TRUE);
}  


//貫通エフェクト描画
void  Jangeki_Player::Draw_Effect() const
{
	//じゃん撃同士の衝突で勝ったときのみ
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