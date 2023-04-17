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
	void SetType(Jan_Type type);                 //�����ύX

	void SetHP(int damage);         //�_���[�W���󂯂�

	//HP�񕜁i���� : �񕜗ʁj
	void Recover_HP(const unsigned int recovery);

	//�ǐՑΏۂ̍��W���Z�b�g�@ ��{�v���C���[
	void SetPlayerLocation(const float player_x, const float player_y);

	void SetPlayerDirection(const int player_dir);

protected:
	Jan_Type e_type;         //�����i�O�[�@�`���L�@�p�[�@�̂����ꂩ�j
	int image = 0;           //�摜
	

	float player_x = 0.0f;   //�v���C���[�̍��W
	float player_y = 0.0f;   //�v���C���[�̍��W
};

