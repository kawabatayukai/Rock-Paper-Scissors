#pragma once
#include"AbstractScene.h"

//タイトルシーン
class EndScene : public AbstractScene
{
public:
	//コンストラクタ
	EndScene();

	~EndScene();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};
