#pragma once
#include"Jangeki_Base.h"

//�c�����ɕ��т��������
class Jangeki_Vertical : public Jangeki_Base
{
public:
	//�R���X�g���N�^  ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�ڎw�������W �@�@�@�^�C�v
	Jangeki_Vertical(float x, float y, float r, float speed, float goal_y, Jan_Type type);

	~Jangeki_Vertical();

	virtual void Update() override;              //�X�V�@�I�[�o�[���C�h�i�Ē�`�j


private:
	/* ���W�n�A�X�s�[�h�@�Ȃǂ̕ϐ���
		  ���N���X Jangeki_Base �� protected �̏�Ԃł���܂�   */

	float goal_y;
};