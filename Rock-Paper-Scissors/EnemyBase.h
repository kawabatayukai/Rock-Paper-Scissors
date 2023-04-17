#pragma once
#include "CharaBase.h"
#include"Jangeki_Base.h"

//敵キャラの基底クラス  CharaBaseを継承
class EnemyBase : public CharaBase
{
public:
	//コンストラクタ  座標、幅・高さ・属性を設定
	EnemyBase(float x, float y, float w, float h, Jan_Type type);

	~EnemyBase();                   //デストラクタ

	virtual void Update() = 0;      //更新（定義は派生クラス内で）
	virtual void Draw() const = 0;  //描画（定義は派生クラス内で）

	Jan_Type GetType() const { return e_type; }  //属性取得
	void SetType(Jan_Type type);                 //属性変更

	void SetHP(int damage);         //ダメージを受ける

	//HP回復（引数 : 回復量）
	void Recover_HP(const unsigned int recovery);

	//追跡対象の座標をセット　 基本プレイヤー
	void SetPlayerLocation(const float player_x, const float player_y);

	void SetPlayerDirection(const int player_dir);

protected:
	Jan_Type e_type;         //属性（グー　チョキ　パー　のいずれか）
	int image = 0;           //画像
	

	float player_x = 0.0f;   //プレイヤーの座標
	float player_y = 0.0f;   //プレイヤーの座標
};

