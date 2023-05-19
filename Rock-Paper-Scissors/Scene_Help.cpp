#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Help.h"
#include"Scene_Title.h"

int HelpScene::font_help = 0;

//�R���X�g���N�^
HelpScene::HelpScene()
{
	HelpImage = LoadGraph("images/help/help_2.png");
	if(font_help == 0) font_help = CreateFontToHandle("���C���I", 40, 10, DX_FONTTYPE_ANTIALIASING_EDGE, -1, 3);
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
	DrawStringToHandle(50, 660, "A : �^�C�g��", 0xffffff, font_help, 0x7cd900);

	//RB
	if (KeyManager::OnPadPressed(PAD_INPUT_6))   
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 80);
		DrawBox(778, 58, (778 + 89), (58 + 60), 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//LB
	if (KeyManager::OnPadPressed(PAD_INPUT_6))   
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 80);
		DrawBox(778, 58, (778 + 89), (58 + 60), 0xffffff, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
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