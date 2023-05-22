#include "Scene_InputNameRanking.h"
#include"Scene_Ranking.h"
#include <DxLib.h>
#include "KeyManager.h"
#include"GameData.h"
#include"Scene_Story.h"

Scene_InputNameRanking::Scene_InputNameRanking()
{
	keyboard = new KeyBoard();
	bgm = LoadSoundMem("Sound/Help/InputName.wav");
}

Scene_InputNameRanking::~Scene_InputNameRanking()
{
	delete keyboard;
	StopSoundMem(bgm);
}

//�X�V
void  Scene_InputNameRanking::Update()
{
	keyboard->Update();
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
}
//�`��
void  Scene_InputNameRanking::Draw() const
{
	keyboard->Draw();
	keyboard->DrawInputInfo();
}


//�V�[���̕ύX����
AbstractScene* Scene_InputNameRanking::ChangeScene()
{
	if (keyboard->KeyBoard_PushA() == 1)
	{
		return dynamic_cast<AbstractScene*> (new Scene_Story());
	}

	return this;
}

