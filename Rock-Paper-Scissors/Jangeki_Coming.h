#pragma once
#include "Jangeki_Base.h"

//�X�s�[�h���ω�����W������
class Jangeki_Coming : public Jangeki_Base
{
private:
	float player_x;
	float player_y;
	float rad;

public:
	//�R���X�g���N�^
	Jangeki_Coming(float x, float y, float r, float speed, Jan_Type type, float p_x, float p_y);
	~Jangeki_Coming();

	virtual void Update()override;
};