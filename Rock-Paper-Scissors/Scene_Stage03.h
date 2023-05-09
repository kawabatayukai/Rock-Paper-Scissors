#pragma once
#include "AbstractScene.h"
#include"Enemy_03.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_03_FLOOR 12     //床・壁の合計数

//0ステージ
class Scene_Stage03 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage03(const Player* player = nullptr);

	~Scene_Stage03();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	void Draw_Janken() const;              //じゃんけん描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void AfterJanken_WIN()  override;      //じゃんけん終了後の挙動（プレイヤー勝ち）

	void AfterJanken_LOSE() override;      //じゃんけん終了後の挙動（プレイヤー負け）

private:
	Enemy_03* obj_enemy;            //敵


	int stage ;//背景
	int GroundImages ; //地面
	int BlockImages ; //ブロック
	int PlayerCutDamege ;//プレイヤーが勝った接触じゃんけん勝利時のダメージカット
	int EnemyCutDamege; //エネミーが勝った接触じゃんけん勝利時のダメージカット
	int SheeldEnduranse;//シールドの耐久力
	
	int ShieldBrokenSE; //完全に壊れた時
	int SlightlyBrokenSE;//少し壊れているとき
	int Enemy_Janwin;//エネミーのじゃんけん結果保持用

};