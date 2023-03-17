#pragma once
#include "AbstractScene.h"
#include"Enemy_07.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_07_FLOOR 10         //床・壁の合計数

//0ステージ
class Scene_Stage07 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage07(const Player* player = nullptr);

	~Scene_Stage07();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Draw_Janken() const;              //じゃんけん描画

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	Enemy_07* obj_enemy;            //敵

	bool janken_flag = false;       //接触時じゃんけんフラグ


private:      //画像など
	int image_back;        //背景
	int image_spotlight;   //スポットライト
};

