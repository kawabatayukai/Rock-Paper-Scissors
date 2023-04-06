#pragma once
#include"Enemy_Cannon.h"
#include"EnemyBase.h"
//8ステージ　敵キャラ
class Enemy_Cannon : public EnemyBase
{
public:
	//コンストラクタ 座標・属性を設定
	Enemy_Cannon(float x, float y, Jan_Type type);

	~Enemy_Cannon();                     //デストラクタ

	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

private:

	int frame_count = 0;       //じゃん撃発射用

	int Enemy_image;
};
