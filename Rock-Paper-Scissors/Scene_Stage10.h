#pragma once
#include "AbstractScene.h"
#include"Enemy_10.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_10_FLOOR 16         //床・壁の合計数

//0ステージ
class Scene_Stage10 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage10(const Player* player = nullptr);

	~Scene_Stage10();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Update_Janken();                  //じゃんけん更新・内部処理
	void Draw_Janken() const;              //じゃんけん描画

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	Enemy_10* obj_enemy;            //敵

	Jangeki_Reflection* reflection;

	bool janken_flag = false;       //接触時じゃんけんフラグ

	int bgm[4];
};

