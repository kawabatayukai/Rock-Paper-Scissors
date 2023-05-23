#pragma once
#include "AbstractScene.h"
#include"SortSave.h"

class Scene_Ranking : public AbstractScene
{
public:


	Scene_Ranking(/*const RankingData* Data*/);

	//デストラクタ
	 ~Scene_Ranking();

	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //背景画像
	int ranking_font;
	//RankingData dataRanking[RANKING_DATA_COLUMN];  // ランキングデータ変数宣言
	int r_bgm;
};

