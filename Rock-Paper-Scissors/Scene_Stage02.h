#pragma once
#include "AbstractScene.h"
#include"Enemy_02.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_02_FLOOR 4         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage02 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage02(const Player* player = nullptr);

	~Scene_Stage02();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Update_Janken();                  //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_02* obj_enemy;            //�G
	bool janken_flag = false;       //�ڐG������񂯂�t���O

private:      //�摜�Ȃ�
	int image_back;        //�w�i
};

