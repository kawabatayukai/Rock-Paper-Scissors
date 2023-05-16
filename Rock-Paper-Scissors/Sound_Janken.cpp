#include "Sound_Janken.h"
#include"DxLib.h"

Sound_Janken::Sound_Janken(const SE_JANKEN& se_type)
	:se_type(se_type), play_se(0), play_time(0), time_count(0)
{
	switch (se_type)
	{
	case SE_JANKEN::JANKEN_PROGRESS:
		play_se = LoadSoundMem("Sound/Janken/janken_roll.wav");

	case SE_JANKEN::JANKEN_WIN:
		play_se = LoadSoundMem("");
		break;

	case SE_JANKEN::JANKEN_LOSE:
		play_se = LoadSoundMem("");
		break;

	default:
		break;
	}
}

Sound_Janken::~Sound_Janken()
{
}

//Update
void Sound_Janken::Play()
{
	if (CheckSoundMem(play_se) == 0)
		PlaySoundMem(play_se, DX_PLAYTYPE_BACK);

	time_count++;
}

bool Sound_Janken::CheckPlayEnd()
{
	if (time_count >= play_time) return true;

	return false;
}