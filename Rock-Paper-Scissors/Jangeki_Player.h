#pragma once
#include"Jangeki_Base.h"

//���X�ɑ傫���Ȃ�
class Jangeki_Player : public Jangeki_Base
{
public:
	//�R���X�g���N�^
	Jangeki_Player(float x, float y, float r, float speed, Jan_Type type);

	//(�p�x�t��)
	Jangeki_Player(float x, float y, float r, float speed, double angle, Jan_Type type);

	~Jangeki_Player();             //�f�X�g���N�^
	 
	void Update() override;         //�X�V
	void Draw() const override;     //�`��

private:

	int image_jangeki[6];           //�摜�i�O�[or�`���Lor�p�[ �̂����ꂩ�j
	int index_jangeki;              //�z��Y��

	double rate_pct;                //�g�嗦(max100)

	unsigned short frame_count;     //�t���[���J�E���g

	int image_lightning;            //���I�Ȃ���
};