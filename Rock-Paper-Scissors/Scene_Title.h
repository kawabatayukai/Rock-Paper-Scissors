#pragma once
#include"AbstractScene.h"

//�^�C�g���V�[��
class TitleScene : public AbstractScene
{
public:
	//�R���X�g���N�^
	TitleScene();

	~TitleScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
};