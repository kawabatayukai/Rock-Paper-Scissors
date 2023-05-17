#pragma once
#include "AbstractScene.h"
#include"Enemy_10.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_10_FLOOR 16         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage10 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage10(const Player* player = nullptr);

	~Scene_Stage10();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Update_Janken();                  //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_10* obj_enemy;            //�G

	Jangeki_Reflection* reflection;

	bool janken_flag = false;       //�ڐG������񂯂�t���O

	int bgm[4];
};

