#pragma once
#include "AbstractScene.h"
#include"Floor.h"
#include"Player.h"
#include"Janken.h"
#include"EnemyBase.h"
#include"Effect_Jangeki.h"
#include"Effect_Enemy.h"
#include"Jangeki_reflection.h"
#include"Sound_Jangeki.h"
#include"Enemy_Death.h"

//�X�e�[�W�̃x�[�X
class Stage_Base : public AbstractScene
{
private:
	int typeImage[3];
public:
	Stage_Base();
	~Stage_Base();

	//UI�`��
	void DrawUI(Jan_Type type, int hp) const;

	//�G�̏��UI�`��
	void DrawUI_ON_Enemy(const EnemyBase* enemy) const;

	//���E�ǂ̏����@�@STAGE_XX_FLOOR ��������
	void Init_Floor(const int floor_MAX);

	//���E�ǂƂ̂����蔻��
	void HitCtrl_Floor(CharaBase* character, const int floor_MAX);


	//"�ڐG������񂯂�"����   player(�����P�Ԗځ@�̏��s���ʂ�Ԃ�)
	Jan_Result Get_JankenResult(Jan_Type player, Jan_Type enemy);

	//�G�ƃv���C���[�̓����蔻�聨�ڐG����񂯂񏈗�    �G�ւ̃|�C���^�A"this" ��������
	void Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr, int my_StageNum = 0);

	//����񌂃q�b�g���G�t�F�N�g ����
	void Effect_Update_HitJangeki(const EnemyBase* enemy, const Jangeki_Reflection* ref = nullptr);

	//����񌂃q�b�g���G�t�F�N�g �`��
	void Effect_Draw_HitJangeki() const;

	//���S������
	void Update_DeathEnemy();

	//���S���`��
	void Draw_DeathEnemy() const;

	//���S���o�I���`�F�b�N
	bool IsEnd_DeathEnemy();
	void GetStage09IsClear(bool isclear);

	//����񂯂�`��
	void Draw_Janken() const;

	void Draw_JankenStart() const;         //����񂯂�J�n����

	virtual void AfterJanken_WIN();        //����񂯂�I����̋����i�v���C���[�����j
	virtual void AfterJanken_LOSE();       //����񂯂�I����̋����i�v���C���[�����j

	//����񂯂�̏�Ԏ擾
	Jan_State GetJanState() const;

protected:
	Player* obj_player = nullptr;             //�v���C���[
	Floor** obj_floor = nullptr;              //���E��
	Janken* obj_janken = nullptr;             //����񂯂�p

private:
	short nhit_time = 0;                      //�Փ˔���Ȃ�����

	static int font;         //����(WIN or LOSE or ONEMORE) �p�t�H���g 

	Jan_State j_state = Jan_State::BEFORE;    //����񂯂�̏��

	unsigned short blackout_time;             //�Ó]���ԁi�ڐG���㉉�o�j

	Effect_Jangeki** obj_effect;              //�G�t�F�N�g�i�����hit�j

	Jan_Type Prev_EnemyType;                  //�G�̑����ω��O�̑���
	Effect_Enemy* obj_effectEnemy;            //�G�t�F�N�g�i�����ω�s�j

	int image_circle[3];                      //���v�p�~
	int image_clock;                          //���v
	int image_clockhand;                      //���v�̐j
	int image_clockchar;                      //���v�̕�����
	static int font_score;                    //Score�`��p�t�H���g

	Sound_Jangeki** obj_sejan;                //SE

	Enemy_Death* obj_death;                   //���S���ɐ�������
	bool stage09_isclear = false;
};

