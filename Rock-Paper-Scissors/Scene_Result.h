#pragma once
#include "AbstractScene.h"

class Scene_Result : public AbstractScene
{
public:
	/*コンストラクタ*/
	virtual ~Scene_Result() {};

	char name[11];

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;
};

