#pragma once

//じゃん撃SEの種類
enum class SE_JAN
{
	PLAYER_WIN,  
	ENEMY_WIN,   
};

class Sound_Jangeki
{
public:
	Sound_Jangeki(SE_JAN se_type);
	~Sound_Jangeki();

	static void LoadSounds();
	static void DeleteSounds();

	void Play();
	bool CheckPlayEnd();

private:
	const SE_JAN se_type;      //再生する音の種類
	int play_se;               //再生する音
	int play_time;             //再生時間
	int time_count;            //time

	static int se_win_player;
	static int se_win_enemy;
};