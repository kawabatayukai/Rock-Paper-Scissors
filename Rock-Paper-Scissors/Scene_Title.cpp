#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"

#include"GameData.h"

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
	//�J�[�\�������킹�ă{�^���������ƑJ��
	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {

		//��{�^���ŏ��
		T_selectnum++;

		if (T_selectnum > 1) T_selectnum = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {

		//���{�^���ŉ���
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 1;

	}

}

//�`��
void TitleScene::Draw() const
{
	SetFontSize(50);
	DrawGraph(0,0,TitleImage,TRUE);
	DrawString(70, 350, "GAMEMAIN", 0xf);
	DrawString(70, 395, "END", 0xf);


	//���j���[�J�[�\��
	DrawTriangle(40, 355 + (T_selectnum * 52), 60, 370 + (T_selectnum * 52), 40, 385 + (T_selectnum * 52), GetColor(255, 0, 0), TRUE);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	
	switch (T_selectnum)
	{
	case 0:

		if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
		{
			GameData::Init_Data();   //�f�[�^�̏�����

			return dynamic_cast<AbstractScene*> (new GameMainScene());
		}
		/*case 1:
			if (KeyManager::OnPadClicked(PAD_INPUT_A))
			{
				return dynamic_cast<AbstractScene*> (new GameEnd());
			}*/

	default:
		break;
	}

	return this;  //�X�V�Ȃ�
}