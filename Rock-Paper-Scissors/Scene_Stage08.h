#pragma once
#include "AbstractScene.h"
#include"Enemy_08.h"
#include"Enemy_Cannon.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_08_FLOOR  30        //床・壁の合計数

//0ステージ
class Scene_Stage08 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage08(const Player* player = nullptr);

	~Scene_Stage08();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Draw_Janken() const;              //じゃんけん描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）

private:
	int Back_image;
	Enemy_08* obj_enemy;            //敵
	Enemy_Cannon* obj_cannon;
	Enemy_Cannon** cannon;
};


