#pragma once
#include "AbstractScene.h"
#include"Enemy_05.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"
#include"Jangeki_reflection.h"
#define STAGE_05_FLOOR 8         //床・壁の合計数

//0ステージ
class Scene_Stage05 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage05(const Player* player = nullptr);

	~Scene_Stage05();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Draw_Janken() const;              //じゃんけん描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）




private:
	Enemy_05* obj_enemy;            //敵
	MobEnemy_05** mob;				//雑魚敵

	int Back_image;					//背景画像

	Jangeki_Reflection* reflection;
};

