#pragma once

enum class SE_JANKEN
{
	JANKEN_PROGRESS,   //����񂯂�

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
	const SE_JANKEN se_type;   //�Đ����鉹�̎��
	int play_se;               //�Đ����鉹
	int play_time;             //�Đ�����
	int time_count;            //time
};
