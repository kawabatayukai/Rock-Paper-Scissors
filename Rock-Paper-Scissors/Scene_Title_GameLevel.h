#pragma once
#include "AbstractScene.h"
class Scene_Title_GameLevel :
    public AbstractScene
{
private:
	int T_selectnum = 0;

	//説明画像
	int ex_image;
	int normal_image;
	int image_back;

	static int font_title;   //フォントハンドル
public:

	//コンストラクタ
	Scene_Title_GameLevel();

	~Scene_Title_GameLevel();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};

