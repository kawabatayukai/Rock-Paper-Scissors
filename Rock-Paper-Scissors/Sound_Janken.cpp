#include "Sound_Janken.h"
#include"DxLib.h"

namespace SE_TIME_JANKEN
{
	const int JAN_WIN = 108;
	const int JAN_LOSE = 120;
	const int JAN_AIKO = 60;
}

Sound_Janken::Sound_Janken(const SE_JANKEN& se_type)
	:se_type(se_type), play_se(0), play_time(0), time_count(0)
{
	using namespace SE_TIME_JANKEN;

	switch (se_type)
	{
	case SE_JANKEN::JANKEN_PROGRESS:
		play_se = LoadSoundMem("Sound/Janken/janken_roll.wav");
		break;

	case SE_JANKEN::JANKEN_WIN:
		play_se = LoadSoundMem("Sound/Janken/Janken_Win.wav");
		play_time = JAN_WIN;
		break;

	case SE_JANKEN::JANKEN_LOSE:
		play_se = LoadSoundMem("Sound/Janken/Janken_Lose.wav");
		play_time = JAN_LOSE;
		break;

	case SE_JANKEN::JANKEN_AIKO:
		play_se = LoadSoundMem("Sound/Janken/Janken_Aiko.wav");
		play_time = JAN_AIKO;
		break;

	default:
		break;
	}

	PlaySoundMem(play_se, DX_PLAYTYPE_BACK);
}

Sound_Janken::~Sound_Janken()
{
	StopSoundMem(play_se);
}

//Update
void Sound_Janken::Play()
{
	time_count++;
}

bool Sound_Janken::CheckPlayEnd()
{
	if (time_count >= play_time) return true;

	return false;
}