#pragma once

//�f�[�^��ێ�����
class GameData
{
public:

	//������
	static void Init_Data();

	//�X�R�A���Z
	static void Add_Score(unsigned int score);

	static unsigned int Get_Score() ;

private:
	GameData();     //�I�u�W�F�N�g�͍��Ȃ�

	static unsigned int g_score;       //�X�R�A�i�Q�[���v���C�������ƕێ��j
	static unsigned int total_time;    //��������
};