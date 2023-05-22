#pragma once
#include "AbstractScene.h"
#include"KeyBoard.h"

//キーの種類
enum class CURSOR_TYPE
{
	NONE = 0,   // 入力0（なにも押されていない）
	NORMAL,     // A～B,a～b,1～9
	CANCEL,     //「×」(ひとつ消す)
	DONE,       //「OK」(確定)
	MISS = 99
};

class Scene_InputNameRanking : public AbstractScene
{
public:
	Scene_InputNameRanking();
    ~Scene_InputNameRanking();
	//更新
	void Update()override;

	//描画
	void Draw()const override;

	//シーンの変更処理
	AbstractScene* ChangeScene()override;

private:
	KeyBoard* keyboard;   //キーボード
	int bgm;
};

