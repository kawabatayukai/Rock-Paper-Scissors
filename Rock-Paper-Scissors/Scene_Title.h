#pragma once
#include"AbstractScene.h"

//タイトルシーン
class TitleScene : public AbstractScene
{
private:

	int TitleImage = 0;
	int T_selectnum = 0;

	int font_title;   //フォントハンドル
public:

	//コンストラクタ
	TitleScene();

	~TitleScene();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};