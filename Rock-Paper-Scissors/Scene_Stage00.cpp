#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Stage00.h"
#include"Scene_GameMain.h"
#include"Janken.h"
#include"GameData.h"

//デバッグモード
#include"Debug_Manager.h"

//コンストラクタ
Scene_Stage00::Scene_Stage00(const Player* player) : frame_count(0)
{
	//画像一覧
	int players[10];
	LoadDivGraph("images/ワンパンマンALL画像腕無し.png", 10, 5, 2, 100, 100, players);

	player_image = players[0];
	player_all = LoadGraph("images/ワンパンマンALL画像腕無し.png");

	enemy_02 = LoadGraph("images/stage02/ex.png");
	enemy_03 = LoadGraph("images/stage03/stage03gard.png");
	enemy_04 = LoadGraph("images/Stage4/stage_Boss04.png");
	enemy_05 = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png");
	enemy_06 = LoadGraph("images/stage06/黄NINJA.png");
	enemy_07 = LoadGraph("images/tyokitest.png");
	enemy_08 = LoadGraph("images/stage08/Stage8_image100.png");
	enemy_09 = LoadGraph("images/stage09/Stage9_100.png");
	enemy_10 = LoadGraph("images/tyokitest.png");

	enemy_05_mob = LoadGraph("images/stage05/Mobenemy_image.png");

	hand_rock = LoadGraph("images/腕のみぐーh左.png");
	hand_scissors = LoadGraph("images/腕のみちょき左.png");
	hand_paper = LoadGraph("images/腕のみぱー左.png");

	//制限時間をセット
	GameData::Set_TimeLimit(10800);
	//プレイヤーを生成
	obj_player = new Player(640, 300,1);
	Init_Floor(1);
	//画像読み込み
	image_back = LoadGraph("images/stage01/Tutorial_Back.png");
	obj_floor[0] = new Floor(-100, 685, 1480, 15, 0);
}

//デストラクタ
Scene_Stage00::~Scene_Stage00()
{
}

//更新
void Scene_Stage00::Update()
{
	frame_count++;
	if (frame_count > 120) frame_count = 0;

	obj_player->Update();    // プレイヤー更新・操作可能
	obj_player->Hit_Floor(obj_floor[0]);

	if (obj_player->GetX() > 1330.0f) obj_player->SetX(-40.0f, true);
	else if (obj_player->GetX() < -50.0f) obj_player->SetX(1320.0f);

	return;
}

//描画
void Scene_Stage00::Draw() const
{
	//DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);

	////すべてのキャラを描画
	//DrawGraph(50, 0, player_image, TRUE);
	//DrawGraph(200, 0, enemy_02, TRUE);
	//DrawGraph(350, 0, enemy_03, TRUE);
	//DrawGraph(500, 0, enemy_04, TRUE);
	//DrawGraph(650, 0, enemy_05, TRUE);
	//DrawRotaGraphF(125, 200, 4.2, 0, enemy_06, TRUE, 0);
	//DrawGraph(200, 150, enemy_07, TRUE);
	//DrawGraph(350, 150, enemy_08, TRUE);
	//DrawGraph(500, 150, enemy_09, TRUE);
	//DrawGraph(650, 150, enemy_10, TRUE);

	//DrawGraph(50, 350, player_all, TRUE);

	//DrawGraph(800, 0, enemy_05_mob, TRUE);

	//DrawGraph(50, 550, hand_rock, TRUE);
	//DrawGraph(150, 550, hand_scissors, TRUE);
	//DrawGraph(250, 550, hand_paper, TRUE);

	//if (frame_count < 60) DrawString(350, 670, "Press A Button To SelectScene", 0x006400);

	DrawGraph(0, 0, image_back, FALSE);
	obj_player->Draw();
}



//シーンの変更
AbstractScene* Scene_Stage00::ChangeScene()
{
#ifdef DEBUG_OFF_00

	//Aボタンでゲームメインに戻る
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}
		
#endif // _DEBUG_MODE_00

	return this;   //更新なし
}
