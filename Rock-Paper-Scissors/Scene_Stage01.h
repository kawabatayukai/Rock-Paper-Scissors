#pragma once
#include "AbstractScene.h"
#include"Enemy_01.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_01_FLOOR 5         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage01 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage01(const Player* player = nullptr);

	~Scene_Stage01();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void Update_Janken();                  //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

private:
	Enemy_01* obj_enemy;            //�G

	bool janken_flag = false;       //�ڐG������񂯂�t���O
};

