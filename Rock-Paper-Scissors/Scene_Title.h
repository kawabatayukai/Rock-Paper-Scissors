#pragma once
#include"AbstractScene.h"

//タイトルシーン
class TitleScene : public AbstractScene
{
private:

	int TitleImage = 0;
	int TitleBgm;
	int SelectSE;
	int ClickSE;
	int T_selectnum = 0;

	static int font_title;   //フォントハンドル
	int bgm;
public:

	//コンストラクタ
	TitleScene();

	~TitleScene();     //デストラクタ

	void Update() override;      //更新
	void Draw() const override;  //描画

	AbstractScene* ChangeScene() override;   //シーンの変更
};