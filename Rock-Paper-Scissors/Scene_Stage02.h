#pragma once
#include "AbstractScene.h"
#include"Enemy_02.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"


#define STAGE_02_FLOOR 3         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage02 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage02(const Player* player = nullptr);

	~Scene_Stage02();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	              //����񂯂�X�V�E��������
	void Draw_Janken() const;              //����񂯂�`��

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j
	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Enemy_02* obj_enemy;            //�G
	

private:      //�摜�Ȃ�
	int image_back;        //�w�i
	int hp = 50;//����HP(�����Â���)
	int  attack_pattern = 0;      //�U���p�^�[���ϐ�
	int STAGE02_BGM;
	int bgm;
};

