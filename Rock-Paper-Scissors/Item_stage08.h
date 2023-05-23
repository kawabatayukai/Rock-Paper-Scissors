#pragma once
#include"Jangeki_Base.h"

//アイテム
class Item_st8 : public Jangeki_Base
{
public:
	//コンストラクタ  ｘ　　　　ｙ　
	Item_st8(float x, float y, float r);

	~Item_st8();

	virtual void Update() override;              //更新　オーバーライド（再定義）
	virtual void Draw() const override;

	
private:
	/* 座標系、スピード　などの変数は
		  基底クラス Jangeki_Base に protected の状態であります   */
	int image;
};