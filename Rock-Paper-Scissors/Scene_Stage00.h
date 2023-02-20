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

	void Update_Janken();                  //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_00* obj_enemy;            //�G

	bool janken_flag = false;       //�ڐG������񂯂�t���O

	//test
	int setumei;  //�����摜
};

