#pragma once

/** じゃん撃ではない **/


//エフェクトを発生させる(じゃん撃同士の衝突)
class Effect_Jangeki
{
public:
	Effect_Jangeki(float play_x, float play_y);
	~Effect_Jangeki();

	void Update();
	void Draw() const;

	bool Check_PlayEnd();          //再生終了 true

private:
	const float play_x;            //エフェクト再生座標ｘ
	const float play_y;            //エフェクト再生座標ｙ

	unsigned int frame_count;      //フレームカウンタ
	unsigned int index_effect;     //配列操作
	unsigned int index_max;        //画像最大数
	
	int* image_effect;             //エフェクト画像

	bool finish_effect;            //エフェクト完了
};
