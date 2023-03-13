#pragma once
#include "AbstractScene.h"
#include"Enemy_05.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

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

	void Update_Janken();                  //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_05* obj_enemy;            //�G

	bool janken_flag = false;       //�ڐG������񂯂�t���O

	int Back_image;					//�w�i�摜
};

