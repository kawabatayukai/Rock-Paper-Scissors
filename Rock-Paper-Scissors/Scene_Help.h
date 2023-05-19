#pragma once
#include"AbstractScene.h"

//�w���v�V�[��
class HelpScene : public AbstractScene
{	
public:
	//�R���X�g���N�^
	HelpScene();

	~HelpScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX

private:
	int HelpImage = 0;
	static int font_help;
};