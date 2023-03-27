#pragma once
#include "AbstractScene.h"
#include"Enemy_09.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"
#include"Jangeki_reflection.h"

#define STAGE_09_FLOOR 11         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage09 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage09(const Player* player = nullptr);

	~Scene_Stage09();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	void Draw_Janken() const;              //����񂯂�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void AfterJanken_WIN()  override;      //����񂯂�I����̋����i�v���C���[�����j
	void AfterJanken_LOSE() override;      //����񂯂�I����̋����i�v���C���[�����j
	
bool Rflg = false; //���˂���񌂔��ʗp
private:
	Enemy_09* obj_enemy;            //�G
	Jangeki_Reflection* reflection;

	int stageimage;


};

