#pragma once

//プレイヤーエフェクト
class Effect_Player
{
public:
	Effect_Player(const float& x = 0.f, const float& y = 0.f);
	~Effect_Player();

	void Update();
	void Draw() const;
	void Draw_Back() const;   //描画背面
	void Draw_Front() const;  //描画前面

	//プレイヤーの座標
	void SetPlayerLocation(const float& x = 0.f, const float& y = 0.f);

	//削除 エフェクトが終了していればtrue
	bool IsEffectFinished();

private:
	float effect_x;
	float effect_y;

	int* image_effect;   //画像
	int index_effect;    //配列操作
	const int max_index; //画像最大数
	int frame_count;     //フレームカウンター

	//se
	int se_rec;       //変身
};