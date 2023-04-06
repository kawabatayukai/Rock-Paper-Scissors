#pragma once
#include "AbstractScene.h"
#include"Enemy_00.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_00_FLOOR 7         //床・壁の合計数　　　床、壁を追加するときに増やす

//0ステージ
class Scene_Stage00 : public Stage_Base
{
public:
	//コンストラクタ      前のステージのプレイヤー情報を引き継ぐ
	Scene_Stage00(const Player* player = nullptr);

	~Scene_Stage00();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:

	short frame_count;    //フレームカウント

	int player_image;
	int player_all;

	int enemy_02;
	int enemy_03;
	int enemy_04;
	int enemy_05;
	int enemy_06;
	int enemy_07;
	int enemy_08;
	int enemy_09;
	int enemy_10;

	int enemy_05_mob;

	int hand_rock;
	int hand_scissors;
	int hand_paper;
};

