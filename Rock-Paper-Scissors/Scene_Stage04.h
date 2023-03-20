#pragma once
#include "AbstractScene.h"
#include"Enemy_04.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_04_FLOOR 16         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage04 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage04(const Player* player = nullptr);

	~Scene_Stage04();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j

	int back_image;

private:
	Enemy_04* obj_enemy;            //�G

	
};

