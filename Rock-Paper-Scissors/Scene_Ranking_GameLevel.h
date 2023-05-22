#pragma once
#include "AbstractScene.h"
class Scene_Ranking_GameLevel :
    public AbstractScene
{
private:

	int image_back = 0;
	int T_selectnum = 0;

	static int font_title;   //フォントハンドル

	int r_gamemode_bgm; //ランキングのゲームモードセレクト画面
public:

	//コンストラクタ
	Scene_Ranking_GameLevel();

	~Scene_Ranking_GameLevel();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};

