#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_GameClear.h"
#include"Scene_GameMain.h"
#include"Scene_Stage00.h"

//�R���X�g���N�^
GameClearScene::GameClearScene()
{
	SetFontSize(50);
}

//�f�X�g���N�^
GameClearScene::~GameClearScene()
{
	SetFontSize(20);
}

//�X�V
void GameClearScene::Update()
{

}

//�`��
void GameClearScene::Draw() const
{
	
	DrawString(100, 360, "�Q�[���N���A", 0xffffff);
	DrawString(100, 460, "A�{�^���������Ă�������", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* GameClearScene::ChangeScene()
{
	//A�{�^���Ŗ߂�
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
		//return dynamic_cast<AbstractScene*> (new Scene_Stage00());
	}

	return this;
}
