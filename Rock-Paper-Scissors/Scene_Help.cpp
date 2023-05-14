#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Help.h"
#include"Scene_Title.h"
#include "Scene_Stage01.h"
//�R���X�g���N�^
HelpScene::HelpScene()
{
	HelpImage = LoadGraph("images/Help2.png");
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

	DrawGraph(0, 0, HelpImage, TRUE);
	SetFontSize(30);
	//DrawString(100, 100, "�ԐF��B�{�^���ŃO�[�����ɕύX", 0x000000);
	//DrawString(100, 500, "�w���v�V�[�� B�{�^���Ń`���[�g���A��", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* HelpScene::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	if (KeyManager::OnPadClicked(PAD_INPUT_B))
	{
		return dynamic_cast<AbstractScene*> (new Scene_Stage01());
	}
	return this;  //�X�V�Ȃ�
}