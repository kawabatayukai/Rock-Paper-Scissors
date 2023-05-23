#pragma once
#include "AbstractScene.h"
class Scene_NextStage :
    public AbstractScene
{
public:
	Scene_NextStage(int Next);                      //�R���X�g���N�^
	~Scene_NextStage();                     //�f�X�g���N�^

	void Update() override;                //�X�V
	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	int Next;
	int nextImage[11];
	int next_se[2];

	int frameCount;
};


