#pragma once
#include "AbstractScene.h"
#include"Enemy_06.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_06_FLOOR 16         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage06 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage06(const Player* player = nullptr);

	~Scene_Stage06();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Update_Janken();                  //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_06* obj_enemy;            //�G

	bool janken_flag = false;       //�ڐG������񂯂�t���O
};

