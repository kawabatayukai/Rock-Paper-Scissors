#pragma once
#include "AbstractScene.h"

class Scne_TitleInterval : public AbstractScene
{
public:
	//コンストラクタ
	Scne_TitleInterval();
	//デストラクタ
	~Scne_TitleInterval();

	void Update() override;
	void Draw() const override;

	//シーンの変更
	AbstractScene* ChangeScene() override;

private:
	int band[3];
};

