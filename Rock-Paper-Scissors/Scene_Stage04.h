#pragma once
#include "AbstractScene.h"
#include"Enemy_04.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_04_FLOOR 16         //床・壁の合計数

//0ステージ
class Scene_Stage04 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage04(const Player* player = nullptr);

	~Scene_Stage04();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Draw_Janken() const;              //じゃんけん描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）

	int back_image;

private:
	Enemy_04* obj_enemy;            //敵

	
};

