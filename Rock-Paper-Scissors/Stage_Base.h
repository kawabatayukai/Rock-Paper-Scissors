#pragma once
#include "AbstractScene.h"
#include"Floor.h"
#include"Player.h"
#include"Janken.h"
#include"EnemyBase.h"

//�X�e�[�W�̃x�[�X
class Stage_Base : public AbstractScene
{
private:
	int typeImage[3];
	int hpImage;
public:
	Stage_Base();
	~Stage_Base();

	//UI�`��
	void DrawUI(Jan_Type type ,int hp) const;

	//���E�ǂ̏����@�@STAGE_XX_FLOOR ��������
	void Init_Floor(const int floor_MAX);

	//���E�ǂƂ̂����蔻��
	void HitCtrl_Floor(CharaBase* character, const int floor_MAX);


	//"�ڐG������񂯂�"����   player(�����P�Ԗځ@�̏��s���ʂ�Ԃ�)
	Jan_Result Get_JankenResult(Jan_Type player, Jan_Type enemy);

	//�G�ƃv���C���[�̓����蔻�聨�ڐG����񂯂񏈗�
	void Touch_Janken(const EnemyBase* enemy);
	//����񂯂�J�n�t���O�擾
	bool GetJanStartFlag() const { return j_start_flag; }

protected:
	Player* obj_player = nullptr;             //�v���C���[
	Floor** obj_floor = nullptr;              //���E��

	Janken* obj_janken = nullptr;             //����񂯂�p

private:
	short nhit_time = 0;                      //�Փ˔���Ȃ�����
	bool j_start_flag = false;                //����񂯂�J�n�t���O
};

