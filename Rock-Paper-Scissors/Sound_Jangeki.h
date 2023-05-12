#pragma once

//�����SE�̎��
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
	const SE_JAN se_type;      //�Đ����鉹�̎��
	int play_se;               //�Đ����鉹
	int play_time;             //�Đ�����
	int time_count;            //time

	static int se_win_player;
	static int se_win_enemy;
};