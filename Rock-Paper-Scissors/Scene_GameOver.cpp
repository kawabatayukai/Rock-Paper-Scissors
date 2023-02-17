#include "Scene_GameOver.h"
#include"Scene_GameMain.h"
#include"Scene_Stage00.h"
#include"DxLib.h"
#include"KeyManager.h"

//�R���X�g���N�^
GameOverScene::GameOverScene()
{
	SetFontSize(50);
}

//�f�X�g���N�^
GameOverScene::~GameOverScene()
{
	SetFontSize(20);
}

//�X�V
void GameOverScene::Update()
{

}

//�`��
void GameOverScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 360, "�Q�[���I�[�o�[", 0xffffff);
	DrawString(100, 460, "A�{�^���������Ă�������", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* GameOverScene::ChangeScene()
{
	//A�{�^���Ŗ߂�
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
		//return dynamic_cast<AbstractScene*> (new Scene_Stage00());
	}

	return this;
}
