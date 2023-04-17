#include"DxLib.h"
#include<math.h>
#include "Jangeki_Base.h"
#include"GameData.h"

//コンストラクタ
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, Jan_Type type, bool ref)
	: x(x), y(y), r(r), speed(speed), smoke_index(0.0), rate_turn(0.0), type(type), refrection(ref), rate_pct(200.0)
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//画像読み込み
	LoadDivGraph("images/Effect/enemy_jan2.png", 3, 3, 1, 100, 100, image);
	
	//反射じゃん撃
	LoadDivGraph("images/stage09/Reflection_Jangeki.png", 3, 3, 1, 100, 100, reflection_image);

	//エフェクト
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

//コンストラクタ（角度あり）
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type, bool ref)
	: x(x), y(y), r(r), smoke_index(0.0), rate_turn(0.0), type(type), refrection(ref), rate_pct(200.0)
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//画像読み込み
	LoadDivGraph("images/Effect/enemy_jan2.png", 3, 3, 1, 100, 100, image);

	//反射じゃん撃
	LoadDivGraph("images/stage09/Reflection_Jangeki.png", 3, 3, 1, 100, 100, reflection_image);

	//エフェクト
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

	//x,y方向のスピードを決める
	this->speed = fabsf(speed) * cosf(static_cast<float>(angle));
	speed_y     = fabsf(speed) * sinf(static_cast<float>(angle));
}

//デストラクタ
Jangeki_Base::~Jangeki_Base()
{
	DrawRotaGraph(x, y, 1, 0, image[0], TRUE);
}

//更新
void Jangeki_Base::Update()
{
	x += speed;
	y -= speed_y;

	//エフェクト
	Update_Effect();
	
}

//描画
void Jangeki_Base::Draw() const
{
	//拡大率
	double rate = (static_cast<double>(r) * 2) / rate_pct;

	//座標をint型に変換　（警告減らす）
	int x = static_cast<int>(this->x);
	int y = static_cast<int>(this->y);

	//属性を変換
	int type_num = static_cast<int>(type);
	if (type_num > 2) type_num = 0;

	//反射でないとき
	if (refrection == false)
	{
		//スモークエフェクト
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(x, y, rate * 0.75, rate_turn, image_smoke[2], TRUE);
		DrawRotaGraph(x, y, rate * 0.75, -rate_turn, image_smoke[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//通常じゃん撃
		DrawRotaGraph(x, y, rate, 0, image[type_num], TRUE);
	}
	else
	{
		//スモークエフェクト
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawRotaGraph(x, y, rate * 0.75, rate_turn, image_smoke[2], TRUE);
		DrawRotaGraph(x, y, rate * 0.75, -rate_turn, image_smoke[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		//反射じゃん撃
		DrawRotaGraph(x, y, rate, 0, reflection_image[type_num], TRUE);
	}
}

//画面外にいるか　true:画面外　false:画面内
bool Jangeki_Base::CheckScreenOut()
{
	if (x > 1280 || x < 0) return true;
	if (y > 780 || y < 0) return true;

	return false;
}

//エフェクトを動作させる（全ての派生じゃん撃内・Updateで呼ぶ）引数：フレーム毎の拡大量
void Jangeki_Base::Update_Effect(double fp_rate)
{
	//拡大率を徐々に上げる
	rate_pct -= fp_rate;
	if (rate_pct <= 100) rate_pct = 100;

	//スモーク
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



// *********  引数のじゃん撃属性と自分の属性を比較  *********
// ・自分の属性が不利（例　自分：グー　引数：パー）　　return 0
// ・自分の属性が有利（例　自分：グー　引数：チョキ）　return 1
// ・　　　あいこ　　（例　自分：グー　引数：グー）　　return 2
int Jangeki_Base::CheckAdvantage(const Jangeki_Base* jangeki)
{
	int result_num = 0;    //結果を格納

	// 引数のじゃん撃の属性が
	switch (jangeki->GetType())
	{
	case Jan_Type::ROCK:         //グーの時

		if (this->type == Jan_Type::SCISSORS) result_num= 0; //自分の属性がチョキの時　0(不利)
		if (this->type == Jan_Type::PAPER) result_num = 1;    //自分の属性がパーの時　　1(有利)
		if (this->type == Jan_Type::ROCK) result_num = 2;     //自分の属性がグーの時　　2(あいこ)
		break;

	case Jan_Type::SCISSORS:     //チョキの時

		if (this->type == Jan_Type::PAPER) result_num = 0;    //自分の属性がパーの時　0(不利)
		if (this->type == Jan_Type::ROCK) result_num = 1;     //自分の属性がグーの時　1(有利)
		if (this->type == Jan_Type::SCISSORS) result_num = 2; //自分の属性がチョキの時　2(あいこ)
		break;

	case Jan_Type::PAPER:        //パーの時

		if (this->type == Jan_Type::ROCK) result_num = 0;     //自分の属性がグーの時　0(不利)
		if (this->type == Jan_Type::SCISSORS) result_num = 1; //自分の属性がチョキの時　1(有利)
		if (this->type == Jan_Type::PAPER) result_num = 2;    //自分の属性がパーの時　2(あいこ)
		break;

	default:
		break;
	}
	if (result_num == 1) //じゃんけん勝ち
	{
		GameData::Add_Score(100);    //スコア加算
	}
	if (result_num == 2) //じゃんけんあいこ
	{
		GameData::Add_Score(100 / 2);    //スコア加算
	}

	//有利の時
	if (result_num == 1)
	{
		GameData::Add_Score(100);    //スコア加算
	}

	return result_num;
}


//追跡対象の座標をセット　　プレイヤーの座標を取りたいときに使えます
void Jangeki_Base::SetTargetLocation(const float target_x, const float target_y)
{
	this->target_x = target_x;
	this->target_y = target_y;
}



//円形の当たり判定
bool Jangeki_Base::Hit_CircleCircle(float c_x, float c_y, float c_r) const
{
	//自分と相手間のベクトルを計算
	float vectrX = fabsf(x - c_x);    //x座標の差分
	float vectrY = fabsf(y - c_y);    //y座標の差分
	float vectrLength = sqrtf((vectrX * vectrX) + (vectrY * vectrY));      //2つの円の距離  ベクトルの大きさを計算

	//自分と相手間のベクトルと半径の合計を比較
	if (vectrLength < (r + c_r)) return true;

	return false;
}

//当たり判定
bool Jangeki_Base::Hit_Jangeki(const Jangeki_Base* jangeki)
{
	if (jangeki == nullptr) return false;

	if (Hit_CircleCircle(jangeki->GetX(), jangeki->GetY(), jangeki->GetR()) == true)
	{
		return true;
	}

	return false;
}

