#pragma once
#include"Jangeki_Base.h"

//じゃんけんの状態
enum class Jan_State
{
	BEFORE,      //じゃんけん前(何もしていない)
	PROGRESS,    //じゃんけん中・・
	AFTER,       //じゃんけん終了（結果を取得可能）

	START,       //スタート（当たった瞬間の演出）
	END,         //終了（終わった演出）
};

// 接触時のじゃんけん  勝敗を決めるクラス
class Janken
{
public:
	//コンストラクタ   敵の出す手をもらう
	Janken(Jan_Type enemy_jan, const int stage_num = 0);

	~Janken();            //デストラクタ

	void Update();        //更新
	void Draw() const;    //描画

	Jan_Result GetResult() const { return result; }  //じゃんけんの結果を返す

	//(あいこの時用) 必要な変数を初期化する
	void OneMore_Init();

private:

	//B（グー）,Y（チョキ）,X（パー）のいずれかが押された瞬間、trueを返す
	bool Check_AnyButton();

	//"接触時じゃんけん"処理
	//   Check_AnyButton() で押されたボタンと enemy（引数）の勝敗結果を返す (押されたボタン目線)
	Jan_Result Get_JankenResult();

private:
	bool button_B = false;   //Bボタンが押されているか
	bool button_Y = false;   //Yボタンが押されているか
	bool button_X = false;   //Xボタンが押されているか

	Jan_Type enemy_jan;      //敵の出す手　コンストラクタでもらう
	Jan_Type player_jan;     //プレイヤーの出す手  Check_AnyButton()で押されたボタン

	Jan_Result result;       // じゃんけんの結果を格納する

	int time = 0;            //カウンター
	int p_image_x;           //プレイヤー描画ｘ座標
	int e_image_x;           //敵描画ｘ座標


//---------------------------------------------------------------
	int image[3];            //画像
	int image_back;          //じゃんけん中背景
	int image_back_light;    //じゃんけん中"VS"

	int image_hand;          //じゃんけん説明
	int image_player;        //プレイヤーじゃんけん中
	int image_enemy;         //敵じゃんけん中

	int image_all_enemy[11]; //全ステージの画像
	int image_all_back[11];  //全ステージの背景
	int stage_num;           //呼び出し元のステージ番号

	int font_result;         //結果(WIN or LOSE or ONEMORE) 用フォント 
	int font_other;          //「じゃんけん..」,「ぽん」など用フォント

	//色
	int blue;
	int red;
	int brack;
	int white;
	int green;
};
