#include"DxLib.h"
#include"GameData.h"

unsigned int GameData::g_score;       //�X�R�A�i�Q�[���v���C�������ƕێ��j
unsigned int GameData::total_time;    //��������

//������
void GameData::Init_Data()
{
	g_score = 0;
	total_time = 0;
}

//�X�R�A���Z
void GameData::Add_Score(unsigned int score)
{
	if (score < 0) return;
	g_score += score;
}

unsigned int GameData::Get_Score() 
{
	return g_score;
}