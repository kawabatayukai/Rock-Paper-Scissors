#pragma once

//じゃん撃SEの種類
enum class SE_JAN
{
	PLAYER_WIN,  
	ENEMY_WIN,   
	ONEMORE,    //(あいこ)
	HIT_JAN,    //当たり
	FIRE_JAN,   //じゃん撃発射
};

class Sound_Jangeki
{
public:
	Sound_Jangeki(SE_JAN se_type);
	Sound_Jangeki(Sound_Jangeki&& obj_sj) noexcept; //move コンストラクタ
	Sound_Jangeki(const Sound_Jangeki& obj_sj);     //copy コンストラクタ

	~Sound_Jangeki();

	//代入演算子(=)のオーバーロード
	Sound_Jangeki& operator=(const Sound_Jangeki& obj_sj);

	void Play();
	bool CheckPlayEnd();

private:
	const SE_JAN se_type;      //再生する音の種類
	int play_se;               //再生する音
	int play_time;             //再生時間
	int time_count;            //time
};
