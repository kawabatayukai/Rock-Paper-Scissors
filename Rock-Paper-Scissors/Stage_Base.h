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
	int hpMax = 100;
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

	//�G�ƃv���C���[�̓����蔻�聨�ڐG����񂯂񏈗�    �G�ւ̃|�C���^�A"this" ��������
	void Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr);

	virtual void AfterJanken_WIN();        //����񂯂�I����̋����i�v���C���[�����j
	virtual void AfterJanken_LOSE();       //����񂯂�I����̋����i�v���C���[�����j

	//����񂯂�̏�Ԏ擾
	Jan_State GetJanState() const { return j_state; }

protected:
	Player* obj_player = nullptr;             //�v���C���[
	Floor** obj_floor = nullptr;              //���E��

	Janken* obj_janken = nullptr;             //����񂯂�p

private:
	short nhit_time = 0;                      //�Փ˔���Ȃ�����

	Jan_State j_state = Jan_State::BEFORE;    //����񂯂�̏��
};

