#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{

}

//�f�X�g���N�^
TitleScene::~TitleScene()
{

}

//�X�V
void TitleScene::Update()
{

}

//�`��
void TitleScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 100, "�^�C�g���V�[�� A�{�^���ŃX�^�[�g", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}

	return this;  //�X�V�Ȃ�
}