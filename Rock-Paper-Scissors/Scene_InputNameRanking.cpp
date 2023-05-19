#include "Scene_InputNameRanking.h"
#include"Scene_Ranking.h"
#include <DxLib.h>
#include "KeyManager.h"
#include"GameData.h"
#include"Scene_Story.h"

Scene_InputNameRanking::Scene_InputNameRanking()
{
	keyboard = new KeyBoard();
}

Scene_InputNameRanking::~Scene_InputNameRanking()
{
	delete keyboard;
}

//更新
void  Scene_InputNameRanking::Update()
{
	keyboard->Update();
}
//描画
void  Scene_InputNameRanking::Draw() const
{
	keyboard->Draw();
	keyboard->DrawInputInfo();
}


//シーンの変更処理
AbstractScene* Scene_InputNameRanking::ChangeScene()
{
	if (keyboard->KeyBoard_PushA() == 1)
	{
		return dynamic_cast<AbstractScene*> (new Scene_Story());
	}

	return this;
}

