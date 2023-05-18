#pragma once

enum class SE_JANKEN
{
	JANKEN_PROGRESS,   //‚¶‚á‚ñ‚¯‚ñ’†

	JANKEN_WIN,
	JANKEN_LOSE,
	JANKEN_AIKO,
};

class Sound_Janken
{
public:
	Sound_Janken(const SE_JANKEN& se_type);
	~Sound_Janken();

	void Play();
	bool CheckPlayEnd();

private:
	const SE_JANKEN se_type;   //Ä¶‚·‚é‰¹‚Ìí—Ş
	int play_se;               //Ä¶‚·‚é‰¹
	int play_time;             //Ä¶ŠÔ
	int time_count;            //time
};
