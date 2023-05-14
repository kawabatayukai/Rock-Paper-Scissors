#pragma once

//プレイヤーSEの種類
enum class SE_PLAYER
{
	RECOVERY,  //回復
	CHANGE,    //じゃん撃チェンジ
};

class Sound_Player
{
public:
	Sound_Player(const SE_PLAYER& se_type);
	~Sound_Player();

	void Play();
	bool CheckPlayEnd();

	static void LoadPlayerSound();
	static void DeletePlayerSound();

private:
	const SE_PLAYER se_type;   //再生する音の種類
	int play_se;               //再生する音
	int play_time;             //再生時間
	int time_count;            //time

	static int se_recovery;
	static int se_change;
};