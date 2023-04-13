#pragma once
#include "AbstractScene.h"
#include"Floor.h"
#include"Player.h"
#include"Janken.h"
#include"EnemyBase.h"

//ステージのベース
class Stage_Base : public AbstractScene
{
private:
	int typeImage[3];
	int hpImage;
public:
	Stage_Base();
	~Stage_Base();

	//UI描画
	void DrawUI(Jan_Type type ,int hp) const;

	//敵の上にUI描画
	void DrawUI_ON_Enemy(const EnemyBase* enemy) const;

	//床・壁の準備　　STAGE_XX_FLOOR を引数に
	void Init_Floor(const int floor_MAX);

	//床・壁とのあたり判定
	void HitCtrl_Floor(CharaBase* character, const int floor_MAX);


	//"接触時じゃんけん"処理   player(引数１番目　の勝敗結果を返す)
	Jan_Result Get_JankenResult(Jan_Type player, Jan_Type enemy);

	//敵とプレイヤーの当たり判定→接触じゃんけん処理    敵へのポインタ、"this" を引数に
	void Touch_Janken(EnemyBase* enemy, Stage_Base* stage_ptr, int my_StageNum = 0);

	//じゃんけん描画
	void Draw_Janken() const;   

	void Draw_JankenStart() const;         //じゃんけん開始直後

	virtual void AfterJanken_WIN();        //じゃんけん終了後の挙動（プレイヤー勝ち）
	virtual void AfterJanken_LOSE();       //じゃんけん終了後の挙動（プレイヤー負け）

	//じゃんけんの状態取得
	Jan_State GetJanState() const;

protected:
	Player* obj_player = nullptr;             //プレイヤー
	Floor** obj_floor = nullptr;              //床・壁
	Janken* obj_janken = nullptr;             //じゃんけん用

private:
	short nhit_time = 0;                      //衝突判定なし時間

	int font;         //結果(WIN or LOSE or ONEMORE) 用フォント 

	Jan_State j_state = Jan_State::BEFORE;    //じゃんけんの状態

	unsigned short blackout_time;             //暗転時間（接触直後演出）
};

