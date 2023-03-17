#pragma once
#include "AbstractScene.h"
#include"Enemy_07.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_07_FLOOR 10         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage07 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage07(const Player* player = nullptr);

	~Scene_Stage07();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Draw_Janken() const;              //����񂯂�`��

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_07* obj_enemy;            //�G

	bool janken_flag = false;       //�ڐG������񂯂�t���O


private:      //�摜�Ȃ�
	int image_back;        //�w�i
	int image_spotlight;   //�X�|�b�g���C�g
};

