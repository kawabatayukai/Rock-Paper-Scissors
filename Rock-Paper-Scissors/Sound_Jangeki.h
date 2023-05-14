#pragma once

//�����SE�̎��
enum class SE_JAN
{
	PLAYER_WIN,  
	ENEMY_WIN,   
	ONEMORE,    //(������)
	HIT_JAN,    //������
	FIRE_JAN,   //����񌂔���
};

class Sound_Jangeki
{
public:
	Sound_Jangeki(SE_JAN se_type);
	Sound_Jangeki(Sound_Jangeki&& obj_sj) noexcept; //move �R���X�g���N�^
	Sound_Jangeki(const Sound_Jangeki& obj_sj);     //copy �R���X�g���N�^

	~Sound_Jangeki();

	//������Z�q(=)�̃I�[�o�[���[�h
	Sound_Jangeki& operator=(const Sound_Jangeki& obj_sj);

	void Play();
	bool CheckPlayEnd();

private:
	const SE_JAN se_type;      //�Đ����鉹�̎��
	int play_se;               //�Đ����鉹
	int play_time;             //�Đ�����
	int time_count;            //time
};
