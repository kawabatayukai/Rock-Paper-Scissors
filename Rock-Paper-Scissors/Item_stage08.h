#pragma once
#include"Jangeki_Base.h"

//�A�C�e��
class Item_st8 : public Jangeki_Base
{
public:
	//�R���X�g���N�^  ���@�@�@�@���@
	Item_st8(float x, float y, float r);

	~Item_st8();

	virtual void Update() override;              //�X�V�@�I�[�o�[���C�h�i�Ē�`�j
	virtual void Draw() const override;

	
private:
	/* ���W�n�A�X�s�[�h�@�Ȃǂ̕ϐ���
		  ���N���X Jangeki_Base �� protected �̏�Ԃł���܂�   */
	int image;
};