#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_End.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
EndScene::EndScene()
{

}

//�f�X�g���N�^
EndScene::~EndScene()
{

}

//�X�V
void EndScene::Update()
{

}

//�`��
void EndScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 100, "�G���h�V�[�� A�{�^���ŏI��", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* EndScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return nullptr;
	}

	return this;  //�X�V�Ȃ�
}