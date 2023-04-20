#pragma once
#include "AbstractScene.h"
#include"Enemy_05.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"
#include"Jangeki_reflection.h"
#define STAGE_05_FLOOR 8         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage05 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage05(const Player* player = nullptr);

	~Scene_Stage05();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j




private:
	Enemy_05* obj_enemy;            //�G
	MobEnemy_05** mob;				//�G���G

	int Back_image;					//�w�i�摜

	Jangeki_Reflection* reflection;
};

