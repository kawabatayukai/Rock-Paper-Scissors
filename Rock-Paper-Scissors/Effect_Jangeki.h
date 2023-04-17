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

private:
	const float play_x;            //エフェクト再生座標ｘ
	const float play_y;            //エフェクト再生座標ｙ

	unsigned short frame_count;    //フレームカウント
	int image_effect[10];          //画像
	int index_image;               //画像No
};
