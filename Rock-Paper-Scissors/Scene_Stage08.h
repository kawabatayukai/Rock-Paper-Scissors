#pragma once
#include "AbstractScene.h"
#include"Enemy_08.h"
#include"Enemy_Cannon.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"


#define STAGE_08_FLOOR  30        //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage08 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage08(const Player* player = nullptr);

	~Scene_Stage08();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j

private:
	int Back_image;
	Enemy_08* obj_enemy;            //�G
	Enemy_Cannon* obj_cannon;
	Enemy_Cannon** cannon;

	Jangeki_Base** Item;

	int damage;
	int bgm;

	bool Player_Janwin = false;
	bool item_ui = false;
	int count = 0;

};


