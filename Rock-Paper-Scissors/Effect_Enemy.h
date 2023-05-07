#pragma once
#include"Jangeki_Base.h"

//�����ω�
class Effect_Enemy
{
public:
	Effect_Enemy(const float& x, const float& y, Jan_Type enemyType = Jan_Type::ROCK);
	~Effect_Enemy();

	void Update();
	void Draw() const;

	//Enemy�̍��W
	void SetEnemyLocation(const float& x = 0.f, const float& y = 0.f);

	//�폜 �G�t�F�N�g���I�����Ă����true
	bool IsEffectFinished();

private:
	float effect_x;
	float effect_y;

	int* image_effect;   //�摜
	int index_effect;    //�z�񑀍�
	const int max_index; //�摜�ő吔
	int frame_count;     //�t���[���J�E���^�[
};
