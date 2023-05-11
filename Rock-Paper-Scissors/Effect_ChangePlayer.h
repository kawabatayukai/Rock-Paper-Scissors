#pragma once
#include"Jangeki_Base.h"

//�v���C���[�G�t�F�N�g
class Effect_ChangePlayer
{
public:
	Effect_ChangePlayer(Jan_Type type, const float& x = 0.f, const float& y = 0.f);
	~Effect_ChangePlayer();

	void Update();
	void Draw() const;
	void Draw_Back() const;   //�`��w��
	void Draw_Front() const;  //�`��O��

	//�v���C���[�̍��W
	void SetPlayerLocation(const float& x = 0.f, const float& y = 0.f);

	//�폜 �G�t�F�N�g���I�����Ă����true
	bool IsEffectFinished();

private:
	float effect_x;
	float effect_y;

	int* image_effect;   //�摜
	int index_effect;    //�z�񑀍�
	const int max_index; //�摜�ő吔
	int frame_count;     //�t���[���J�E���^�[

	int se_change;       //�ϐg
};