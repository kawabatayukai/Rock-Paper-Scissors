#include"DxLib.h"
#include"Sound_Jangeki.h"



//seの再生時間
namespace SE_TIME_JAN
{
	const int PLAYER_WIN = 80;
	const int ENEMY_WIN = 90;
	const int ONEMORE = 105;
	const int HIT_JANGEKI = 64;
	const int FIRE_JANGEKI = 17;
}

//コンストラクタ
Sound_Jangeki::Sound_Jangeki(SE_JAN se_type) :se_type(se_type),play_se(0),play_time(0),time_count(0)
{
	switch (se_type)
	{
	case SE_JAN::PLAYER_WIN:
		play_se = LoadSoundMem("Sound/Jangeki/win1.wav");
		play_time = SE_TIME_JAN::PLAYER_WIN;
		break;

	case SE_JAN::ENEMY_WIN:
		play_se = LoadSoundMem("Sound/Jangeki/win2.wav");
		play_time = SE_TIME_JAN::ENEMY_WIN;
		break;

	case SE_JAN::ONEMORE:
		play_se = LoadSoundMem("Sound/Jangeki/aiko.wav");
		play_time = SE_TIME_JAN::ONEMORE;
		break;

	case SE_JAN::HIT_JAN:
		play_se = LoadSoundMem("Sound/Jangeki/shoot.wav");
		play_time = SE_TIME_JAN::HIT_JANGEKI;
		break;

	case SE_JAN::FIRE_JAN:
		play_se = LoadSoundMem("Sound/Jangeki/jan_fire1.wav");
		play_time = SE_TIME_JAN::FIRE_JANGEKI;
		break;

	default:
		break;
	}
}

//move コンストラクタ
Sound_Jangeki::Sound_Jangeki(Sound_Jangeki&& obj_sj) noexcept
	:se_type(obj_sj.se_type), play_se(obj_sj.play_se), play_time(obj_sj.play_time), time_count(obj_sj.time_count)
{
	//右辺の値を左辺に
}

//copy コンストラクタ
Sound_Jangeki::Sound_Jangeki(const Sound_Jangeki& obj_sj)
	:se_type(obj_sj.se_type), play_se(obj_sj.play_se), play_time(obj_sj.play_time), time_count(obj_sj.time_count)
{
	//オブジェクトをコピーする
}

//デストラクタ
Sound_Jangeki::~Sound_Jangeki()
{
	DeleteSoundMem(play_se);
}

//代入演算子(=)のオーバーロード
Sound_Jangeki& Sound_Jangeki::operator=(const Sound_Jangeki& obj_sj)
{
	if (this == &obj_sj) return *this;

	play_se = obj_sj.play_se;
	play_time = obj_sj.play_time;
	time_count = obj_sj.time_count;

	return *this;
}

//Update
void Sound_Jangeki::Play()
{
	if (CheckSoundMem(play_se) == 0) 
		PlaySoundMem(play_se, DX_PLAYTYPE_BACK);

	time_count++;
}

bool Sound_Jangeki::CheckPlayEnd()
{
	if (time_count >= play_time) return true;

	return false;
}