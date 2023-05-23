#pragma once
#include "AbstractScene.h"
class Scene_NextStage :
    public AbstractScene
{
public:
	Scene_NextStage(int Next);                      //コンストラクタ
	~Scene_NextStage();                     //デストラクタ

	void Update() override;                //更新
	void Draw() const override;            //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	int Next;
	int nextImage[11];
	int next_se[2];

	int frameCount;
};


