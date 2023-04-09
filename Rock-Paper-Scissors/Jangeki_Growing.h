#pragma once
#include"Jangeki_Base.h"

//徐々に大きくなる
class Jangeki_Growing : public Jangeki_Base
{
public:
	//コンストラクタ
	Jangeki_Growing(float x, float y, float r, float speed, Jan_Type type);

	//(角度付き)
	Jangeki_Growing(float x, float y, float r, float speed, double angle, Jan_Type type);

	~Jangeki_Growing();             //デストラクタ
	 
	void Update() override;         //更新
	void Draw() const override;     //描画

private:

	int image_jangeki[6];           //画像（グーorチョキorパー のいずれか）
	int index_jangeki;              //配列添字

	double rate_pct;                //拡大率(max100)

	unsigned short frame_count;     //フレームカウント
};