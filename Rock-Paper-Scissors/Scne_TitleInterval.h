#pragma once
#include "AbstractScene.h"

class Scne_TitleInterval : public AbstractScene
{
public:
	//�R���X�g���N�^
	Scne_TitleInterval();
	//�f�X�g���N�^
	~Scne_TitleInterval();

	void Update() override;
	void Draw() const override;

	//�V�[���̕ύX
	AbstractScene* ChangeScene() override;

private:
	int band[3];
};

