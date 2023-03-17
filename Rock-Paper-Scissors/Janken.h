#pragma once
#include"Jangeki_Base.h"

//じゃんけんの状態
enum class Jan_State
{
	BEFORE,      //じゃんけん前(何もしていない)
	PROGRESS,    //じゃんけん中・・
	AFTER,       //じゃんけん終了（結果を取得可能）
};

// 接触時のじゃんけん  勝敗を決めるクラス
class Janken
{
public:
	//コンストラクタ   敵の出す手をもらう
	Janken(Jan_Type enemy_jan);

	~Janken();            //デストラクタ

	void Update();        //更新
	void Draw() const;    //描画

	Jan_Result GetResult() const { return result; }  //じゃんけんの結果を返す


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
	
	int image[3];            //画像
};
