#include"DxLib.h"
#include<math.h>
#include "Jangeki_Base.h"

//コンストラクタ
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, Jan_Type type)
	: x(x), y(y), r(r), speed(speed), type(type)
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//画像読み込み
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image);
}

//コンストラクタ（角度あり）
Jangeki_Base::Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type)
	: x(x), y(y), r(r), type(type)
{
	for (int i = 0; i < 3; i++) image[i] = 0;

	//画像読み込み
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image);

	//x,y方向のスピードを決める
	this->speed = fabsf(speed) * cosf(static_cast<float>(angle));
	speed_y     = fabsf(speed) * sinf(static_cast<float>(angle));
}

//デストラクタ
Jangeki_Base::~Jangeki_Base()
{
}

//更新
void Jangeki_Base::Update()
{
	x += speed;
	y -= speed_y;
}

//描画
void Jangeki_Base::Draw() const
{
	//画像がないとき
	if (image[0] == 0)
	{
		switch (type)
		{
		case Jan_Type::ROCK:         //グー
			//水色
			DrawCircle((int)x, (int)y, (int)r, 0xff0000, TRUE);
			break;

		case Jan_Type::SCISSORS:     //チョキ
			//黄色
			DrawCircle((int)x, (int)y, (int)r, 0xffff00, TRUE);
			break;

		case Jan_Type::PAPER:        //パー
			//赤
			DrawCircle((int)x, (int)y, (int)r, 0x00ffff, TRUE);
			break;

		default:
			break;
		}
	}
	else
	{
		//拡大率
		double rate = (static_cast<double>(r) * 2) / 100;

		//座標をint型に変換　（警告減らす）
		int x = static_cast<int>(this->x);
		int y = static_cast<int>(this->y);

		switch (type)
		{
		case Jan_Type::ROCK:         //グー

			DrawRotaGraph(x, y, rate, 1, image[0], TRUE);
			break;

		case Jan_Type::SCISSORS:     //チョキ
			
			DrawRotaGraph(x, y, rate, 1, image[1], TRUE);
			break;

		case Jan_Type::PAPER:        //パー

			DrawRotaGraph(x, y, rate, 1, image[2], TRUE);
			break;

		default:
			break;
		}
	}
}

//画面外にいるか　true:画面外　false:画面内
bool Jangeki_Base::CheckScreenOut()
{
	if (x > 1280 || x < 0) return true;
	if (y > 720 || y < 0) return true;

	return false;
}



// *********  引数のじゃん撃属性と自分の属性を比較  *********
// ・自分の属性が不利（例　自分：グー　引数：パー）　　return 0
// ・自分の属性が有利（例　自分：グー　引数：チョキ）　return 1
// ・　　　あいこ　　（例　自分：グー　引数：グー）　　return 2
int Jangeki_Base::CheckAdvantage(const Jangeki_Base* jangeki)
{
	// 引数のじゃん撃の属性が
	switch (jangeki->GetType())
	{
	case Jan_Type::ROCK:         //グーの時

		if (this->type == Jan_Type::SCISSORS) return 0; //自分の属性がチョキの時　0(不利)
		if (this->type == Jan_Type::PAPER) return 1;    //自分の属性がパーの時　　1(有利)
		if (this->type == Jan_Type::ROCK) return 2;     //自分の属性がグーの時　　2(あいこ)
		break;

	case Jan_Type::SCISSORS:     //チョキの時

		if (this->type == Jan_Type::PAPER) return 0;    //自分の属性がパーの時　0(不利)
		if (this->type == Jan_Type::ROCK) return 1;     //自分の属性がグーの時　1(有利)
		if (this->type == Jan_Type::SCISSORS) return 2; //自分の属性がチョキの時　2(あいこ)
		break;

	case Jan_Type::PAPER:        //パーの時

		if (this->type == Jan_Type::ROCK) return 0;     //自分の属性がグーの時　0(不利)
		if (this->type == Jan_Type::SCISSORS) return 1; //自分の属性がチョキの時　1(有利)
		if (this->type == Jan_Type::PAPER) return 2;    //自分の属性がパーの時　2(あいこ)
		break;

	default:
		break;
	}

	return false;
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

