#pragma once
#include "AbstractScene.h"
#include"Enemy_00.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_00_FLOOR 7         //���E�ǂ̍��v���@�@�@���A�ǂ�ǉ�����Ƃ��ɑ��₷

//0�X�e�[�W
class Scene_Stage00 : public Stage_Base
{
public:
	//�R���X�g���N�^      �O�̃X�e�[�W�̃v���C���[���������p��
	Scene_Stage00(const Player* player = nullptr);

	~Scene_Stage00();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:

	short frame_count;    //�t���[���J�E���g

	int player_image;
	int player_all;

	int enemy_02;
	int enemy_03;
	int enemy_04;
	int enemy_05;
	int enemy_06;
	int enemy_07;
	int enemy_08;
	int enemy_09;
	int enemy_10;

	int enemy_05_mob;

	int hand_rock;
	int hand_scissors;
	int hand_paper;
};

