#pragma once
#include "AbstractScene.h"
#include"Enemy_02.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"


#define STAGE_02_FLOOR 3         //床・壁の合計数

//0ステージ
class Scene_Stage02 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage02(const Player* player = nullptr);

	~Scene_Stage02();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	              //じゃんけん更新・内部処理
	void Draw_Janken() const;              //じゃんけん描画

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）
	AbstractScene* ChangeScene() override; //シーンの変更

private:
	Enemy_02* obj_enemy;            //敵
	

private:      //画像など
	int image_back;        //背景
	int hp = 50;//復活HP(半分づつ減る)
	int  attack_pattern = 0;      //攻撃パターン変数
	int STAGE02_BGM;
	int bgm;
};

