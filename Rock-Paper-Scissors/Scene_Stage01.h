#pragma once
#include "AbstractScene.h"
#include"Enemy_01.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_01_FLOOR 5         //床・壁の合計数

//0ステージ
class Scene_Stage01 : public Stage_Base
{
public:
	//コンストラクタ
	Scene_Stage01(const Player* player = nullptr);

	~Scene_Stage01();                      //デストラクタ

	void Update() override;                //更新

	void Draw() const override;            //描画

	AbstractScene* ChangeScene() override; //シーンの変更

	void Draw_Janken() const;              //じゃんけん描画

	//チュートリアル
private:

	void NextTutorial();            //次の操作へ

	bool CheckMoveLR();             //左右移動を確認する

private:
	Enemy_01* obj_enemy;            //敵

	
	int font_tut;                   //チュートリアル用フォント
	int frame_count;                //時間をカウント

	//色
	int blue;
	int red;
	int brack;
	int white;
	int green;


	//チュートリアルの段階
	enum class TUTORIAL_STATE
	{
		START_TUTORIAL,  //チュートリアル開始

		PLAYER_MOVE,     //プレイヤーの左右移動を確認
		PLAYER_JUMP,     //プレイヤーのジャンプを確認
		PLAYER_AIMING,   //プレイヤーの照準を確認

		TOUCH_JANKEN,    //接触じゃんけん
	};
	TUTORIAL_STATE Now_Tut_State;    //現在のチュートリアルの状況を保持
};

