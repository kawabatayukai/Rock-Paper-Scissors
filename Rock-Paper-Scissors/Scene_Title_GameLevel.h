#pragma once
#include "AbstractScene.h"
class Scene_Title_GameLevel :
    public AbstractScene
{
private:

	int TitleImage = 0;
	int T_selectnum = 0;

	int font_title;   //フォントハンドル
	int font_debug;   //デバッグ用フォント
public:

	//コンストラクタ
	Scene_Title_GameLevel();

	~Scene_Title_GameLevel();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};

