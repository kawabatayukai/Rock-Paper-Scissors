#pragma once
#include "AbstractScene.h"
#include"SortSave.h"

class Scene_Ranking : public AbstractScene
{
public:
	Scene_Ranking(/*const RankingData* Data*/);

	/*コンストラクタ*/
	virtual ~Scene_Ranking() {};

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //背景画像
	//RankingData dataRanking[RANKING_DATA];  // ランキングデータ変数宣言
};

