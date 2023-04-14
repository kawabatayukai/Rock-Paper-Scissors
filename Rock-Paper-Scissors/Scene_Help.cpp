#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Help.h"
#include"Scene_Title.h"

//�R���X�g���N�^
HelpScene::HelpScene()
{

}

//�f�X�g���N�^
HelpScene::~HelpScene()
{

}

//�X�V
void HelpScene::Update()
{

}

//�`��
void HelpScene::Draw() const
{
	SetFontSize(50);
	DrawString(100, 100, "�w���v�V�[�� A�{�^���Ń^�C�g��", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* HelpScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}

	return this;  //�X�V�Ȃ�
}