#pragma once

//じゃんけんタイプ
enum class Jan_Type
{
	ROCK,        //ロック　　　（グー）
	SCISSORS,    //シザーズ　　（チョキ）
	PAPER,       //ペーパー　　（パー）

	NONE,        //無属性
};

//じゃんけんの結果
enum class Jan_Result
{
	LOSE,            //負け
	WIN,             //勝ち
	ONEMORE,         //あいこ
	_ERROR = 99      //エラー
};

//エフェクトの種類
enum class EFFECT_TYPE
{
	WIN,         //勝ち
	OFFSET,      //相殺

	_NO_EFFECT,  //エフェクトなし
};

//じゃん撃
class Jangeki_Base
{
public:
	//コンストラクタ  ｘ　　　　ｙ　　　半径　　スピード　　　タイプ      反射タイプか
	Jangeki_Base(float x, float y, float r, float speed, Jan_Type type, bool ref = false);

	//コンストラクタ（角度あり）
	Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type, bool ref = false);

	//デストラクタ
	~Jangeki_Base();

	//画像読み込み
	static void Input_Images(); 

	virtual void Update();                    //更新
	virtual void Draw() const;                //描画
	bool CheckScreenOut();                    //画面外にいるか　true:画面外　false:画面内

	//エフェクトを動作させる（全ての派生じゃん撃内・Updateで呼ぶ）引数：フレーム毎の拡大量
	void Update_Effect(double fp_rate = 5.0);

	/* 
	   *********  引数のじゃん撃属性と自分の属性を比較  *********  
	   ・自分の属性が不利（例　自分：グー　引数：パー）　　return 0
	   ・自分の属性が有利（例　自分：グー　引数：チョキ）　return 1
	   ・　　　あいこ　　（例　自分：グー　引数：グー）　　return 2
	*/
	int CheckAdvantage(Jangeki_Base* jangeki);

	float GetX() const { return x; }           //ｘ座標取得
	float GetY() const { return y; }           //ｙ座標取得
	float GetR() const { return r; }           //半径取得
	float GetSpeed() const { return speed; }   //スピード取得
	Jan_Type GetType() const { return type; }  //属性取得

	//タイプ取得（グー,チョキ,パー）
	Jan_Type GeteEnemyType() const { return type; }

	//追跡対象の座標をセット　プレイヤーの座標を取りたいときに使えます
	void SetTargetLocation(const float target_x, const float target_y);

	//じゃん撃同士の当たり判定
	bool Hit_Jangeki(const Jangeki_Base* jangeki);

	//円形の当たり判定
	bool Hit_CircleCircle(float c_x, float c_y, float c_r) const;

	//発動するエフェクトの種類（player）
	EFFECT_TYPE GetPlayerEffect() const { return player_effect; }

	//あいこ相殺エフェクト（player側で行う）
	void Update_OffsetEffect();

	//あいこ相殺エフェクト描画（player側で行う）
	void Draw_OffsetEffect() const;

	float GetOffsetEffect_X() const { return effect_x; }
	float GetOffsetEffect_Y() const { return effect_y; }

protected:

	float x;            //ｘ
	float y;            //ｙ
	float r;            //半径
	float speed;        //スピード
	float speed_y = 0;  //ｙ座標スピード

	static int image[3];          //じゃん撃画像
	static int image_smoke[3][4]; //スモークなエフェクト
	short smoke_index;            //エフェクトアニメーション用

	double rate_pct;    //拡大率
	double rate_turn;   //回転率

	//反射専用
	int reflection_image[3];
	bool refrection;    //trueの時、自身は反射である

	Jan_Type type;      //タイプ　グーorチョキorパー


	float target_x = 0; //対象のｘ座標
	float target_y = 0; //対象のｙ座標


	int index_effect =0;              //画像No
	int index_max = 0;

	static int image_effects[3][12];  //貫通時エフェクト
	double turn_effect =0.0;          //回転率


	EFFECT_TYPE player_effect;   //player側じゃん撃が発動するエフェクト
	EFFECT_TYPE enemy_effect;    //enemy側じゃん撃が発動するエフェクト

	float effect_x;              //エフェクト描画ｘ（あいこ）
	float effect_y;              //エフェクト描画ｙ（あいこ）
};
