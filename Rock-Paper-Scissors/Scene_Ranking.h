#pragma once
#include "AbstractScene.h"

class Scene_Ranking : public AbstractScene
{
	/*�R���X�g���N�^*/
	virtual ~Scene_Ranking() {};

	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;
};

