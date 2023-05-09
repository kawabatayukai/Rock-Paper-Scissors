#pragma once
#include"Jangeki_Base.h"
#include"CharaBase.h"

/** じゃん撃ではない **/

//エフェクトを発生させる(じゃん撃同士の衝突)
class Effect_Jangeki
{
public:
	Effect_Jangeki(float play_x, float play_y, Jan_Type type = Jan_Type::PAPER, _CHAR_TYPE character = _CHAR_TYPE::PLAYER);
	~Effect_Jangeki();

	void Update();
	void Draw() const;

	bool Check_PlayEnd();          //再生終了 true

	//Characterの座標
	void SetCharacterLocation(const float& x = 0.f, const float& y = 0.f);

	_CHAR_TYPE GetCharacterType() const { return character; }

private:
	float play_x;            //エフェクト再生座標ｘ
	float play_y;            //エフェクト再生座標ｙ

	unsigned int frame_count;      //フレームカウンタ
	unsigned int index_effect;     //配列操作
	unsigned int index_max;        //画像最大数
	
	int* image_effect;             //エフェクト画像
	int image_sub;                 //サブエフェクト

	const _CHAR_TYPE character;

	bool finish_effect;            //エフェクト完了
};
