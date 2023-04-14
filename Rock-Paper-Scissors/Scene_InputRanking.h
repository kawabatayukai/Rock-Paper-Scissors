<<<<<<<< HEAD:Rock-Paper-Scissors/Scene_InputRanking.h
#pragma once
#include <stdio.h>

#define RANKING_DATA 10

/*ランキングデータ（構造体*/
struct RankingData {

	int no;

	char name[11];

	long score;
};


class Scene_InputRanking
{
private:
	FILE* fp;
	RankingData g_Ranking[RANKING_DATA];  // ランキングデータ変数宣言

public:

	/*ランキング並べ替え*/
	void SortRanking(void);

	/*ランキングデータの保存*/
	int  SaveRanking(void);

	/*ランキングデータ読み込み*/
	int ReadRanking(void);

	/*ランキングデータ（構造体*/
	RankingData getRankingData(int i);

	void setName(int i, char name[11]);

	void setScore(int i, int score);
};
extern Scene_InputRanking inputRanking;
========
//#pragma once
//#include "AbstractScene.h"
//#include <stdio.h>
//
//#define RANKING_DATA 10
//
///*ランキングデータ（構造体)*/
//struct RankingData
//{
//	int rank; //順位番号
//
//	char name[11]; //名前[11]
//
//	long score; //スコア
//
//	//int time;  //時間
//};
//
//class SortSave :
//    public AbstractScene
//{
//private:
//	FILE* fp;
//
//	RankingData dataRanking[RANKING_DATA];  // ランキングデータ変数宣言
//
//public:
//
//	SortSave(const char* name);
//
//	//更新
//	void Update()override;
//
//	//描画
//	void Draw()const override;
//
//	/*ランキング並べ替え*/
//	void SortRanking(void);
//
//	/*ランキングデータの保存*/
//	int  SaveRanking(void);
//
//	/*ランキングデータ読み込み*/
//	int ReadRanking(void);
//
//	//スコアをセット
//	void setScore(int i, int score);
//
//	//シーンの変更処理
//	AbstractScene* ChangeScene()override;
//
//};
//
>>>>>>>> parent of bfaa0a9 (繝ｩ繝ｳ繧ｭ繝ｳ繧ｰ蜃ｦ逅�縺ｮ螟画峩霑ｽ蜉):Rock-Paper-Scissors/SortSave.h
