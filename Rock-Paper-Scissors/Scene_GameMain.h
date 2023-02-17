#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Floor.h"

//ゲームメイン
class GameMainScene : public AbstractScene
{
public:
	//コンストラクタ()
	GameMainScene();

	~GameMainScene();                      //デストラクタ     

	void Update() override;                //更新

	void Draw() const override;            //描画

	AbstractScene* ChangeScene() override; //シーンの変更

private:
	Player* obj_player;
	Floor** obj_floor;

	//セレクト番号
	int select_num = 0;

	//AbstractScene** Stage_Select;    //0～2ステージへのポインタ
};