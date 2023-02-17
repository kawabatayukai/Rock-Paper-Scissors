#pragma once
#include "CharaBase.h"
#include"Jangeki_Base.h"

//�G�L�����̊��N���X  CharaBase���p��
class EnemyBase : public CharaBase
{
public:
	//�R���X�g���N�^  ���W�A���E�����E������ݒ�
	EnemyBase(float x, float y, float w, float h, Jan_Type type);

	~EnemyBase();                   //�f�X�g���N�^

	virtual void Update() = 0;      //�X�V�i��`�͔h���N���X���Łj
	virtual void Draw() const = 0;  //�`��i��`�͔h���N���X���Łj

	Jan_Type GetType() const { return e_type; }  //�����擾
	void SetHP(int damage);

protected:
	Jan_Type e_type;         //�����i�O�[�@�`���L�@�p�[�@�̂����ꂩ�j
	int image = 0;
};

