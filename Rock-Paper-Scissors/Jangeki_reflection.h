#pragma once
#include "Jangeki_Base.h"
#include"DxLib.h"
#include"CharaBase.h"

class Jangeki_Reflection : public Jangeki_Base{

public:
		//コンストラクタ  ｘ　　　　ｙ　　　半径　　スピード　　　タイプ
	Jangeki_Reflection(float x, float y, float r, float speed, Jan_Type type);

	~Jangeki_Reflection();

	//virtual void Update() override;       //更新　オーバーライド（再定義）
	//void Draw() const override;        //描画は基底クラスの内容のままでok

	void Update_reflection();
	void Draw_reflectionJangeki() const;
	void Init_reflectionJangeki();
	void Delete_reflectionJangeki(int jan_count_reflection);

	void trueFlg();
	void falseFlg();
	Jangeki_Base** GetJangeki() const { return obj_reflection; } //反射されたジャン撃取得

protected:
	Jangeki_Base** obj_reflection;//反射ジャン撃用配列
	
private:
	bool reflectionFlg = false;


};

