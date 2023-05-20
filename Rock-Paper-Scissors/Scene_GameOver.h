#pragma once
#include "AbstractScene.h"

//�Q�[���I�[�o�[
class GameOverScene : public AbstractScene
{
public:
	GameOverScene(int again);                      //�R���X�g���N�^
	GameOverScene();

	~GameOverScene();                     //�f�X�g���N�^

	void Update() override;                //�X�V
	void Draw() const override;            //�`��
	void GameOverPlay();

	AbstractScene* ChangeScene() override; //�V�[���̕ύX
private:      //�摜�Ȃ�
	int image_back;        //�w�i
	int again;
	int gameover_se;
};
