#pragma once
#include "AbstractScene.h"

//�Q�[���I�[�o�[
class GameOverScene : public AbstractScene
{
public:
	GameOverScene();                      //�R���X�g���N�^
	~GameOverScene();                     //�f�X�g���N�^

	void Update() override;                //�X�V
	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX
};
