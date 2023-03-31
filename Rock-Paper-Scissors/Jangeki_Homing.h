#pragma once
#include"Jangeki_Base.h"

/**************************************************************************************/
/*　ホーミングじゃん撃を使うときはUpdateの前に SetTargetLocation(player x , player y) */
/**************************************************************************************/

//ホーミングじゃん撃
class Jangeki_Homing : public Jangeki_Base
{
public:
	//コンストラクタ  ｘ　　　　ｙ　　　半径　　スピード　　　タイプ
	Jangeki_Homing(float x, float y, float r, float speed, Jan_Type type, bool ref = false);

	~Jangeki_Homing();

	virtual void Update() override;              //更新　オーバーライド（再定義）
	//void Draw() const override;        //描画は基底クラスの内容のままでok


private:
	/* 座標系、スピード　などの変数は
	      基底クラス Jangeki_Base に protected の状態であります   */


	double angle;             //角度
	int time_counter = 0;     //追跡時間をカウント
};