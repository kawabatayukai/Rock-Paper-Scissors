#pragma once
#include"AbstractScene.h"

//�^�C�g���V�[��
class EndScene : public AbstractScene
{
public:
	//�R���X�g���N�^
	EndScene();

	~EndScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX

private:
	int framecount ;  //�t���[��
	int GameState = 0;
	int WaitTime = 0;
	int PosY;
};
