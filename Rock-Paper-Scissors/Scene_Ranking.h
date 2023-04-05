#pragma once
#include "AbstractScene.h"

class Scene_Ranking : public AbstractScene
{
	/*コンストラクタ*/
	virtual ~Scene_Ranking() {};

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;
};

