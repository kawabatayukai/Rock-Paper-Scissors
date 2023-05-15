#pragma once

enum class SE_JANKEN
{
	JANKEN_PROGRESS,   //じゃんけん中

	JANKEN_WIN,
	JANKEN_LOSE,
};

class Sound_Janken
{
public:
	Sound_Janken(const SE_JANKEN& se_type);
	~Sound_Janken();

	void Play();
	bool CheckPlayEnd();

private:
	const SE_JANKEN se_type;   //再生する音の種類
	int play_se;               //再生する音
	int play_time;             //再生時間
	int time_count;            //time
};
