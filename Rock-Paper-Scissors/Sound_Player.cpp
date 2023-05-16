#include "Sound_Player.h"
#include"DxLib.h"

//se‚ÌÄ¶ŠÔ
namespace SE_TIME_PLAYER
{
	const int RECOVERY_P = 120;
	const int CHANGE_P = 60;
}

int Sound_Player::se_recovery;
int Sound_Player::se_change;

Sound_Player::Sound_Player(const SE_PLAYER& se_type)
	:se_type(se_type), play_se(0), play_time(0), time_count(0)
{
	switch (se_type)
	{
	case SE_PLAYER::RECOVERY:
		play_se = DuplicateSoundMem(se_recovery);
		play_time = SE_TIME_PLAYER::RECOVERY_P;
		break;

	case SE_PLAYER::CHANGE:
		play_se = DuplicateSoundMem(se_change);
		play_time = SE_TIME_PLAYER::CHANGE_P;
		break;

	default:
		break;
	}
}

Sound_Player::~Sound_Player()
{
	DeleteSoundMem(play_se);
}

void Sound_Player::Play()
{
	if (CheckSoundMem(play_se) == 0)
		PlaySoundMem(play_se, DX_PLAYTYPE_BACK);

	time_count++;
}

bool Sound_Player::CheckPlayEnd()
{
	if (time_count >= play_time) return true;
	return false;
}

//“Ç‚İ‚İ
void Sound_Player::LoadPlayerSound()
{
	se_recovery = LoadSoundMem("Sound/Player/kaihuku.wav");
	se_change = LoadSoundMem("Sound/Player/change2.wav");
}

//íœ
void Sound_Player::DeletePlayerSound()
{
	DeleteSoundMem(se_recovery);
	DeleteSoundMem(se_change);
}
