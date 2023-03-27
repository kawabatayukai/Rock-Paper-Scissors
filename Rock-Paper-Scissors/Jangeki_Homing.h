#pragma once
#include"Jangeki_Base.h"

/**************************************************************************************/
/*�@�z�[�~���O����񌂂��g���Ƃ���Update�̑O�� SetTargetLocation(player x , player y) */
/**************************************************************************************/

//�z�[�~���O�����
class Jangeki_Homing : public Jangeki_Base
{
public:
	//�R���X�g���N�^  ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�^�C�v
	Jangeki_Homing(float x, float y, float r, float speed, Jan_Type type, bool ref = false);

	~Jangeki_Homing();

	virtual void Update() override;              //�X�V�@�I�[�o�[���C�h�i�Ē�`�j
	//void Draw() const override;        //�`��͊��N���X�̓��e�̂܂܂�ok


private:
	/* ���W�n�A�X�s�[�h�@�Ȃǂ̕ϐ���
	      ���N���X Jangeki_Base �� protected �̏�Ԃł���܂�   */


	double angle;             //�p�x
	int time_counter = 0;     //�ǐՎ��Ԃ��J�E���g
};