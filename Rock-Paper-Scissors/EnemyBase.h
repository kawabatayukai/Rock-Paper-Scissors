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
	void SetHP(int damage);

protected:
	Jan_Type e_type;         //属性（グー　チョキ　パー　のいずれか）
	int image = 0;
};

