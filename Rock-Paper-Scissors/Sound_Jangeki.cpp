#include"DxLib.h"
#include"Sound_Jangeki.h"

int Sound_Jangeki::se_win_player;
int Sound_Jangeki::se_win_enemy;

//seの再生時間
namespace SE_TIME
{
	const int PLAYER_WIN = 80;
	const int ENEMY_WIN = 90;
}

//コンストラクタ
Sound_Jangeki::Sound_Jangeki(SE_JAN se_type) :se_type(se_type), play_time(0), time_count(0)
{
	switch (se_type)
	{
	case SE_JAN::PLAYER_WIN:
		play_se = se_win_player;
		play_time = SE_TIME::PLAYER_WIN;
		break;

	case SE_JAN::ENEMY_WIN:
		play_se = se_win_enemy;
		play_time = SE_TIME::ENEMY_WIN;
		break;
	default:
		break;
	}

	
}

//デストラクタ
Sound_Jangeki::~Sound_Jangeki()
{

}

void Sound_Jangeki::LoadSounds()
{
	se_win_player = LoadSoundMem("Sound/Jangeki/win1.wav");
	se_win_enemy = LoadSoundMem("Sound/Jangeki/win2.wav");
}
void Sound_Jangeki::DeleteSounds()
{
	DeleteSoundMem(se_win_player);
	DeleteSoundMem(se_win_enemy);
}

//Update
void Sound_Jangeki::Play()
{
	if (CheckSoundMem(play_se) == 0) PlaySoundMem(play_se, DX_PLAYTYPE_BACK);

	time_count++;
}

bool Sound_Jangeki::CheckPlayEnd()
{
	if (time_count >= play_time) return true;

	return false;
}