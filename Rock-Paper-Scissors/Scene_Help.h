#pragma once
#include"AbstractScene.h"

//�w���v�V�[��
class HelpScene : public AbstractScene
{
private:
	int HelpImage = 0;
	int HelpImage1;
public:
	//�R���X�g���N�^
	HelpScene();

	~HelpScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
};