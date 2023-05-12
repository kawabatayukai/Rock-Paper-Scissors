#pragma once

//‚¶‚á‚ñŒ‚SE‚Ìí—Ş
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
	const SE_JAN se_type;      //Ä¶‚·‚é‰¹‚Ìí—Ş
	int play_se;               //Ä¶‚·‚é‰¹
	int play_time;             //Ä¶ŠÔ
	int time_count;            //time

	static int se_win_player;
	static int se_win_enemy;
};