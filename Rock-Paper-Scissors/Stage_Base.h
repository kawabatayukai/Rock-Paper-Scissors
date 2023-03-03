#pragma once
#include "AbstractScene.h"
#include"Floor.h"
#include"Player.h"
#include"Janken.h"

//ステージのベース
class Stage_Base : public AbstractScene
{
private:
	int typeImage[3];
public:
	Stage_Base();
	~Stage_Base();

	void DrawUI(Jan_Type type ,int hp) const;

	//床・壁の準備　　STAGE_XX_FLOOR を引数に
	void Init_Floor(const int floor_MAX);

	//床・壁とのあたり判定
	void HitCtrl_Floor(CharaBase* character, const int floor_MAX);


	//"接触時じゃんけん"処理   player(引数１番目　の勝敗結果を返す)
	Jan_Result Get_JankenResult(Jan_Type player, Jan_Type enemy);

protected:
	Player* obj_player = nullptr;             //プレイヤー
	Floor** obj_floor = nullptr;              //床・壁

	Janken* obj_janken = nullptr;             //じゃんけん用
};

