#pragma once

/** じゃん撃ではない **/


//エフェクトを発生させる(じゃん撃同士の衝突)
class Effect_Jangeki
{
public:
	Effect_Jangeki(float play_x, float play_y, int result_num = 0);
	~Effect_Jangeki();

	void Update();
	void Draw() const;

	bool Check_PlayEnd();          //再生終了 true

private:
	const float play_x;            //エフェクト再生座標ｘ
	const float play_y;            //エフェクト再生座標ｙ

	unsigned short frame_count;    //フレームカウント
	int* image_effect;             //画像
	int index_image;               //画像No
	unsigned int image_max;        //画像最大数

	bool play_end;                 //再生終了
};
