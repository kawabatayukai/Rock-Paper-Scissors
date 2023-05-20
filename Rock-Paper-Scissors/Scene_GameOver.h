#pragma once
#include "AbstractScene.h"

//ゲームオーバー
class GameOverScene : public AbstractScene
{
public:
	GameOverScene(int again);                      //コンストラクタ
	GameOverScene();

	~GameOverScene();                     //デストラクタ

	void Update() override;                //更新
	void Draw() const override;            //描画
	void GameOverPlay();

	AbstractScene* ChangeScene() override; //シーンの変更
private:      //画像など
	int image_back;        //背景
	int again;
	int gameover_se;
};
