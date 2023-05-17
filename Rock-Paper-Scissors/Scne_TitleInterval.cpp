#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"



//�R���X�g���N�^
Scne_TitleInterval::Scne_TitleInterval()
{
	band[0] = LoadGraph("images/���[��1.png");
	band[1] = LoadGraph("images/���[��2.png");
	band[2] = LoadGraph("images/���[��3.png");
}

//�f�X�g���N�^
Scne_TitleInterval::~Scne_TitleInterval()
{

}

void Scne_TitleInterval::Update()
{

}

//�`��
void Scne_TitleInterval::Draw() const
{
	DrawString(0, 360, "Press A", 0xffffff);
	DrawString(0, 400, "�Â����^�C�g��", 0xffffff);
}

//�V�[���̕ύX
AbstractScene* Scne_TitleInterval::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		return dynamic_cast<AbstractScene*> (new TitleScene());
	//�X�V�Ȃ�
	return this;
}