#pragma once
#include "AbstractScene.h"
#include"Enemy_03.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_03_FLOOR 12       //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage03 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage03(const Player* player = nullptr);

	~Scene_Stage03();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j

	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j

private:
	Enemy_03* obj_enemy;            //�G


	int stage = 0;//�w�i
	int GroundImages = 0; //�n��
	int BlockImages = 0; //�u���b�N
};

