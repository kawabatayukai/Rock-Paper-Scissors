#include"DxLib.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"
#include"Scene_End.h"
#include"Scene_Stage01.h"

#include"GameData.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle.png");

	//�t�H���g�f�[�^���쐬
	font_title = CreateFontToHandle("Yu Gothic UI", 50, 3, DX_FONTTYPE_ANTIALIASING_4X4);
}

//�f�X�g���N�^
TitleScene::~TitleScene()
{
	//�t�H���g�f�[�^���폜
	DeleteFontToHandle(font_title);
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
	DrawGraph(0,0,TitleImage,TRUE);
	
	// �J�����[�h����Debug_Manager.h��"DEBUG_MODE_GAMEMAIN"���R�����g�A�E�g����
#ifdef  DEBUG_MODE_GAMEMAIN

	DrawStringToHandle(70, 350, "START", 0xf, font_title);
#else
	DrawStringToHandle(70, 350, "GAMEMAIN", 0xf, font_title);
#endif

	DrawStringToHandle(70, 395, "END", 0xf, font_title);

	//���j���[�J�[�\��
	DrawTriangle(40, 355 + (T_selectnum * 52), 60, 370 + (T_selectnum * 52), 40, 385 + (T_selectnum * 52), GetColor(255, 0, 0), TRUE);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	//A�{�^���Ō���
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		switch (T_selectnum)
		{
		case 0:

			GameData::Init_Data();   //�f�[�^�̏�����

			// �J�����[�h����Debug_Manager.h��"DEBUG_MODE_GAMEMAIN"���R�����g�A�E�g����
#ifdef  DEBUG_MODE_GAMEMAIN

			return dynamic_cast<AbstractScene*> (new Scene_Stage01);
#else
			return dynamic_cast<AbstractScene*> (new GameMainScene());
#endif
			break;



#ifdef  DEBUG_MODE_GAMEMAIN

			case 1:
				if (KeyManager::OnPadClicked(PAD_INPUT_A))
				{
					return dynamic_cast<AbstractScene*> (new EndScene());
				}
				break;
#endif

		default:
			break;
		}
	}

	return this;  //�X�V�Ȃ�
}