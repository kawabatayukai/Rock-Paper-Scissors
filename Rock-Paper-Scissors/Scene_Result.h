#pragma once
#include "AbstractScene.h"

class Scene_Result : public AbstractScene
{
public:
	/*�R���X�g���N�^*/
	virtual ~Scene_Result() {};

	char name[11];

	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;
};

