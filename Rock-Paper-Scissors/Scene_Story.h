#pragma once
#include"AbstractScene.h"
#include<iostream>
#include<vector>

//あらすじ
class Scene_Story : public AbstractScene
{
public:
	//コンストラクタ
	Scene_Story();         

	//デストラクタ
	~Scene_Story();               

	void Update() override;
	void Draw() const override;

	//シーンの変更
	AbstractScene* ChangeScene() override;

private:

	//あらすじテキスト
	std::vector<std::string> *text;

	bool isLoadFailed;  //読み込み失敗!
	int font_text;      //テキスト用フォント
	int font_skip;      //"skip"用フォント

	int scroll_y;       //スクロール(テキスト描画y座標に減算する)
	int scroll_speed;   //スクロール速度(Aボタンで増加)

	bool str_end;
	int skipflash_count;//スキップ点滅用フレームカウンター
};