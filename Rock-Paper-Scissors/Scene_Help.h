#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Floor.h"

//ヘルプシーン
class HelpScene : public AbstractScene
{	
public:
	//コンストラクタ
	HelpScene();

	~HelpScene();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更

private:
	int HelpImage = 0;      //画像
	static int font_help;   //フォント

	Player* obj_player;     //プレイヤー
	Floor** obj_floor;      //床
};