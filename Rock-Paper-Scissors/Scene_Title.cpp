#include"DxLib.h"
#include"KeyManager.h"
#include"Debug_Manager.h"
#include"Scene_Title.h"
#include"Scene_GameMain.h"
#include"Scene_End.h"
#include"Scene_Stage01.h"
#include "Scene_Ranking.h"
#include "Scene_Help.h"
#include"GameData.h"

//�R���X�g���N�^
TitleScene::TitleScene()
{
	TitleImage = LoadGraph("images/JankenWorldTitle1.png");

	//�^�C�g��BGM�Ǎ���
	TitleBgm = LoadSoundMem("Sound/TitleBGM.mp3");
	//�^�C�g��BGM����
	ChangeVolumeSoundMem(150, TitleBgm);
	//�Z���N�gSE�Ǎ���
	SelectSE = LoadSoundMem("Sound/Select.mp3");
	//�Z���N�gSE����
	ChangeVolumeSoundMem(230, SelectSE);
	//����SE�Ǎ���
	ClickSE = LoadSoundMem("Sound/����{�^��������24.mp3");
	//����SE����
	ChangeVolumeSoundMem(230, ClickSE);
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
	if (KeyManager::OnPadClicked(PAD_INPUT_DOWN) == true) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);
		//��{�^���ŏ��
		T_selectnum++;

		if (T_selectnum > 3) T_selectnum = 0;
		/*if (T_selectnum > 2) T_selectnum = 1;
		if (T_selectnum > 3) T_selectnum = 2;*/
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_UP) == true) {
		PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK, TRUE);

		//���{�^���ŉ���
		T_selectnum--;

		if (T_selectnum < 0) T_selectnum = 3;
		/*if (T_selectnum < 1) T_selectnum = 2;
		if (T_selectnum < 2) T_selectnum = 3;*/

	}

}

//�`��
void TitleScene::Draw() const
{
	DrawGraph(0,0,TitleImage,TRUE);
	PlaySoundMem(TitleBgm, DX_PLAYTYPE_LOOP, FALSE);
	// �J�����[�h����Debug_Manager.h��"DEBUG_MODE_GAMEMAIN"���R�����g�A�E�g����
#ifdef  DEBUG_MODE_GAMEMAIN

	DrawStringToHandle(70, 350, "START", 0xf, font_title);
#else
	DrawStringToHandle(70, 140, "GAMEMAIN", 0xf, font_title);
	DrawStringToHandle(70, 195, "HELP", 0xf, font_title);
	DrawStringToHandle(70, 245, "RANKING", 0xf, font_title);
#endif

	DrawStringToHandle(70, 295, "END", 0xf, font_title);

	//���j���[�J�[�\��
	DrawTriangle(40, 155 + (T_selectnum * 50), 60, 170 + (T_selectnum * 50), 40, 185 + (T_selectnum * 50), GetColor(255, 0, 0), TRUE);
}

//�V�[���̕ύX
AbstractScene* TitleScene::ChangeScene()
{
	//A�{�^���Ō���
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		PlaySoundMem(ClickSE, DX_PLAYTYPE_BACK, TRUE);
		switch (T_selectnum)
		{
		case 0:

			GameData::Init_Data();   //�f�[�^�̏�����

			// �J�����[�h����Debug_Manager.h��"DEBUG_MODE_GAMEMAIN"���R�����g�A�E�g����
#ifdef  DEBUG_MODE_GAMEMAIN

			return dynamic_cast<AbstractScene*> (new Scene_Stage01());
#else
			return dynamic_cast<AbstractScene*> (new GameMainScene());
		case 1:
			return dynamic_cast<AbstractScene*> (new HelpScene());
			/*if (KeyManager::OnPadClicked(PAD_INPUT_A))
			{

			}*/
			break;
		case 2:
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			break;
		case 3:
			return dynamic_cast<AbstractScene*> (new EndScene());
			/*return dynamic_cast<AbstractScene*> (new HelpScene());
			return dynamic_cast<AbstractScene*> (new Scene_Ranking());
			return dynamic_cast<AbstractScene*> (new EndScene());*/
#endif
			break;



#ifdef  DEBUG_MODE_GAMEMAIN


			
#endif
				


		default:
			break;
		}
	}

	return this;  //�X�V�Ȃ�
}