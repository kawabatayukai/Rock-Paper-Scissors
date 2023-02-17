#pragma once

//じゃんけんタイプ
enum class Jan_Type
{
	ROCK,        //ロック　　　（グー）
	SCISSORS,    //シザーズ　　（チョキ）
	PAPER,       //ペーパー　　（パー）
};

//じゃんけんの結果
enum class Jan_Result
{
	LOSE,            //負け
	WIN,             //勝ち
	ONEMORE,         //あいこ
	_ERROR = 99      //エラー
};

//じゃん撃
class Jangeki_Base
{
public:
	//コンストラクタ  ｘ　　　　ｙ　　　半径　　スピード　　　タイプ
	Jangeki_Base(float x, float y, float r, float speed, Jan_Type type);

	//コンストラクタ（角度あり）
	Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type);

	//デストラクタ
	~Jangeki_Base();

	void Update();                    //更新
	void Draw() const;                //描画
	bool CheckScreenOut();            //画面外にいるか　true:画面外　false:画面内

	/* 
	   *********  引数のじゃん撃属性と自分の属性を比較  *********  
	   ・自分の属性が不利（例　自分：グー　引数：パー）　　return 0
	   ・自分の属性が有利（例　自分：グー　引数：チョキ）　return 1
	   ・　　　あいこ　　（例　自分：グー　引数：グー）　　return 2
	*/
	int CheckAdvantage(const Jangeki_Base* jangeki);

	float GetX() const { return x; }  //ｘ座標取得
	float GetY() const { return y; }  //ｙ座標取得
	float GetR() const { return r; }  //半径取得
	Jan_Type GetType() const { return type; }  //属性取得

	//タイプ取得（グー,チョキ,パー）
	Jan_Type GeteEnemyType() const { return type; }

	//じゃん撃同士の当たり判定
	bool Hit_Jangeki(const Jangeki_Base* jangeki);

	//円形の当たり判定
	bool Hit_CircleCircle(float c_x, float c_y, float c_r) const;

protected:

	float x;     //ｘ
	float y;     //ｙ
	float r;     //半径
	float speed; //スピード
	float speed_y = 0; //ｙ座標スピード

	int image[3];

	Jan_Type type;   //タイプ　グーorチョキorパー
};
