#include "Scene_NextStage.h"
#include"DxLib.h"
#include"KeyManager.h"

#include"Scene_GameMain.h"
#include"Scene_Title.h"

#include"Scene_Stage00.h"
#include"Scene_Stage01.h"
#include"Scene_Stage02.h"
#include"Scene_Stage03.h"
#include"Scene_Stage04.h"
#include"Scene_Stage05.h"
#include"Scene_Stage06.h"
#include"Scene_Stage07.h"
#include"Scene_Stage08.h"
#include"Scene_Stage09.h"
#include"Scene_Stage10.h"

#include"Scene_End.h"
#include"Scene_Help.h"
#include"SortSave.h"
#include"GameData.h"
#include"SortSave.h"
#include"Scene_Ranking.h"
#include "SortSaveTime.h"


//コンストラクタ
Scene_NextStage::Scene_NextStage(int Next) :Next(Next)
{
	nextImage[0] = LoadGraph("images/GameClear2.png");
	nextImage[1] = LoadGraph("images/GameClear2.png");
	nextImage[2] = LoadGraph("images/GameClear2.png");
	nextImage[3] = LoadGraph("images/GameClear2.png");
	nextImage[4] = LoadGraph("images/GameClear2.png");
	nextImage[5] = LoadGraph("images/GameClear2.png");
	nextImage[6] = LoadGraph("images/GameClear2.png");
	nextImage[7] = LoadGraph("images/GameClear2.png");
	nextImage[8] = LoadGraph("images/GameClear2.png");
	nextImage[9] = LoadGraph("images/GameClear2.png");

	next_se = LoadSoundMem("Sound/和太鼓でドドン.mp3");
}

//デストラクタ
Scene_NextStage::~Scene_NextStage()
{
	StopSoundMem(next_se);
	SetFontSize(20);
}

//更新
void Scene_NextStage::Update()
{
	//clear_se
	if (CheckSoundMem(next_se) == 0) PlaySoundMem(next_se, DX_PLAYTYPE_BACK);
}

//描画
void Scene_NextStage::Draw() const
{
	switch (Next)
	{
	case 1:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 2:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 3:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 4:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 5:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 6:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 7:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 8:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 9:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 10:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;

	case 11:
		//背景
		DrawGraph(0, 0, nextImage[0], TRUE);
		break;
	}

}

//シーンの変更
AbstractScene* Scene_NextStage::ChangeScene()
{
	//Aボタンで戻る
	/*if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}*/
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		switch (Next)
		{
		case 0:
			return dynamic_cast<AbstractScene*> (new Scene_Stage00());
			break;

		case 1:
			return dynamic_cast<AbstractScene*> (new Scene_Stage01());
			break;

		case 2:
			return dynamic_cast<AbstractScene*> (new Scene_Stage02());
			break;

		case 3:
			return dynamic_cast<AbstractScene*> (new Scene_Stage03());
			break;

		case 4:
			return dynamic_cast<AbstractScene*> (new Scene_Stage04());
			break;

		case 5:
			return dynamic_cast<AbstractScene*> (new Scene_Stage05());
			break;

		case 6:
			return dynamic_cast<AbstractScene*> (new Scene_Stage06());
			break;

		case 7:
			return dynamic_cast<AbstractScene*> (new Scene_Stage07());
			break;

		case 8:
			return dynamic_cast<AbstractScene*> (new Scene_Stage08());
			break;

		case 9:
			return dynamic_cast<AbstractScene*> (new Scene_Stage09());
			break;

		case 10:
			return dynamic_cast<AbstractScene*> (new Scene_Stage10());
			break;

		case 11:/*ランキング内部処理*/

			/*スコア順*/
			sortSave.setScore(9, 10);	// ランキングデータの１０番目にスコアを登録
			sortSave.SortRanking();		// ランキング並べ替え
			sortSave.SaveRanking();		// ランキングデータの保存

			/*時間順*/
			sortSaveTime.setTimerMin(9, 10); // ランキングデータの１０番目に時間：分を登録
			sortSaveTime.setTimerSec(9, 10); // ランキングデータの１０番目に時間：秒を登録
			sortSaveTime.SortRanking();		// ランキング並べ替え
			sortSaveTime.SaveRanking();		// ランキングデータの保存

			/*ランキング画面へ*/
			return new Scene_Ranking();
			break;

		default:
			break;
		}

	}
	return this;
}