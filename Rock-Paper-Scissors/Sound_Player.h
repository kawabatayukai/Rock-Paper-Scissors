#pragma once

//�v���C���[SE�̎��
enum class SE_PLAYER
{
	RECOVERY,  //��
	CHANGE,    //����񌂃`�F���W
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
	const SE_PLAYER se_type;   //�Đ����鉹�̎��
	int play_se;               //�Đ����鉹
	int play_time;             //�Đ�����
	int time_count;            //time

	static int se_recovery;
	static int se_change;
};