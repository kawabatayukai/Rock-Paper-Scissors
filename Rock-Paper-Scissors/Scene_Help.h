#pragma once
#include"AbstractScene.h"

//ヘルプシーン
class HelpScene : public AbstractScene
{
private:
	int HelpImage = 0;
	int HelpImage1;
public:
	//コンストラクタ
	HelpScene();

	~HelpScene();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};