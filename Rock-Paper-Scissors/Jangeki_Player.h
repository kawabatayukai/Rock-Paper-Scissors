#pragma once
#include"Jangeki_Base.h"

//徐々に大きくなる
class Jangeki_Player : public Jangeki_Base
{
public:
	//コンストラクタ
	Jangeki_Player(float x, float y, float r, float speed, Jan_Type type);

	//(角度付き)
	Jangeki_Player(float x, float y, float r, float speed, double angle, Jan_Type type);

	~Jangeki_Player();             //デストラクタ
	 
	static void LoadJanImage();     //画像読み込み

	void Update() override;         //更新
	void Draw() const override;     //描画

	void Draw_Effect() const;       //貫通エフェクト描画

private:

	static int image_jangeki[3][6]; //画像（グーorチョキorパー のいずれか）
	int index_jangeki;              //配列添字

	double rate_pct;                //拡大率(max100)

	//--------------------  エフェクト  --------------------
	unsigned short frame_count;     //フレームカウント
	static int image_lightning[3];  //雷的なもの

	int index_effect;               //画像No
	int index_max;

	static int image_effects[3][12];//貫通時エフェクト
	double turn_effect;             //回転率
};