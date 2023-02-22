#pragma once
#include "AbstractScene.h"

//ゲームクリア
class GameClearScene : public AbstractScene
{
public:
	GameClearScene(int Next);                      //コンストラクタ
	~GameClearScene();                     //デストラクタ

	void Update() override;                //更新
	void Draw() const override;            //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	int Next;
};

