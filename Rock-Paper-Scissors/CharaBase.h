#pragma once
#include"Floor.h"
#include"Jangeki_Base.h"

#define MAX_LENGTH 16     //めりこみ許容範囲
#define _GRAVITY 1.0f     //キャラクターにかかる重力

#define JANGEKI_MAX 60    //じゃん撃最大数


//キャラクターの基底クラス　　プレイヤー・敵キャラのベース
class CharaBase
{
public:
	//コンストラクタ    ｘ,ｙ座標, 幅,高さ　を設定
	CharaBase(float x, float y, float w, float h);
	~CharaBase();                  //デストラクタ

/****************  ↓↓ 以降、キャラクターが共通して持つ変数・関数 ↓↓  ****************/

	virtual void Update() = 0;          //更新（定義は派生クラス内で）
	virtual void Draw() const = 0;      //描画（定義は派生クラス内で）


	virtual void Update_Jangeki();      //じゃん撃生成・更新    使っても使わなくても
	void Draw_Jangeki() const;          //じゃん撃描画
	void Init_Jangeki();                //じゃん撃用意   じゃん撃を使用したいときにコンストラクタで呼び出す
	void DeleteJangeki(int jan_count);  //じゃん撃削除


	float GetX() const { return x; }    //ｘ座標取得
	float GetY() const { return y; }    //ｙ座標取得
	float GetW() const { return w; }    //幅　　取得
	float GetH() const { return h; }    //高さ　取得
	int  GetHP() const { return hp; }   //  hp  取得
	Jangeki_Base** GetJangeki() const { return obj_jangeki; }  //じゃん撃配列取得

	void ReceiveDamage(int damage);     //ダメージを受ける　（hp -= damage）
	void SetX(const float x);           //ｘ座標変更
	void SetY(const float y);           //ｙ座標変更
 
	/*******************  当たり判定  *******************/
	
	//Floor(床)との当たり処理
	void Hit_Floor(const Floor* floor);

	//キャラクター同士の当たり判定  Hit:true
	bool Hit_Character(const CharaBase* character);

	//じゃん撃とキャラクターの当たり判定
	bool Hit_Jangeki(const Jangeki_Base* jangeki);

private:
	//矩形と矩形の当たり判定
	bool CheckHitBox_Box(int box_x, int box_y, int box_w, int box_h);

	//矩形と円形の当たり判定
	bool CheckHitBox_Circle(float c_x, float c_y, float c_r);

	/****************************************************/

protected:
	//キャラクターの座標は中心
	float x;
	float y;
	float w;
	float h;

	float speed;              //スピード
	int hp;                   //HP
	int dir;                  //向き

	bool land_flg = false;    //接地フラグ　　接地:true   非接地:false

	//じゃん撃　ポインタ配列
	Jangeki_Base** obj_jangeki;
};
