#pragma once
#include "AbstractScene.h"
#include"Enemy_09.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"
#include"Jangeki_reflection.h"

#define STAGE_09_FLOOR 11         //床・壁の合計数

//0ステージ
class Scene_Stage09 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage09(const Player* player = nullptr);

	~Scene_Stage09();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Draw_Janken() const;              //じゃんけん描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）
	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）
	
bool Rflg = false; //反射じゃん撃判別用
private:
	Enemy_09* obj_enemy;            //敵
	Jangeki_Reflection* reflection;

	int stageimage;


};

