#pragma once
#include "AbstractScene.h"

//�Q�[���N���A
class GameClearScene : public AbstractScene
{
public:
	GameClearScene(int Next);                      //�R���X�g���N�^
	~GameClearScene();                     //�f�X�g���N�^

	void Update() override;                //�X�V
	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	int Next;
};

