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

	void Draw_Janken() const;              //じゃんけん描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	Enemy_00* obj_enemy;            //敵


	//test
	int setumei;  //説明画像
};

