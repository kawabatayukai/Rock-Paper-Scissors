#pragma once
#include "AbstractScene.h"
class Scene_RankingTime :
    public AbstractScene
{
public:

	/*コンストラクタ*/
	Scene_RankingTime();

	//デストラクタ
	~Scene_RankingTime();

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //背景画像
	int ranking_font;
	int r_bgm;
};

