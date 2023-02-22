#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");
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
	
	DrawGraph(0,0,TitleImage,TRUE);
	DrawString(100, 640, "�^�C�g���V�[�� A�{�^���ŃX�^�[�g", GetColor(255,0,0));
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